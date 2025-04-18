#include <gkyl_canonical_pb_kernels.h>  
#include <gkyl_binop_mul_ser.h> 
GKYL_CU_DH void canonical_pb_vars_util_1x1v_ser_p2(const double *h_ij_inv, const double *v_i, const double *u_j, double* GKYL_RESTRICT v_dot_u) 
{ 
  // h_ij_inv:         Input volume expansion of the inverse metric tensor.
  //                   [Hxx, Hxy, Hxz, 
  //                     - , Hyy, Hyz, 
  //                     - ,  - , Hzz] 
  // v_i:              Input volume expansion of v.
  //                   [vx, vy, vz] 
  // u_j:              Input volume expansion of u.
  //                   [ux, uy, uz] 
  // v_dot_u:           Output volume expansion of v_dot_u = h^{ij}*v_i*u_j .

  const double *Vx = &v_i[0]; 

  const double *Ux = &u_j[0]; 

  const double *Hxx = &h_ij_inv[0]; 

  // h^{ij}*v_i*u_j 
  double Hxx_Vx[3] = {0.0}; 
  double Hxx_Vx_Ux[3] = {0.0}; 
  binop_mul_1d_ser_p2(Hxx, Vx, Hxx_Vx); 
  binop_mul_1d_ser_p2(Hxx_Vx, Ux, Hxx_Vx_Ux); 
 
  v_dot_u[0] = 0.0; 
  v_dot_u[0] += Hxx_Vx_Ux[0]; 
  v_dot_u[1] = 0.0; 
  v_dot_u[1] += Hxx_Vx_Ux[1]; 
  v_dot_u[2] = 0.0; 
  v_dot_u[2] += Hxx_Vx_Ux[2]; 
 
} 
