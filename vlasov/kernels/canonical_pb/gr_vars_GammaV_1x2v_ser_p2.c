#include <gkyl_canonical_pb_gr_Gamma_kernels.h> 
#include <gkyl_canonical_pb_kernels.h>  
#include <gkyl_basis_ser_1x_p2_sqrt.h> 
GKYL_CU_DH void gr_vars_GammaV_1x2v_ser_p2(const double *h_ij_inv, const double *u_i, double* GKYL_RESTRICT u_i_sq, double* GKYL_RESTRICT GammaV, double* GKYL_RESTRICT GammaV_sq) 
{ 
  // h_ij_inv:         Input volume expansion of the inverse metric tensor.
  //                   [Hxx, Hxy, Hxz, 
  //                     - , Hyy, Hyz, 
  //                     - ,  - , Hzz] 
  // u_i:       Input spatial components of bulk four-velocity = GammaV*V_drift. 
  // u_i_sq:    Output squared spatial components of bulk four-velocity = sum_i u_i^2. 
  // GammaV:    Output bulk four-velocity Lorentz factor = sqrt(1 + |u_i|^2). 
  // GammaV_sq: Output squared bulk four-velocity Lorentz factor = 1 + |u_i|^2. 
 
  canonical_pb_vars_util_1x2v_ser_p2(h_ij_inv, u_i, u_i, u_i_sq); 
  double *V_sq = u_i_sq; 
 
  GammaV_sq[0] = V_sq[0]+1.414213562373095; 
  GammaV_sq[1] = V_sq[1]; 
  GammaV_sq[2] = V_sq[2]; 

  ser_1x_p2_sqrt(GammaV_sq, GammaV); 
} 
 
