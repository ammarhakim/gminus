// Private header: not for direct use
#pragma once

#include <math.h>

#include <gkyl_array.h>
#include <gkyl_basis.h>
#include <gkyl_proj_on_basis.h>
#include <gkyl_canonical_pb_gr_Gamma_kernels.h>
#include <gkyl_range.h>
#include <gkyl_util.h>
#include <assert.h>

typedef void (*gr_n_set_t)(int count, struct gkyl_nmat *A, struct gkyl_nmat *rhs, 
  const double *M0, const double *M1i);

typedef void (*gr_n_copy_t)(int count, const double *h_ij_inv, struct gkyl_nmat *x, 
  const double *M0, double* GKYL_RESTRICT n);

typedef void (*gr_GammaV_t)(const double *h_ij_inv, const double *u_i, double* GKYL_RESTRICT u_i_sq, 
  double* GKYL_RESTRICT GammaV, double* GKYL_RESTRICT GammaV_sq);

typedef void (*gr_pressure_t)(const double *w, const double *dxv, 
  const double *h_ij_inv, const double *u_i, const double *u_i_sq, 
  const double *GammaV, const double *GammaV_sq, 
  const double *f, double* GKYL_RESTRICT gr_pressure);

// The cv_index[cd].vdim[vd] is used to index the various list of
// kernels below
GKYL_CU_D
static struct { int vdim[4]; } cv_index[] = {
  {-1, -1, -1, -1}, // 0x makes no sense
  {-1,  0,  1,  2}, // 1x kernel indices
  {-1, -1,  3,  4}, // 2x kernel indices
  {-1, -1, -1,  5}, // 3x kernel indices  
};

// for use in kernel tables
typedef struct { gr_n_set_t kernels[3]; } gkyl_dg_gr_vars_n_set_kern_list;
typedef struct { gr_n_copy_t kernels[3]; } gkyl_dg_gr_vars_n_copy_kern_list;
typedef struct { gr_GammaV_t kernels[3]; } gkyl_dg_gr_vars_GammaV_kern_list;
typedef struct { gr_pressure_t kernels[3]; } gkyl_dg_gr_vars_pressure_kern_list;

struct gkyl_dg_calc_gr_vars {
  struct gkyl_rect_grid phase_grid; // Phase-space grid for cell spacing and cell center 
                                    // in pressure velocity moment computation.
  struct gkyl_rect_grid vel_grid; // Momentum (four-velocity)-space grid for cell spacing and cell center 
                                  // in gamma and 1/gamma computation.
  struct gkyl_range vel_range; // Momentum (four-velocity)-space range.
  int poly_order; // polynomial order (determines whether we solve linear system or use basis_inv method).
  struct gkyl_range mem_range; // Configuration-space range for linear solve.

  struct gkyl_nmat *As, *xs; // matrices for LHS and RHS for V_drift solve to find rest-frame density.
  gkyl_nmat_mem *mem; // memory for use in batched linear solve for V_drift solve to find rest-frame density.
  int Ncomp; // number of components in the linear solve (vdim components of V_drift from weak division).

  gr_n_set_t gr_n_set; // kernel for setting matrices for linear solve for rest-frame density.
  gr_n_copy_t gr_n_copy; // kernel for copying solution for V_drift from weak division and computing rest-frame density.
  gr_GammaV_t gr_GammaV; // kernel for computing bulk four-velocity derived quantities such as GammaV.
  gr_pressure_t gr_pressure; // kernel for computing rest-frame pressure as a velocity moment of distribution function.

  uint32_t flags;
  struct gkyl_dg_calc_gr_vars *on_dev; // pointer to itself or device data.
};

// Set matrices for computing rest-frame density kernel list (Serendipity kernels).
GKYL_CU_D
static const gkyl_dg_gr_vars_n_set_kern_list ser_gr_vars_n_set_kernels[] = {
  // 1x kernels
  { NULL, gr_vars_n_set_1x1v_ser_p1, gr_vars_n_set_1x1v_ser_p2 }, // 0
  { NULL, gr_vars_n_set_1x2v_ser_p1, gr_vars_n_set_1x2v_ser_p2 }, // 1
  { NULL, gr_vars_n_set_1x3v_ser_p1, gr_vars_n_set_1x3v_ser_p2 }, // 2
  // 2x kernels
  { NULL, gr_vars_n_set_2x2v_ser_p1, gr_vars_n_set_2x2v_ser_p2 }, // 3
  { NULL, gr_vars_n_set_2x3v_ser_p1, gr_vars_n_set_2x3v_ser_p2 }, // 4
  // 3x kernels
  { NULL, gr_vars_n_set_3x3v_ser_p1, NULL }, // 5
};

// Copy solution for computing rest-frame density kernel list (Serendipity kernels).
GKYL_CU_D
static const gkyl_dg_gr_vars_n_copy_kern_list ser_gr_vars_n_copy_kernels[] = {
  // 1x kernels
  { NULL, gr_vars_n_copy_1x1v_ser_p1, gr_vars_n_copy_1x1v_ser_p2 }, // 0
  { NULL, gr_vars_n_copy_1x2v_ser_p1, gr_vars_n_copy_1x2v_ser_p2 }, // 1
  { NULL, gr_vars_n_copy_1x3v_ser_p1, gr_vars_n_copy_1x3v_ser_p2 }, // 2
  // 2x kernels
  { NULL, gr_vars_n_copy_2x2v_ser_p1, gr_vars_n_copy_2x2v_ser_p2 }, // 3
  { NULL, gr_vars_n_copy_2x3v_ser_p1, gr_vars_n_copy_2x3v_ser_p2 }, // 4
  // 3x kernels
  { NULL, gr_vars_n_copy_3x3v_ser_p1, NULL }, // 5
};

// Compute bulk four-velocity derived quantities kernel list (Serendipity kernels).
GKYL_CU_D
static const gkyl_dg_gr_vars_GammaV_kern_list ser_gr_vars_GammaV_kernels[] = {
  // 1x kernels
  { NULL, gr_vars_GammaV_1x1v_ser_p1, gr_vars_GammaV_1x1v_ser_p2 }, // 0
  { NULL, gr_vars_GammaV_1x2v_ser_p1, gr_vars_GammaV_1x2v_ser_p2 }, // 1
  { NULL, gr_vars_GammaV_1x3v_ser_p1, gr_vars_GammaV_1x3v_ser_p2 }, // 2
  // 2x kernels
  { NULL, gr_vars_GammaV_2x2v_ser_p1, gr_vars_GammaV_2x2v_ser_p2 }, // 3
  { NULL, gr_vars_GammaV_2x3v_ser_p1, gr_vars_GammaV_2x3v_ser_p2 }, // 4
  // 3x kernels
  { NULL, gr_vars_GammaV_3x3v_ser_p1, NULL }, // 5
};

// Compute rest-frame pressure kernel list (Serendipity kernels).
GKYL_CU_D
static const gkyl_dg_gr_vars_pressure_kern_list ser_gr_vars_pressure_kernels[] = {
  // 1x kernels
  { NULL, gr_vars_pressure_1x1v_ser_p1, gr_vars_pressure_1x1v_ser_p2 }, // 0
  { NULL, gr_vars_pressure_1x2v_ser_p1, gr_vars_pressure_1x2v_ser_p2 }, // 1
  { NULL, gr_vars_pressure_1x3v_ser_p1, gr_vars_pressure_1x3v_ser_p2 }, // 2
  // 2x kernels
  { NULL, gr_vars_pressure_2x2v_ser_p1, gr_vars_pressure_2x2v_ser_p2 }, // 3
  { NULL, gr_vars_pressure_2x3v_ser_p1, gr_vars_pressure_2x3v_ser_p2 }, // 4
  // 3x kernels
  { NULL, NULL, NULL }, // 5
};

// Compute rest-frame pressure kernel list (Tensor kernels).
GKYL_CU_D
static const gkyl_dg_gr_vars_pressure_kern_list tensor_gr_vars_pressure_kernels[] = {
  // 1x kernels
  { NULL, gr_vars_pressure_1x1v_tensor_p1, gr_vars_pressure_1x1v_tensor_p2 }, // 0
  { NULL, gr_vars_pressure_1x2v_tensor_p1, gr_vars_pressure_1x2v_tensor_p2 }, // 1
  { NULL, gr_vars_pressure_1x3v_tensor_p1, gr_vars_pressure_1x3v_tensor_p2 }, // 2
  // 2x kernels
  { NULL, gr_vars_pressure_2x2v_tensor_p1, gr_vars_pressure_2x2v_tensor_p2 }, // 3
  { NULL, gr_vars_pressure_2x3v_tensor_p1, NULL }, // 4
  // 3x kernels
  { NULL, gr_vars_pressure_3x3v_tensor_p1, NULL }, // 5
};

GKYL_CU_D
static gr_n_set_t
choose_gr_vars_n_set_kern(enum gkyl_basis_type b_type, int cdim, int vdim, int poly_order)
{
  switch (b_type) {
    case GKYL_BASIS_MODAL_SERENDIPITY:    
      return ser_gr_vars_n_set_kernels[cv_index[cdim].vdim[vdim]].kernels[poly_order];
      break;
    default:
      assert(false);
      break;  
  }
}

GKYL_CU_D
static gr_n_copy_t
choose_gr_vars_n_copy_kern(enum gkyl_basis_type b_type, int cdim, int vdim, int poly_order)
{
  switch (b_type) {
    case GKYL_BASIS_MODAL_SERENDIPITY:   
      return ser_gr_vars_n_copy_kernels[cv_index[cdim].vdim[vdim]].kernels[poly_order];
      break;
    default:
      assert(false);
      break;  
  }
}

GKYL_CU_D
static gr_GammaV_t
choose_gr_vars_GammaV_kern(enum gkyl_basis_type b_type, int cdim, int vdim, int poly_order)
{
  switch (b_type) {
    case GKYL_BASIS_MODAL_SERENDIPITY:    
      return ser_gr_vars_GammaV_kernels[cv_index[cdim].vdim[vdim]].kernels[poly_order];
      break;
    default:
      assert(false);
      break;  
  }
}

GKYL_CU_D
static gr_pressure_t
choose_gr_vars_pressure_kern(enum gkyl_basis_type b_type, int cdim, int vdim, int poly_order)
{
  switch (b_type) {
    case GKYL_BASIS_MODAL_SERENDIPITY:
      if (poly_order != 2)
        // Only polyorder 2 basis are supported for ser
        assert(false);
      return ser_gr_vars_pressure_kernels[cv_index[cdim].vdim[vdim]].kernels[poly_order];
      break; 
    case GKYL_BASIS_MODAL_HYBRID:
      if (poly_order != 1)
        // Only polyorder 1 basis are supported for hybrid
        assert(false); 
      return ser_gr_vars_pressure_kernels[cv_index[cdim].vdim[vdim]].kernels[poly_order];
      break; 
    case GKYL_BASIS_MODAL_TENSOR:
      return tensor_gr_vars_pressure_kernels[cv_index[cdim].vdim[vdim]].kernels[poly_order];
      break; 
    default:
      assert(false);
      break;  
  }
}
