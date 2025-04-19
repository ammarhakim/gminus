#include <gkyl_canonical_pb_kernels.h>  
#include <gkyl_binop_mul_ser.h> 
GKYL_CU_DH void canonical_pb_vars_util_2x2v_tensor_p2(const double *h_ij_inv, const double *v_i, const double *u_j, double* GKYL_RESTRICT v_dot_u) 
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
  const double *Vy = &v_i[9]; 

  const double *Ux = &u_j[0]; 
  const double *Uy = &u_j[9]; 

  const double *Hxx = &h_ij_inv[0]; 
  const double *Hxy = &h_ij_inv[9]; 
  const double *Hyy = &h_ij_inv[18]; 

  // h^{ij}*v_i*u_j 
  double Hxx_Vx[9] = {0.0}; 
  double Hxx_Vx_Ux[9] = {0.0}; 
  binop_mul_2d_tensor_p2(Hxx, Vx, Hxx_Vx); 
  binop_mul_2d_tensor_p2(Hxx_Vx, Ux, Hxx_Vx_Ux); 
 
  double Hxy_Vx[9] = {0.0}; 
  double Hxy_Vx_Uy[9] = {0.0}; 
  binop_mul_2d_tensor_p2(Hxy, Vx, Hxy_Vx); 
  binop_mul_2d_tensor_p2(Hxy_Vx, Uy, Hxy_Vx_Uy); 
 
  double Hxy_Ux[9] = {0.0}; 
  double Hxy_Ux_Vy[9] = {0.0}; 
  binop_mul_2d_tensor_p2(Hxy, Ux, Hxy_Ux); 
  binop_mul_2d_tensor_p2(Hxy_Ux, Vy, Hxy_Ux_Vy); 
 
  double Hyy_Vy[9] = {0.0}; 
  double Hyy_Vy_Uy[9] = {0.0}; 
  binop_mul_2d_tensor_p2(Hyy, Vy, Hyy_Vy); 
  binop_mul_2d_tensor_p2(Hyy_Vy, Uy, Hyy_Vy_Uy); 
 
  v_dot_u[0] = 0.0; 
  v_dot_u[0] += Hxx_Vx_Ux[0]; 
  v_dot_u[0] += (Hxy_Vx_Uy[0] + Hxy_Ux_Vy[0]); 
  v_dot_u[0] +=  Hyy_Vy_Uy[0]; 
  v_dot_u[1] = 0.0; 
  v_dot_u[1] += Hxx_Vx_Ux[1]; 
  v_dot_u[1] += (Hxy_Vx_Uy[1] + Hxy_Ux_Vy[1]); 
  v_dot_u[1] +=  Hyy_Vy_Uy[1]; 
  v_dot_u[2] = 0.0; 
  v_dot_u[2] += Hxx_Vx_Ux[2]; 
  v_dot_u[2] += (Hxy_Vx_Uy[2] + Hxy_Ux_Vy[2]); 
  v_dot_u[2] +=  Hyy_Vy_Uy[2]; 
  v_dot_u[3] = 0.0; 
  v_dot_u[3] += Hxx_Vx_Ux[3]; 
  v_dot_u[3] += (Hxy_Vx_Uy[3] + Hxy_Ux_Vy[3]); 
  v_dot_u[3] +=  Hyy_Vy_Uy[3]; 
  v_dot_u[4] = 0.0; 
  v_dot_u[4] += Hxx_Vx_Ux[4]; 
  v_dot_u[4] += (Hxy_Vx_Uy[4] + Hxy_Ux_Vy[4]); 
  v_dot_u[4] +=  Hyy_Vy_Uy[4]; 
  v_dot_u[5] = 0.0; 
  v_dot_u[5] += Hxx_Vx_Ux[5]; 
  v_dot_u[5] += (Hxy_Vx_Uy[5] + Hxy_Ux_Vy[5]); 
  v_dot_u[5] +=  Hyy_Vy_Uy[5]; 
  v_dot_u[6] = 0.0; 
  v_dot_u[6] += Hxx_Vx_Ux[6]; 
  v_dot_u[6] += (Hxy_Vx_Uy[6] + Hxy_Ux_Vy[6]); 
  v_dot_u[6] +=  Hyy_Vy_Uy[6]; 
  v_dot_u[7] = 0.0; 
  v_dot_u[7] += Hxx_Vx_Ux[7]; 
  v_dot_u[7] += (Hxy_Vx_Uy[7] + Hxy_Ux_Vy[7]); 
  v_dot_u[7] +=  Hyy_Vy_Uy[7]; 
  v_dot_u[8] = 0.0; 
  v_dot_u[8] += Hxx_Vx_Ux[8]; 
  v_dot_u[8] += (Hxy_Vx_Uy[8] + Hxy_Ux_Vy[8]); 
  v_dot_u[8] +=  Hyy_Vy_Uy[8]; 
 
} 
