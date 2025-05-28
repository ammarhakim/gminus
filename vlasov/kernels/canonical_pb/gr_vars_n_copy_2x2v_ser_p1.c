#include <gkyl_mat.h> 
#include <gkyl_canonical_pb_gr_Gamma_kernels.h> 
#include <gkyl_canonical_pb_kernels.h>  
#include <gkyl_basis_ser_2x_p1_sqrt.h> 
GKYL_CU_DH void gr_vars_n_copy_2x2v_ser_p1(int count, const double *h_ij, struct gkyl_nmat *x, const double *M0, double* GKYL_RESTRICT n) 
{ 
  // count: integer to indicate which matrix being fetched. 
  // h_ij(_inv):         Input volume expansion of the metric tensor (could be covariant or contravaraint depending on use).
  //                   [Hxx, Hxy, Hxz, 
  //                     - , Hyy, Hyz, 
  //                     - ,  - , Hzz] 
  // x:     Input solution vector. 
  // M0:    Lab frame density = Gamma*n.
  // n:     Rest-frame density computed as Gamma_inv*M0 where Gamma_inv = sqrt(1 - |V_drift|^2). 
 
  double V[8] = {0.0}; 
  struct gkyl_mat x0 = gkyl_nmat_get(x, count+0); 
  double V_0[4] = {0.0}; 
  V[0] = gkyl_mat_get(&x0,0,0);   V_0[0] = gkyl_mat_get(&x0,0,0); 
  V[1] = gkyl_mat_get(&x0,1,0);   V_0[1] = gkyl_mat_get(&x0,1,0); 
  V[2] = gkyl_mat_get(&x0,2,0);   V_0[2] = gkyl_mat_get(&x0,2,0); 
  V[3] = gkyl_mat_get(&x0,3,0);   V_0[3] = gkyl_mat_get(&x0,3,0); 
 
  struct gkyl_mat x1 = gkyl_nmat_get(x, count+1); 
  double V_1[4] = {0.0}; 
  V[4] = gkyl_mat_get(&x1,0,0);   V_1[0] = gkyl_mat_get(&x1,0,0); 
  V[5] = gkyl_mat_get(&x1,1,0);   V_1[1] = gkyl_mat_get(&x1,1,0); 
  V[6] = gkyl_mat_get(&x1,2,0);   V_1[2] = gkyl_mat_get(&x1,2,0); 
  V[7] = gkyl_mat_get(&x1,3,0);   V_1[3] = gkyl_mat_get(&x1,3,0); 
 
  double V_sq[4] = {0.0}; 
  canonical_pb_vars_util_2x2v_ser_p1(h_ij, V, V, V_sq); 
 
  double Gamma2_inv[4] = {0.0}; 
  Gamma2_inv[0] = 2.0-1.0*V_sq[0]; 
  Gamma2_inv[1] = -1.0*V_sq[1]; 
  Gamma2_inv[2] = -1.0*V_sq[2]; 
  Gamma2_inv[3] = -1.0*V_sq[3]; 

  int cell_avg = 0;
  if (0.5*Gamma2_inv[3]-0.5*Gamma2_inv[2]-0.5*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if ((-0.5*Gamma2_inv[3])+0.5*Gamma2_inv[2]-0.5*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if ((-0.5*Gamma2_inv[3])-0.5*Gamma2_inv[2]+0.5*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if (0.5*Gamma2_inv[3]+0.5*Gamma2_inv[2]+0.5*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  const double *Hxx = &h_ij[0]; 
  const double *Hxy = &h_ij[4]; 
  const double *Hyy = &h_ij[8]; 

  if (cell_avg) { 
    double Gamma2_inv_lobatto[4] = {0.0}; 
    double Gamma2_inv_p1[4] = {0.0}; 
    double Gamma_inv_p1[4] = {0.0}; 
    double V0_quad = 0.0; 
    double hxx_quad = 0.0; 
    double V1_quad = 0.0; 
    double hxy_quad = 0.0; 
    double hyy_quad = 0.0; 

    V0_quad = 1.5*V_0[3]-0.8660254037844386*V_0[2]-0.8660254037844386*V_0[1]+0.5*V_0[0]; 
    V1_quad = 1.5*V_1[3]-0.8660254037844386*V_1[2]-0.8660254037844386*V_1[1]+0.5*V_1[0]; 
    hxx_quad = 1.5*Hxx[3]-0.8660254037844386*Hxx[2]-0.8660254037844386*Hxx[1]+0.5*Hxx[0]; 
    hxy_quad = 1.5*Hxy[3]-0.8660254037844386*Hxy[2]-0.8660254037844386*Hxy[1]+0.5*Hxy[0]; 
    hyy_quad = 1.5*Hyy[3]-0.8660254037844386*Hyy[2]-0.8660254037844386*Hyy[1]+0.5*Hyy[0]; 
    Gamma2_inv_lobatto[0] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad; 
    if (Gamma2_inv_lobatto[0] < 0.0) Gamma2_inv_lobatto[0] = 1.0e-16; 

    V0_quad = (-1.5*V_0[3])-0.8660254037844386*V_0[2]+0.8660254037844386*V_0[1]+0.5*V_0[0]; 
    V1_quad = (-1.5*V_1[3])-0.8660254037844386*V_1[2]+0.8660254037844386*V_1[1]+0.5*V_1[0]; 
    hxx_quad = (-1.5*Hxx[3])-0.8660254037844386*Hxx[2]+0.8660254037844386*Hxx[1]+0.5*Hxx[0]; 
    hxy_quad = (-1.5*Hxy[3])-0.8660254037844386*Hxy[2]+0.8660254037844386*Hxy[1]+0.5*Hxy[0]; 
    hyy_quad = (-1.5*Hyy[3])-0.8660254037844386*Hyy[2]+0.8660254037844386*Hyy[1]+0.5*Hyy[0]; 
    Gamma2_inv_lobatto[1] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad; 
    if (Gamma2_inv_lobatto[1] < 0.0) Gamma2_inv_lobatto[1] = 1.0e-16; 

    V0_quad = (-1.5*V_0[3])+0.8660254037844386*V_0[2]-0.8660254037844386*V_0[1]+0.5*V_0[0]; 
    V1_quad = (-1.5*V_1[3])+0.8660254037844386*V_1[2]-0.8660254037844386*V_1[1]+0.5*V_1[0]; 
    hxx_quad = (-1.5*Hxx[3])+0.8660254037844386*Hxx[2]-0.8660254037844386*Hxx[1]+0.5*Hxx[0]; 
    hxy_quad = (-1.5*Hxy[3])+0.8660254037844386*Hxy[2]-0.8660254037844386*Hxy[1]+0.5*Hxy[0]; 
    hyy_quad = (-1.5*Hyy[3])+0.8660254037844386*Hyy[2]-0.8660254037844386*Hyy[1]+0.5*Hyy[0]; 
    Gamma2_inv_lobatto[2] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad; 
    if (Gamma2_inv_lobatto[2] < 0.0) Gamma2_inv_lobatto[2] = 1.0e-16; 

    V0_quad = 1.5*V_0[3]+0.8660254037844386*V_0[2]+0.8660254037844386*V_0[1]+0.5*V_0[0]; 
    V1_quad = 1.5*V_1[3]+0.8660254037844386*V_1[2]+0.8660254037844386*V_1[1]+0.5*V_1[0]; 
    hxx_quad = 1.5*Hxx[3]+0.8660254037844386*Hxx[2]+0.8660254037844386*Hxx[1]+0.5*Hxx[0]; 
    hxy_quad = 1.5*Hxy[3]+0.8660254037844386*Hxy[2]+0.8660254037844386*Hxy[1]+0.5*Hxy[0]; 
    hyy_quad = 1.5*Hyy[3]+0.8660254037844386*Hyy[2]+0.8660254037844386*Hyy[1]+0.5*Hyy[0]; 
    Gamma2_inv_lobatto[3] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad; 
    if (Gamma2_inv_lobatto[3] < 0.0) Gamma2_inv_lobatto[3] = 1.0e-16; 

    Gamma2_inv_p1[0] = 0.5*Gamma2_inv_lobatto[3]+0.5*Gamma2_inv_lobatto[2]+0.5*Gamma2_inv_lobatto[1]+0.5*Gamma2_inv_lobatto[0]; 
    Gamma2_inv_p1[1] = 0.2886751345948129*Gamma2_inv_lobatto[3]-0.2886751345948129*Gamma2_inv_lobatto[2]+0.2886751345948129*Gamma2_inv_lobatto[1]-0.2886751345948129*Gamma2_inv_lobatto[0]; 
    Gamma2_inv_p1[2] = 0.2886751345948129*Gamma2_inv_lobatto[3]+0.2886751345948129*Gamma2_inv_lobatto[2]-0.2886751345948129*Gamma2_inv_lobatto[1]-0.2886751345948129*Gamma2_inv_lobatto[0]; 
    Gamma2_inv_p1[3] = 0.1666666666666667*Gamma2_inv_lobatto[3]-0.1666666666666667*Gamma2_inv_lobatto[2]-0.1666666666666667*Gamma2_inv_lobatto[1]+0.1666666666666667*Gamma2_inv_lobatto[0]; 
    ser_2x_p1_sqrt(Gamma2_inv_p1, Gamma_inv_p1); 
    n[0] = 0.5*Gamma_inv_p1[3]*M0[3]+0.5*Gamma_inv_p1[2]*M0[2]+0.5*Gamma_inv_p1[1]*M0[1]+0.5*Gamma_inv_p1[0]*M0[0]; 
    n[1] = 0.5*Gamma_inv_p1[2]*M0[3]+0.5*M0[2]*Gamma_inv_p1[3]+0.5*Gamma_inv_p1[0]*M0[1]+0.5*M0[0]*Gamma_inv_p1[1]; 
    n[2] = 0.5*Gamma_inv_p1[1]*M0[3]+0.5*M0[1]*Gamma_inv_p1[3]+0.5*Gamma_inv_p1[0]*M0[2]+0.5*M0[0]*Gamma_inv_p1[2]; 
    n[3] = 0.5*Gamma_inv_p1[0]*M0[3]+0.5*M0[0]*Gamma_inv_p1[3]+0.5*Gamma_inv_p1[1]*M0[2]+0.5*M0[1]*Gamma_inv_p1[2]; 
  } 
  else { 
    double Gamma_inv[4] = {0.0}; 
    ser_2x_p1_sqrt(Gamma2_inv, Gamma_inv); 
    n[0] = 0.5*Gamma_inv[3]*M0[3]+0.5*Gamma_inv[2]*M0[2]+0.5*Gamma_inv[1]*M0[1]+0.5*Gamma_inv[0]*M0[0]; 
    n[1] = 0.5*Gamma_inv[2]*M0[3]+0.5*M0[2]*Gamma_inv[3]+0.5*Gamma_inv[0]*M0[1]+0.5*M0[0]*Gamma_inv[1]; 
    n[2] = 0.5*Gamma_inv[1]*M0[3]+0.5*M0[1]*Gamma_inv[3]+0.5*Gamma_inv[0]*M0[2]+0.5*M0[0]*Gamma_inv[2]; 
    n[3] = 0.5*Gamma_inv[0]*M0[3]+0.5*M0[0]*Gamma_inv[3]+0.5*Gamma_inv[1]*M0[2]+0.5*M0[1]*Gamma_inv[2]; 
  } 

} 
 
