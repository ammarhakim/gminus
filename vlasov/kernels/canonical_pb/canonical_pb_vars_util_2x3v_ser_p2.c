#include <gkyl_canonical_pb_kernels.h>  
#include <gkyl_binop_mul_ser.h> 
GKYL_CU_DH void canonical_pb_vars_util_2x3v_ser_p2(const double *h_ij_inv, const double *v_i, const double *u_j, double* GKYL_RESTRICT v_dot_u) 
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
  const double *Vy = &v_i[8]; 
  const double *Vz = &v_i[16]; 

  const double *Ux = &u_j[0]; 
  const double *Uy = &u_j[8]; 
  const double *Uz = &u_j[16]; 

  const double *Hxx = &h_ij_inv[0]; 
  const double *Hxy = &h_ij_inv[8]; 
  const double *Hxz = &h_ij_inv[16]; 
  const double *Hyy = &h_ij_inv[24]; 
  const double *Hyz = &h_ij_inv[32]; 
  const double *Hzz = &h_ij_inv[40]; 

  // h^{ij}*v_i*u_j 
  double Hxx_Vx[8] = {0.0}; 
  double Hxx_Vx_Ux[8] = {0.0}; 
  binop_mul_2d_ser_p2(Hxx, Vx, Hxx_Vx); 
  binop_mul_2d_ser_p2(Hxx_Vx, Ux, Hxx_Vx_Ux); 
 
  double Hxy_Vx[8] = {0.0}; 
  double Hxy_Vx_Uy[8] = {0.0}; 
  binop_mul_2d_ser_p2(Hxy, Vx, Hxy_Vx); 
  binop_mul_2d_ser_p2(Hxy_Vx, Uy, Hxy_Vx_Uy); 
 
  double Hxy_Ux[8] = {0.0}; 
  double Hxy_Ux_Vy[8] = {0.0}; 
  binop_mul_2d_ser_p2(Hxy, Ux, Hxy_Ux); 
  binop_mul_2d_ser_p2(Hxy_Ux, Vy, Hxy_Ux_Vy); 
 
  double Hyy_Vy[8] = {0.0}; 
  double Hyy_Vy_Uy[8] = {0.0}; 
  binop_mul_2d_ser_p2(Hyy, Vy, Hyy_Vy); 
  binop_mul_2d_ser_p2(Hyy_Vy, Uy, Hyy_Vy_Uy); 
 
  double Hxz_Vx[8] = {0.0}; 
  double Hxz_Vx_Uz[8] = {0.0}; 
  binop_mul_2d_ser_p2(Hxz, Vx, Hxz_Vx); 
  binop_mul_2d_ser_p2(Hxz_Vx, Uz, Hxz_Vx_Uz); 
 
  double Hxz_Ux[8] = {0.0}; 
  double Hxz_Ux_Vz[8] = {0.0}; 
  binop_mul_2d_ser_p2(Hxz, Ux, Hxz_Ux); 
  binop_mul_2d_ser_p2(Hxz_Ux, Vz, Hxz_Ux_Vz); 
 
  double Hyz_Vy[8] = {0.0}; 
  double Hyz_Vy_Uz[8] = {0.0}; 
  binop_mul_2d_ser_p2(Hyz, Vy, Hyz_Vy); 
  binop_mul_2d_ser_p2(Hyz_Vy, Uz, Hyz_Vy_Uz); 
 
  double Hyz_Uy[8] = {0.0}; 
  double Hyz_Uy_Vz[8] = {0.0}; 
  binop_mul_2d_ser_p2(Hyz, Uy, Hyz_Uy); 
  binop_mul_2d_ser_p2(Hyz_Uy, Vz, Hyz_Uy_Vz); 
 
  double Hzz_Vz[8] = {0.0}; 
  double Hzz_Vz_Uz[8] = {0.0}; 
  binop_mul_2d_ser_p2(Hzz, Vz, Hzz_Vz); 
  binop_mul_2d_ser_p2(Hzz_Vz, Uz, Hzz_Vz_Uz); 
 
  v_dot_u[0] = 0.0; 
  v_dot_u[0] += Hxx_Vx_Ux[0]; 
  v_dot_u[0] += (Hxy_Vx_Uy[0] + Hxy_Ux_Vy[0]); 
  v_dot_u[0] +=  Hyy_Vy_Uy[0]; 
  v_dot_u[0] += (Hxz_Vx_Uz[0] + Hxz_Ux_Vz[0]); 
  v_dot_u[0] += (Hyz_Vy_Uz[0] + Hyz_Uy_Vz[0]); 
  v_dot_u[0] +=  Hzz_Vz_Uz[0]; 
  v_dot_u[1] = 0.0; 
  v_dot_u[1] += Hxx_Vx_Ux[1]; 
  v_dot_u[1] += (Hxy_Vx_Uy[1] + Hxy_Ux_Vy[1]); 
  v_dot_u[1] +=  Hyy_Vy_Uy[1]; 
  v_dot_u[1] += (Hxz_Vx_Uz[1] + Hxz_Ux_Vz[1]); 
  v_dot_u[1] += (Hyz_Vy_Uz[1] + Hyz_Uy_Vz[1]); 
  v_dot_u[1] +=  Hzz_Vz_Uz[1]; 
  v_dot_u[2] = 0.0; 
  v_dot_u[2] += Hxx_Vx_Ux[2]; 
  v_dot_u[2] += (Hxy_Vx_Uy[2] + Hxy_Ux_Vy[2]); 
  v_dot_u[2] +=  Hyy_Vy_Uy[2]; 
  v_dot_u[2] += (Hxz_Vx_Uz[2] + Hxz_Ux_Vz[2]); 
  v_dot_u[2] += (Hyz_Vy_Uz[2] + Hyz_Uy_Vz[2]); 
  v_dot_u[2] +=  Hzz_Vz_Uz[2]; 
  v_dot_u[3] = 0.0; 
  v_dot_u[3] += Hxx_Vx_Ux[3]; 
  v_dot_u[3] += (Hxy_Vx_Uy[3] + Hxy_Ux_Vy[3]); 
  v_dot_u[3] +=  Hyy_Vy_Uy[3]; 
  v_dot_u[3] += (Hxz_Vx_Uz[3] + Hxz_Ux_Vz[3]); 
  v_dot_u[3] += (Hyz_Vy_Uz[3] + Hyz_Uy_Vz[3]); 
  v_dot_u[3] +=  Hzz_Vz_Uz[3]; 
  v_dot_u[4] = 0.0; 
  v_dot_u[4] += Hxx_Vx_Ux[4]; 
  v_dot_u[4] += (Hxy_Vx_Uy[4] + Hxy_Ux_Vy[4]); 
  v_dot_u[4] +=  Hyy_Vy_Uy[4]; 
  v_dot_u[4] += (Hxz_Vx_Uz[4] + Hxz_Ux_Vz[4]); 
  v_dot_u[4] += (Hyz_Vy_Uz[4] + Hyz_Uy_Vz[4]); 
  v_dot_u[4] +=  Hzz_Vz_Uz[4]; 
  v_dot_u[5] = 0.0; 
  v_dot_u[5] += Hxx_Vx_Ux[5]; 
  v_dot_u[5] += (Hxy_Vx_Uy[5] + Hxy_Ux_Vy[5]); 
  v_dot_u[5] +=  Hyy_Vy_Uy[5]; 
  v_dot_u[5] += (Hxz_Vx_Uz[5] + Hxz_Ux_Vz[5]); 
  v_dot_u[5] += (Hyz_Vy_Uz[5] + Hyz_Uy_Vz[5]); 
  v_dot_u[5] +=  Hzz_Vz_Uz[5]; 
  v_dot_u[6] = 0.0; 
  v_dot_u[6] += Hxx_Vx_Ux[6]; 
  v_dot_u[6] += (Hxy_Vx_Uy[6] + Hxy_Ux_Vy[6]); 
  v_dot_u[6] +=  Hyy_Vy_Uy[6]; 
  v_dot_u[6] += (Hxz_Vx_Uz[6] + Hxz_Ux_Vz[6]); 
  v_dot_u[6] += (Hyz_Vy_Uz[6] + Hyz_Uy_Vz[6]); 
  v_dot_u[6] +=  Hzz_Vz_Uz[6]; 
  v_dot_u[7] = 0.0; 
  v_dot_u[7] += Hxx_Vx_Ux[7]; 
  v_dot_u[7] += (Hxy_Vx_Uy[7] + Hxy_Ux_Vy[7]); 
  v_dot_u[7] +=  Hyy_Vy_Uy[7]; 
  v_dot_u[7] += (Hxz_Vx_Uz[7] + Hxz_Ux_Vz[7]); 
  v_dot_u[7] += (Hyz_Vy_Uz[7] + Hyz_Uy_Vz[7]); 
  v_dot_u[7] +=  Hzz_Vz_Uz[7]; 
 
} 
