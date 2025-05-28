#include <gkyl_mat.h> 
#include <gkyl_canonical_pb_gr_Gamma_kernels.h> 
#include <gkyl_canonical_pb_kernels.h>  
#include <gkyl_basis_ser_1x_p2_sqrt.h> 
#include <gkyl_basis_ser_1x_p1_sqrt.h> 
GKYL_CU_DH void gr_vars_n_copy_1x3v_ser_p2(int count, const double *h_ij, struct gkyl_nmat *x, const double *M0, double* GKYL_RESTRICT n) 
{ 
  // count: integer to indicate which matrix being fetched. 
  // h_ij(_inv):         Input volume expansion of the metric tensor (could be covariant or contravaraint depending on use).
  //                   [Hxx, Hxy, Hxz, 
  //                     - , Hyy, Hyz, 
  //                     - ,  - , Hzz] 
  // x:     Input solution vector. 
  // M0:    Lab frame density = Gamma*n.
  // n:     Rest-frame density computed as Gamma_inv*M0 where Gamma_inv = sqrt(1 - |V_drift|^2). 
 
  double V[9] = {0.0}; 
  struct gkyl_mat x0 = gkyl_nmat_get(x, count+0); 
  double V_0[3] = {0.0}; 
  V[0] = gkyl_mat_get(&x0,0,0);   V_0[0] = gkyl_mat_get(&x0,0,0); 
  V[1] = gkyl_mat_get(&x0,1,0);   V_0[1] = gkyl_mat_get(&x0,1,0); 
  V[2] = gkyl_mat_get(&x0,2,0);   V_0[2] = gkyl_mat_get(&x0,2,0); 
 
  struct gkyl_mat x1 = gkyl_nmat_get(x, count+1); 
  double V_1[3] = {0.0}; 
  V[3] = gkyl_mat_get(&x1,0,0);   V_1[0] = gkyl_mat_get(&x1,0,0); 
  V[4] = gkyl_mat_get(&x1,1,0);   V_1[1] = gkyl_mat_get(&x1,1,0); 
  V[5] = gkyl_mat_get(&x1,2,0);   V_1[2] = gkyl_mat_get(&x1,2,0); 
 
  struct gkyl_mat x2 = gkyl_nmat_get(x, count+2); 
  double V_2[3] = {0.0}; 
  V[6] = gkyl_mat_get(&x2,0,0);   V_2[0] = gkyl_mat_get(&x2,0,0); 
  V[7] = gkyl_mat_get(&x2,1,0);   V_2[1] = gkyl_mat_get(&x2,1,0); 
  V[8] = gkyl_mat_get(&x2,2,0);   V_2[2] = gkyl_mat_get(&x2,2,0); 
 
  double V_sq[3] = {0.0}; 
  canonical_pb_vars_util_1x3v_ser_p2(h_ij, V, V, V_sq); 
 
  double Gamma2_inv[3] = {0.0}; 
  Gamma2_inv[0] = 1.414213562373095-1.0*V_sq[0]; 
  Gamma2_inv[1] = -1.0*V_sq[1]; 
  Gamma2_inv[2] = -1.0*V_sq[2]; 

  int cell_avg = 0;
  if (0.6324555320336759*Gamma2_inv[2]-0.9486832980505137*Gamma2_inv[1]+0.7071067811865475*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if (0.7071067811865475*Gamma2_inv[0]-0.7905694150420947*Gamma2_inv[2] < 0.0) cell_avg = 1; 
  if (0.6324555320336759*Gamma2_inv[2]+0.9486832980505137*Gamma2_inv[1]+0.7071067811865475*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  const double *Hxx = &h_ij[0]; 
  const double *Hxy = &h_ij[3]; 
  const double *Hxz = &h_ij[6]; 
  const double *Hyy = &h_ij[9]; 
  const double *Hyz = &h_ij[12]; 
  const double *Hzz = &h_ij[15]; 

  if (cell_avg) { 
    double Gamma2_inv_lobatto[2] = {0.0}; 
    double Gamma2_inv_p1[2] = {0.0}; 
    double Gamma_inv_p1[2] = {0.0}; 
    double V0_quad = 0.0; 
    double hxx_quad = 0.0; 
    double V1_quad = 0.0; 
    double hxy_quad = 0.0; 
    double hyy_quad = 0.0; 
    double V2_quad = 0.0; 
    double hxz_quad = 0.0; 
    double hyz_quad = 0.0; 
    double hzz_quad = 0.0; 

    V0_quad = 1.58113883008419*V_0[2]-1.224744871391589*V_0[1]+0.7071067811865475*V_0[0]; 
    V1_quad = 1.58113883008419*V_1[2]-1.224744871391589*V_1[1]+0.7071067811865475*V_1[0]; 
    V2_quad = 1.58113883008419*V_2[2]-1.224744871391589*V_2[1]+0.7071067811865475*V_2[0]; 
    hxx_quad = 1.58113883008419*Hxx[2]-1.224744871391589*Hxx[1]+0.7071067811865475*Hxx[0]; 
    hxy_quad = 1.58113883008419*Hxy[2]-1.224744871391589*Hxy[1]+0.7071067811865475*Hxy[0]; 
    hxz_quad = 1.58113883008419*Hxz[2]-1.224744871391589*Hxz[1]+0.7071067811865475*Hxz[0]; 
    hyy_quad = 1.58113883008419*Hyy[2]-1.224744871391589*Hyy[1]+0.7071067811865475*Hyy[0]; 
    hyz_quad = 1.58113883008419*Hyz[2]-1.224744871391589*Hyz[1]+0.7071067811865475*Hyz[0]; 
    hzz_quad = 1.58113883008419*Hzz[2]-1.224744871391589*Hzz[1]+0.7071067811865475*Hzz[0]; 
    Gamma2_inv_lobatto[0] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad - 2.0*hyz_quad*V1_quad*V2_quad - hzz_quad*V2_quad*V2_quad - 2.0*hxz_quad*V0_quad*V2_quad; 
    if (Gamma2_inv_lobatto[0] < 0.0) Gamma2_inv_lobatto[0] = 1.0e-16; 

    V0_quad = 1.58113883008419*V_0[2]+1.224744871391589*V_0[1]+0.7071067811865475*V_0[0]; 
    V1_quad = 1.58113883008419*V_1[2]+1.224744871391589*V_1[1]+0.7071067811865475*V_1[0]; 
    V2_quad = 1.58113883008419*V_2[2]+1.224744871391589*V_2[1]+0.7071067811865475*V_2[0]; 
    hxx_quad = 1.58113883008419*Hxx[2]+1.224744871391589*Hxx[1]+0.7071067811865475*Hxx[0]; 
    hxy_quad = 1.58113883008419*Hxy[2]+1.224744871391589*Hxy[1]+0.7071067811865475*Hxy[0]; 
    hxz_quad = 1.58113883008419*Hxz[2]+1.224744871391589*Hxz[1]+0.7071067811865475*Hxz[0]; 
    hyy_quad = 1.58113883008419*Hyy[2]+1.224744871391589*Hyy[1]+0.7071067811865475*Hyy[0]; 
    hyz_quad = 1.58113883008419*Hyz[2]+1.224744871391589*Hyz[1]+0.7071067811865475*Hyz[0]; 
    hzz_quad = 1.58113883008419*Hzz[2]+1.224744871391589*Hzz[1]+0.7071067811865475*Hzz[0]; 
    Gamma2_inv_lobatto[1] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad - 2.0*hyz_quad*V1_quad*V2_quad - hzz_quad*V2_quad*V2_quad - 2.0*hxz_quad*V0_quad*V2_quad; 
    if (Gamma2_inv_lobatto[1] < 0.0) Gamma2_inv_lobatto[1] = 1.0e-16; 

    Gamma2_inv_p1[0] = 0.7071067811865475*Gamma2_inv_lobatto[1]+0.7071067811865475*Gamma2_inv_lobatto[0]; 
    Gamma2_inv_p1[1] = 0.408248290463863*Gamma2_inv_lobatto[1]-0.408248290463863*Gamma2_inv_lobatto[0]; 
    ser_1x_p1_sqrt(Gamma2_inv_p1, Gamma_inv_p1); 
    n[0] = 0.7071067811865475*Gamma_inv_p1[1]*M0[1]+0.7071067811865475*Gamma_inv_p1[0]*M0[0]; 
    n[1] = 0.6324555320336759*Gamma_inv_p1[1]*M0[2]+0.7071067811865475*Gamma_inv_p1[0]*M0[1]+0.7071067811865475*M0[0]*Gamma_inv_p1[1]; 
    n[2] = 0.7071067811865475*Gamma_inv_p1[0]*M0[2]+0.6324555320336759*Gamma_inv_p1[1]*M0[1]; 
  } 
  else { 
    double Gamma_inv[3] = {0.0}; 
    ser_1x_p2_sqrt(Gamma2_inv, Gamma_inv); 
    n[0] = 0.7071067811865475*Gamma_inv[2]*M0[2]+0.7071067811865475*Gamma_inv[1]*M0[1]+0.7071067811865475*Gamma_inv[0]*M0[0]; 
    n[1] = 0.6324555320336759*Gamma_inv[1]*M0[2]+0.6324555320336759*M0[1]*Gamma_inv[2]+0.7071067811865475*Gamma_inv[0]*M0[1]+0.7071067811865475*M0[0]*Gamma_inv[1]; 
    n[2] = 0.4517539514526256*Gamma_inv[2]*M0[2]+0.7071067811865475*Gamma_inv[0]*M0[2]+0.7071067811865475*M0[0]*Gamma_inv[2]+0.6324555320336759*Gamma_inv[1]*M0[1]; 
  } 

} 
 
