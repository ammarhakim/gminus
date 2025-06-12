/* -*- c++ -*- */

extern "C" {
#include <float.h>
#include <math.h>
#include <time.h>

#include <gkyl_alloc.h>
#include <gkyl_array.h>
#include <gkyl_array_ops.h>
#include <gkyl_null_comm.h>
#include <gkyl_rect_decomp.h>
#include <gkyl_util.h>
#include <gkyl_wave_geom.h>
#include <gkyl_wave_prop.h>
#include <gkyl_wave_prop_priv.h>
}

__global__ static void
gkyl_wave_prop_waves_qfluct_cu_ker(gkyl_wv_eqn *eqn, 
  int ndim, int dir,  int loidx, int upidx, int meqn, double cflm, 
  enum gkyl_wv_flux_type ftype, 
  struct gkyl_range update_range, struct gkyl_range perp_range, 
  const struct gkyl_wave_geom *wg, const struct gkyl_array *redo_fluct, const struct gkyl_array *qin, 
  struct gkyl_array *waves, struct gkyl_array *speeds, struct gkyl_array *amdq, struct gkyl_array *apdq, 
  struct gkyl_array *cfla, struct gkyl_array *is_cfl_violated)
{
  int idxl[GKYL_MAX_DIM], idxr[GKYL_MAX_DIM];
  // 2D thread grid
  // linc2 goes from loidx to upidx (total size of linc2 set by upidx-loidx)
  long linc2 = threadIdx.y + blockIdx.y*blockDim.y + loidx;
  for (unsigned long tid = threadIdx.x + blockIdx.x*blockDim.x;
    tid < perp_range.volume; tid += blockDim.x*gridDim.x) {

    gkyl_sub_range_inv_idx(&perp_range, tid, idxl);
    gkyl_copy_int_arr(ndim, idxl, idxr);

    // perform 1D sweeps handled by second dimension of thread grid
    idxl[dir] = linc2-1; idxr[dir] = linc2;

    // Fetch the redo fluctuation flag, geometry, waves, speeds, and A^-/+ Delta Q fluctuations arrays
    const double *redo_fluct_d = (const double*) gkyl_array_cfetch(redo_fluct, idxr);
    const struct gkyl_wave_cell_geom *cg = gkyl_wave_geom_get(geom, idxr);
    double *waves_d = (double*) gkyl_array_fetch(waves, idxr);
    double *speeds_d = (double*) gkyl_array_fetch(speeds, idxr);
    double *amdq_d = (double*) gkyl_array_fetch(amdq, idxr);
    double *apdq_d = (double*) gkyl_array_fetch(apdq, idxr);

    // compute fluctuations and waves only if needed (this
    // prevents doing the full 1D sweep with low-order fluxes
    // on positivity violations)
    if (redo_fluct_d[0] > 0.0) {
      long lidx = gkyl_range_idx(update_range, idxl);
      long ridx = gkyl_range_idx(update_range, idxr);

      const double *qinl = (const double*) gkyl_array_cfetch(qin, lidx);
      const double *qinr = (const double*) gkyl_array_cfetch(qin, ridx);

      gkyl_wv_eqn_fused_rotate_waves_qfluct(eqn, ftype, 
        cg->tau1[dir], cg->tau2[dir], cg->norm[dir], cg->lenr[dir], 
        qinl, qinr, 
        waves_d, speeds_d, amdq_d, apdq_d); 

      // Reset second order flux correction to zero if redo_fluct flag is true 
      // so that no second order fluxes are used if we have to redo any fluctuation
      // computation. If we do not have to redo the fluctuations, the second order
      // fluxes will be computed and included in the update outside this loop. 
      double *flux2_d = (double*) gkyl_array_fetch(flux2, idxr);
      for (int i=0; i<meqn; ++i) {
        flux2_d[i] = 0.0; 
      }

      double *cfla_d = (double*) gkyl_array_fetch(cfla, idxr);  
      clfa_d[0] = dtdx/cg->kappa*my_max_speed; 
      // check time-step before any updates are performed
      if (cfla[0] > cflm) {
        double *is_cfl_violated_d = (double*) gkyl_array_fetch(is_cfl_violated, idxr);  
        is_cfl_violated_d[0] = 1.0;
      }   
    }        
  }
}

__global__ static void
gkyl_wave_prop_second_order_flux_cu_ker(enum gkyl_wave_limiter limiter, double dtdx, 
  int ndim, int dir,  int loidx, int upidx, int meqn, int mwaves, 
  struct gkyl_range update_range, struct gkyl_range perp_range, 
  const struct gkyl_wave_geom *wg, struct gkyl_array *waves, struct gkyl_array *speeds, 
  struct gkyl_array *flux2)
{
  int idxl[GKYL_MAX_DIM], idxc[GKYL_MAX_DIM], idxr[GKYL_MAX_DIM];
  // 2D thread grid
  // linc2 goes from loidx to upidx (total size of linc2 set by upidx-loidx)
  long linc2 = threadIdx.y + blockIdx.y*blockDim.y + loidx;
  for (unsigned long tid = threadIdx.x + blockIdx.x*blockDim.x;
    tid < perp_range.volume; tid += blockDim.x*gridDim.x) {

    gkyl_sub_range_inv_idx(&perp_range, tid, idxc);
    gkyl_copy_int_arr(ndim, idxc, idxl);
    gkyl_copy_int_arr(ndim, idxl, idxr);

    // perform 1D sweeps handled by second dimension of thread grid
    idxl[dir] = linc2-1; idxc[dir] = linc2; idxr[dir] = linc2+1; 
    for (int mw=0; mw<mwaves; ++mw) {
      const double *wl = (const double*) gkyl_array_cfetch(waves, idxl);
      double *wc = (double*) gkyl_array_cfetch(waves, idxc);
      const double *wr = (const double*) gkyl_array_cfetch(waves, idxr);
      const double *s = (const double*) gkyl_array_cfetch(speeds, idxc);

      double dotl = wave_dot_prod(meqn, &wl[mw*meqn], &wc[mw*meqn]);
      double wnorm2 = wave_dot_prod(meqn, &wc[mw*meqn], &wc[mw*meqn]);
      double dotr = wave_dot_prod(meqn, &wc[mw*meqn], &wr[mw*meqn]);
      if (wnorm2 > 0) {
        double r = s[mw] > 0 ? dotl/wnorm2 : dotr/wnorm2;
        double theta = limiter_function(r, limiter);
        wave_rescale(meqn, theta, &wc[mw*meqn]);
      }
    }
    // Each cell owns its flux at the lower interface, so fetch the 
    // lower and center geometry to get kappa on either side of the interface
    const struct gkyl_wave_cell_geom *cgl = gkyl_wave_geom_get(geom, idxl);
    const struct gkyl_wave_cell_geom *cgc = gkyl_wave_geom_get(geom, idxc);
    double kappal = cgl->kappa;
    double kappac = cgc->kappa;
    double *flux2 = (double*) gkyl_array_fetch(flux2, idxc);
    for (int mw=0; mw<mwaves; ++mw) {
      calc_second_order_qflux(meqn, dtdx/(0.5*(kappal+kappar)), s[mw], &wc[mw*meqn], flux2);
    }
  }
}

__global__ static void
gkyl_wave_prop_update_state_cu_kern(double dtdx, 
  int ndim, int dir,  int loidx_c, int upidx_c, int meqn, 
  struct gkyl_range update_range, 
  const struct gkyl_wave_geom *wg, const struct gkyl_array *qin, 
  const struct gkyl_array *amdq, const struct gkyl_array *apdq, const struct gkyl_array *flux2, 
  struct gkyl_array *redo_fluct, struct gkyl_array *qout)
{
  int idxl[GKYL_MAX_DIM], idxc[GKYL_MAX_DIM], idxr[GKYL_MAX_DIM];
  for (unsigned long tid = threadIdx.x + blockIdx.x*blockDim.x;
    tid < update_range.volume; tid += blockDim.x*gridDim.x) { 

    gkyl_sub_range_inv_idx(&update_range, tid, idxc);
    gkyl_copy_int_arr(ndim, idxc, idxr);
    idxr[dir] = i+1; 
    // Each cell owns its flux at the lower interface, so fetch the 
    // lower geometry to get kappa in the cell and the right-going fluctuations 
    // and second order fluxes on the lower interface and left-going fluctuations
    // and second order fluxes on the upper interface
    const struct gkyl_wave_cell_geom *cg = gkyl_wave_geom_get(geom, idxc);
    const double *apdq_l = (const double*) gkyl_array_cfetch(apdq, idxc);
    const double *amdq_r = (const double*) gkyl_array_cfetch(amdq, idxr);
    const double *flux2_l = (const double*) gkyl_array_cfetch(flux2, idxc);
    const double *flux2_r = (const double*) gkyl_array_cfetch(flux2, idxr);
    const double *qin_c = (const double*) gkyl_array_cfetch(qin, idxc);
    double *qout_c = (double*) gkyl_array_fetch(qout, idxc);
    for (int i=0; i<meqn; ++i) {
      qout_c[i] = qin_c[i] 
        - dtdx/cg->kappa*(apdq_l[i] + amdq_r[i] + flux2_r[i] - flux2_l[i]);
    }
    if (check_inv_domain) {
      idxl[dir] = i-1; 
      double *qout_l = (double*) gkyl_array_cfetch(qout, idxl);
      // Check the solution on both sides of the interface
      if (!gkyl_wv_eqn_fuse_check_inv(eqn, qout_l, qout_c)) {
        double *redo_fluct_c = (double*) gkyl_array_fetch(redo_fluct, idxc);
        redo_fluct_c[0] = 1.0; 
        // Since we are looping over cells and we own our lower edge values, 
        // if the upper edge would drive a cell negative, we need to also 
        // set the redo_fluct flag at the upper edge. 
        if (idxc[dir] == update_range.upper[dir]) {
          double *redo_fluct_r = (double*) gkyl_array_fetch(redo_fluct, idxr);
          redo_fluct_r[0] = 1.0; 
        }
      }
    }
  }
}

__global__ static void
gkyl_wave_prop_redo_update_state_cu_kern(double dtdx, 
  int ndim, int dir,  int loidx_c, int upidx_c, int meqn, 
  struct gkyl_range update_range, 
  const struct gkyl_wave_geom *wg, const struct gkyl_array *qin, 
  const struct gkyl_array *amdq, const struct gkyl_array *apdq, 
  struct gkyl_array *qout)
{
  int idxl[GKYL_MAX_DIM], idxc[GKYL_MAX_DIM], idxr[GKYL_MAX_DIM];
  for (unsigned long tid = threadIdx.x + blockIdx.x*blockDim.x;
    tid < update_range.volume; tid += blockDim.x*gridDim.x) { 

    gkyl_sub_range_inv_idx(&update_range, tid, idxc);
    gkyl_copy_int_arr(ndim, idxc, idxr);
    idxr[dir] = i+1; 
    // Each cell owns its flux at the lower interface, so fetch the 
    // lower geometry to get kappa in the cell and the right-going fluctuations 
    // and second order fluxes on the lower interface and left-going fluctuations
    // and second order fluxes on the upper interface
    const struct gkyl_wave_cell_geom *cg = gkyl_wave_geom_get(geom, idxc);
    const double *apdq_l = (const double*) gkyl_array_cfetch(apdq, idxc);
    const double *amdq_r = (const double*) gkyl_array_cfetch(amdq, idxr);
    const double *flux2_l = (const double*) gkyl_array_cfetch(flux2, idxc);
    const double *flux2_r = (const double*) gkyl_array_cfetch(flux2, idxr);
    const double *qin_c = (const double*) gkyl_array_cfetch(qin, idxc);
    double *qout_c = (double*) gkyl_array_fetch(qout, idxc);
    for (int i=0; i<meqn; ++i) {
      qout_c[i] = qin_c[i] 
        - dtdx/cg->kappa*(apdq_l[i] + amdq_r[i] + flux2_r[i] - flux2_l[i]);
    }
  }    
}

// advance method
struct gkyl_wave_prop_status
gkyl_wave_prop_advance_cu(gkyl_wave_prop *wv,
  double tm, double dt, const struct gkyl_range *update_range,
  const struct gkyl_array *qin, struct gkyl_array *qout)
{
  wv->n_calls += 1;
  
  int ndim = update_range->ndim;
  int meqn = wv->equation->num_equations;
  //  when forced to use Lax fluxes, we only have a single wave
  int mwaves = wv->force_low_order_flux ? 2 :  wv->equation->num_waves;

  double cfl = wv->cfl, cflm = 1.1*cfl;
  gkyl_array_clear(wv->cfla, 0.0); 
  gkyl_array_clear(wv->is_cfl_violated, 0.0);
  // Small arrays for reducing actual cfl value over the whole domain
  // and whether the cfl was violated anywhere in the domain. 
  double red_cfla[1];
  double red_is_cfl_violated[1];
  double red_cfl[2];
  double red_cfl_global[2];

  // Loop over update directions
  for (int d=0; d<wv->num_up_dirs; ++d) {
    int dir = wv->update_dirs[d];

    double dtdx = dt/wv->grid.dx[dir];

    // upper/lower bounds in direction 'd'. These are edge indices
    int loidx = update_range->lower[dir]-1;
    int upidx = update_range->upper[dir]+2;

    // cell indices in 1D slice for interior cells
    int loidx_c = update_range->lower[dir];
    int upidx_c = update_range->upper[dir];

    struct gkyl_range perp_range;
    gkyl_range_shorten_from_above(&perp_range, update_range, dir, 1);
    struct gkyl_range_iter iter;
    gkyl_range_iter_init(&iter, &perp_range);

    // Copy previous time step solution 
    gkyl_array_set_range(qout, 1.0, qin, update_range); 
    // Set the redo_fluct array so in the first sweep, we compute fluxes at every interface
    gkyl_array_clear(wv->redo_fluct, 1.0); 

    enum gkyl_wv_flux_type ftype = wv->force_low_order_flux ?
      GKYL_WV_LOW_ORDER_FLUX : GKYL_WV_HIGH_ORDER_FLUX;
    gkyl_wave_prop_waves_qfluct_cu_ker(wv->equation->on_dev, ndim, dir, loidx, upidx, meqn, cflm, 
      ftype, *update_range, perp_range, 
      wv->wg->on_dev, wv->redo_fluct->on_dev, qin->on_dev, 
      wv->waves->on_dev, wv->speeds->on_dev, wv->amdq->on_dev, wv->apdq->on_dev, 
      wv->cfla->on_dev, wv->is_cfl_violated->on_dev);

    // To avoid race conditions on the wave limiting, split the second order flux
    // computation into a separate kernel after waves and fluctuations computed
    gkyl_wave_prop_second_order_flux_cu_ker(wv->limiter, ndim, dir, loidx, upidx, 
      meqn, mwaves, *update_range, perp_range, 
      wv->wg->on_dev, wv->waves->on_dev, wv->speeds->on_dev, wv->flux2->on_dev);

    // Before updating the state, determine if the CFL was violated anywhere in the domain
    gkyl_array_reduce_range(wv->cfla_ptr, wv->cfla, GKYL_MAX, update_range);  
    gkyl_array_reduce_range(wv->is_cfl_violated_ptr, wv->is_cfl_violated, GKYL_MAX, update_range);
    gkyl_cu_memcpy(red_cfla, wv->cfla_ptr, sizeof(double), GKYL_CU_MEMCPY_D2H);
    gkyl_cu_memcpy(red_is_cfl_violated, wv->is_cfl_violated_ptr, sizeof(double), GKYL_CU_MEMCPY_D2H);
    red_cfl[0] = red_cfla[0]; 
    red_cfl[1] = red_is_cfl_violated[0]; 
    gkyl_comm_allreduce_host(wv->comm, GKYL_DOUBLE, GKYL_MAX, 2, &red_cfl, &red_cfl_global);
    if (red_cfl_global[1] > 0.0) {
      goto outsideloop;
    }

    // Update the solution with both the first order update and the second order corrections. 
    gkyl_array_clear(wv->redo_fluct, 0.0); // Clear redo fluctuation flag before update. 
    gkyl_wave_prop_update_state_cu_kern(dtdx, ndim, dir, loidx_c, upidx_c, meqn, *update_range, 
      wv->wg->on_dev, qin->on_dev, 
      wv->amdq->on_dev, wv->apdq->on_dev,  wv->flux2->on_dev, 
      wv->redo_fluct->on_dev, qout->on_dev); 

    // Determine if we need to redo any flux computations 
    gkyl_array_reduce_range(wv->redo_fluct_ptr, wv->redo_fluct, GKYL_MAX, update_range);
    double redo_fluct_ptr_ho[1];
    gkyl_cu_memcpy(redo_fluct_ptr_ho, wv->redo_fluct_ptr, sizeof(double), GKYL_CU_MEMCPY_D2H);
    if (redo_fluct_ptr_ho[0] > 0.0) {
      gkyl_wave_prop_waves_qfluct_cu_ker(wv->equation->on_dev, ndim, dir, loidx, upidx, meqn, cflm, 
        GKYL_WV_LOW_ORDER_FLUX, *update_range, perp_range, 
        wv->wg->on_dev, wv->redo_fluct->on_dev, qin->on_dev, 
        wv->waves->on_dev, wv->speeds->on_dev, wv->amdq->on_dev, wv->apdq->on_dev, 
        wv->cfla->on_dev, wv->is_cfl_violated->on_dev); 
      
      // Update state with re-computed first order fluxes. 
      // Note that the second order fluxes are zeroed out at re-done interfaces
      // so no second order corrections are included when re-doing the update. 
      gkyl_wave_prop_redo_update_state_cu_kern(dtdx, ndim, dir, loidx_c, upidx_c, meqn, *update_range, 
      wv->wg->on_dev, qin->on_dev, 
      wv->amdq->on_dev, wv->apdq->on_dev,  wv->flux2->on_dev, 
      wv->redo_fluct->on_dev, qout->on_dev); 
    }
  }  

  outsideloop:
  ;
  double dt_suggested = dt*cfl/fmax(red_cfl_global[0], DBL_MIN);
  if (red_cfl_global[1] > 0.0) {
    // indicate failure, and return smaller stable time-step
    return (struct gkyl_wave_prop_status) {
      .success = 0,
      .dt_suggested = dt_suggested,
      .max_speed = 0.0, // Not currently used by GPUs
    };
  }
  // on success, suggest only bigger time-step; (Only way dt can
  // reduce is if the update fails. If the code comes here the update
  // succeeded and so we should not allow dt to reduce).
  return (struct gkyl_wave_prop_status) {
    .success = red_cfl_global[1] > 0.0 ? 0 : 1,
    .dt_suggested = dt_suggested > dt ? dt_suggested : dt,
    .max_speed = 0.0, // Not currently used by GPUs
  }; 
}