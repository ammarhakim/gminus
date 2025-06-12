/* -*- c++ -*- */
extern "C" {
#include <float.h>

#include <gkyl_alloc.h>
#include <gkyl_array_ops.h>
#include <gkyl_array_reduce.h>
#include <gkyl_null_comm.h>
#include <gkyl_ten_moment_grad_closure.h>
#include <gkyl_ten_moment_grad_closure_priv.h>
}

static void
create_offsets_vertices(const struct gkyl_range *range, long offsets[])
{
  int arr1[3] = { -1, -1, -1 }, arr2[3] = { 0, 0, 0 };

  // box spanning stencil
  struct gkyl_range box3;
  gkyl_range_init(&box3, range->ndim, arr1, arr2);

  struct gkyl_range_iter iter3;
  gkyl_range_iter_init(&iter3, &box3);

  // construct list of offsets
  int count = 0;
  while (gkyl_range_iter_next(&iter3))
    offsets[count++] = gkyl_range_offset(range, iter3.idx);
}

static void
create_offsets_centers(const struct gkyl_range *range, long offsets[])
{
  int arr1[3] = { -1, -1, -1 }, arr2[3] = { 0, 0, 0 };

  // box spanning stencil
  struct gkyl_range box3;
  gkyl_range_init(&box3, range->ndim, arr1, arr2);

  struct gkyl_range_iter iter3;
  gkyl_range_iter_init(&iter3, &box3);

  // construct list of offsets
  int count = 0;
  while (gkyl_range_iter_next(&iter3))
    offsets[count++] = gkyl_range_offset(range, iter3.idx);
}

__global__ static void 
gkyl_ten_moment_grad_closure_set_cu_dev_ptrs(gkyl_ten_moment_grad_closure *gces,
  struct gkyl_rect_grid grid, double k0, double cfl)
{
  gces->grid = grid;
  gces->ndim = grid.ndim;
  gces->k0 = k0;
  gces->cfl = cfl;

  grad_closure_calc_q_choose(gces);
  grad_closure_update_q_choose(gces);
}

__global__ static void
gkyl_ten_moment_grad_closure_calc_cu_ker(const gkyl_ten_moment_grad_closure *gces,
  const struct gkyl_range heat_flux_range, const struct gkyl_range update_range,
  long *offsets_vertices, long *offsets_centers, int sz_idx,
  const struct gkyl_array *fluid, const struct gkyl_array *em_tot,
  struct gkyl_array *cflrate, double dt, struct gkyl_array *heat_flux)
{
  const double* fluid_d[8];
  const double* em_tot_d[8];
  double *heat_flux_d;

  int vidx[GKYL_MAX_DIM];

  for(unsigned long linc = threadIdx.x + blockIdx.x*blockDim.x;
      linc < heat_flux_range.volume; linc += blockDim.x*gridDim.x) {

    gkyl_sub_range_inv_idx(&heat_flux_range, linc, vidx);

    long linc_vertex = gkyl_range_idx(&heat_flux_range, vidx);
    long linc_center = gkyl_range_idx(&update_range, vidx);

    for (int i=0; i<sz_idx; ++i) {
      em_tot_d[i] =  (const double*) gkyl_array_cfetch(em_tot,
        linc_center + offsets_vertices[i]);
      fluid_d[i] = (const double*) gkyl_array_cfetch(fluid,
        linc_center + offsets_vertices[i]);
    }

    heat_flux_d = (double*) gkyl_array_fetch(heat_flux, linc_vertex);
    double *cflr = (double*) gkyl_array_fetch(cflrate, linc_center);

    gces->calc_q(gces, fluid_d, cflr, dt, heat_flux_d);
  }
}

__global__ static void
gkyl_ten_moment_grad_closure_update_cu_ker(const gkyl_ten_moment_grad_closure *gces,
  const struct gkyl_range heat_flux_range, const struct gkyl_range update_range,
  long *offsets_vertices, long *offsets_centers, int sz_idx,
  const struct gkyl_array *heat_flux, struct gkyl_array *rhs)
{
  const double* heat_flux_up[8];
  
  int cidx[GKYL_MAX_DIM];

  for(unsigned long linc = threadIdx.x + blockIdx.x*blockDim.x;
    linc < update_range.volume; linc += blockDim.x*gridDim.x) {

    gkyl_sub_range_inv_idx(&update_range, linc, cidx);

    long linc_vertex = gkyl_range_idx(&heat_flux_range, cidx);
    long linc_center = gkyl_range_idx(&update_range, cidx);

    for (int i=0; i<sz_idx; ++i)
      heat_flux_up[i] = (const double*) gkyl_array_cfetch(heat_flux,
        linc_vertex + offsets_centers[i]);

    double* rhs_d = (double*) gkyl_array_fetch(rhs, linc_center);

    gces->update_q(gces, heat_flux_up, rhs_d);
  }
}

gkyl_ten_moment_grad_closure*
gkyl_ten_moment_grad_closure_cu_dev_new(struct gkyl_ten_moment_grad_closure_inp inp)
{
  gkyl_ten_moment_grad_closure *gces = (gkyl_ten_moment_grad_closure*)
    gkyl_malloc(sizeof(gkyl_ten_moment_grad_closure));

  gces->cfla = (double*) gkyl_cu_malloc(sizeof(double));

  struct gkyl_null_comm_inp null = { };
  
  if (inp.comm)
    gces->comm = gkyl_comm_acquire(inp.comm);
  else
    gces->comm = gkyl_null_comm_inew( &null );

  // copy the host struct to device struct
  gkyl_ten_moment_grad_closure *gces_cu = (gkyl_ten_moment_grad_closure*)
    gkyl_cu_malloc(sizeof(gkyl_ten_moment_grad_closure));
  gkyl_cu_memcpy(gces_cu, gces, sizeof(gkyl_ten_moment_grad_closure),
    GKYL_CU_MEMCPY_H2D);

  gkyl_ten_moment_grad_closure_set_cu_dev_ptrs<<<1,1>>>(gces_cu, *(inp.grid),
    inp.k0, inp.cfl);
  
  gces->on_dev = gces_cu; // CPU obj points to itself
  return gces;
}

struct gkyl_ten_moment_grad_closure_status
gkyl_ten_moment_grad_closure_advance_cu(const gkyl_ten_moment_grad_closure *gces,
  const struct gkyl_range *heat_flux_range, const struct gkyl_range *update_range,
  const struct gkyl_array *fluid, const struct gkyl_array *em_tot,
  struct gkyl_array *cflrate, double dt, struct gkyl_array *heat_flux,
  struct gkyl_array *rhs)
{
  int nblocks = heat_flux_range->nblocks, nthreads = heat_flux_range->nthreads;

  double cfla[1] = { 0.0 }, cfl = 0.0;
  double is_cfl_violated = 0.0; // deliberately a double

  // gkyl_cu_memcpy(cfl, gces->cfl, sizeof(double), GKYL_CU_MEMCPY_D2H); // probably don't actually need this? Don't think there's any reason for cfl to be needed on device.
  double cflm = 1.1*gces->cfl;

  int ndim = update_range->ndim;
  long sz[] = { 2, 4, 8 };

  int sz_idx = sz[ndim-1];

  long offsets_vertices[sz_idx];
  create_offsets_vertices(update_range, offsets_vertices);

  long offsets_centers[sz_idx];
  create_offsets_centers(heat_flux_range, offsets_centers);
  
  gkyl_ten_moment_grad_closure_calc_cu_ker<<<nblocks, nthreads>>>(gces->on_dev,
    *heat_flux_range, *update_range, offsets_vertices, offsets_centers, sz_idx,
    fluid->on_dev, em_tot->on_dev, cflrate->on_dev, dt, heat_flux->on_dev);

  gkyl_ten_moment_grad_closure_update_cu_ker<<<nblocks, nthreads>>>(gces->on_dev,
    *heat_flux_range, *update_range, offsets_vertices, offsets_centers, sz_idx,
     heat_flux->on_dev, rhs->on_dev);

  gkyl_array_reduce(gces->cfla, cflrate, GKYL_MAX);
  gkyl_cu_memcpy(cfla, gces->cfla, sizeof(double), GKYL_CU_MEMCPY_D2H);

  if (cfla[0] > cflm)
    is_cfl_violated = 1.0;

  // compute actual CFL, status & max-speed across all domains
  double red_vars[2] = { cfla[0], is_cfl_violated };
  double red_vars_global[2] = { 0.0, 0.0 };
  gkyl_comm_allreduce(gces->comm, GKYL_DOUBLE, GKYL_MAX, 2, &red_vars, &red_vars_global);

  cfla[0] = red_vars_global[0];
  is_cfl_violated = red_vars_global[1];

  double dt_suggested = dt*cfl/fmax(cfla[0], DBL_MIN);

  if (is_cfl_violated > 0.0)
    // indicate failure, and return smaller stable time-step
    return (struct gkyl_ten_moment_grad_closure_status) {
      .success = 0,
      .dt_suggested = dt_suggested,
    };

  // on success, suggest only bigger time-step; (Only way dt can
  // reduce is if the update fails. If the code comes here the update
  // succeeded and so we should not allow dt to reduce).
  return (struct gkyl_ten_moment_grad_closure_status) {
    .success = is_cfl_violated > 0.0 ? 0 : 1,
    .dt_suggested = dt_suggested > dt ? dt_suggested : dt,
  };

}
