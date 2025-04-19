#include <gkyl_canonical_pb_kernels.h>  
#include <gkyl_binop_mul_ser.h> 
GKYL_CU_DH void canonical_pb_vars_util_1x2v_tensor_p2(const double *h_ij_inv, const double *v_i, const double *u_j, double* GKYL_RESTRICT v_dot_u) 
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
  const double *Vy = &v_i[3]; 

  const double *Ux = &u_j[0]; 
  const double *Uy = &u_j[3]; 

  const double *Hxx = &h_ij_inv[0]; 
  const double *Hxy = &h_ij_inv[3]; 
  const double *Hyy = &h_ij_inv[6]; 

  // h^{ij}*v_i*u_j 
  double Hxx_Vx[3] = {0.0}; 
  double Hxx_Vx_Ux[3] = {0.0}; 
  binop_mul_1d_ser_p2(Hxx, Vx, Hxx_Vx); 
  binop_mul_1d_ser_p2(Hxx_Vx, Ux, Hxx_Vx_Ux); 
 
  double Hxy_Vx[3] = {0.0}; 
  double Hxy_Vx_Uy[3] = {0.0}; 
  binop_mul_1d_ser_p2(Hxy, Vx, Hxy_Vx); 
  binop_mul_1d_ser_p2(Hxy_Vx, Uy, Hxy_Vx_Uy); 
 
  double Hxy_Ux[3] = {0.0}; 
  double Hxy_Ux_Vy[3] = {0.0}; 
  binop_mul_1d_ser_p2(Hxy, Ux, Hxy_Ux); 
  binop_mul_1d_ser_p2(Hxy_Ux, Vy, Hxy_Ux_Vy); 
 
  double Hyy_Vy[3] = {0.0}; 
  double Hyy_Vy_Uy[3] = {0.0}; 
  binop_mul_1d_ser_p2(Hyy, Vy, Hyy_Vy); 
  binop_mul_1d_ser_p2(Hyy_Vy, Uy, Hyy_Vy_Uy); 
 
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
 
} 
