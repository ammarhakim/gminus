#include <gkyl_mat.h> 
#include <gkyl_canonical_pb_gr_Gamma_kernels.h> 
#include <gkyl_canonical_pb_kernels.h>  
#include <gkyl_basis_ser_2x_p2_sqrt.h> 
#include <gkyl_basis_ser_2x_p1_sqrt.h> 
GKYL_CU_DH void gr_vars_n_copy_2x3v_ser_p2(int count, const double *h_ij, struct gkyl_nmat *x, const double *M0, double* GKYL_RESTRICT n) 
{ 
  // count: integer to indicate which matrix being fetched. 
  // h_ij(_inv):         Input volume expansion of the metric tensor (could be covariant or contravaraint depending on use).
  //                   [Hxx, Hxy, Hxz, 
  //                     - , Hyy, Hyz, 
  //                     - ,  - , Hzz] 
  // x:     Input solution vector. 
  // M0:    Lab frame density = Gamma*n.
  // n:     Rest-frame density computed as Gamma_inv*M0 where Gamma_inv = sqrt(1 - |V_drift|^2). 
 
  double V[24] = {0.0}; 
  struct gkyl_mat x0 = gkyl_nmat_get(x, count+0); 
  double V_0[8] = {0.0}; 
  V[0] = gkyl_mat_get(&x0,0,0);   V_0[0] = gkyl_mat_get(&x0,0,0); 
  V[1] = gkyl_mat_get(&x0,1,0);   V_0[1] = gkyl_mat_get(&x0,1,0); 
  V[2] = gkyl_mat_get(&x0,2,0);   V_0[2] = gkyl_mat_get(&x0,2,0); 
  V[3] = gkyl_mat_get(&x0,3,0);   V_0[3] = gkyl_mat_get(&x0,3,0); 
  V[4] = gkyl_mat_get(&x0,4,0);   V_0[4] = gkyl_mat_get(&x0,4,0); 
  V[5] = gkyl_mat_get(&x0,5,0);   V_0[5] = gkyl_mat_get(&x0,5,0); 
  V[6] = gkyl_mat_get(&x0,6,0);   V_0[6] = gkyl_mat_get(&x0,6,0); 
  V[7] = gkyl_mat_get(&x0,7,0);   V_0[7] = gkyl_mat_get(&x0,7,0); 
 
  struct gkyl_mat x1 = gkyl_nmat_get(x, count+1); 
  double V_1[8] = {0.0}; 
  V[8] = gkyl_mat_get(&x1,0,0);   V_1[0] = gkyl_mat_get(&x1,0,0); 
  V[9] = gkyl_mat_get(&x1,1,0);   V_1[1] = gkyl_mat_get(&x1,1,0); 
  V[10] = gkyl_mat_get(&x1,2,0);   V_1[2] = gkyl_mat_get(&x1,2,0); 
  V[11] = gkyl_mat_get(&x1,3,0);   V_1[3] = gkyl_mat_get(&x1,3,0); 
  V[12] = gkyl_mat_get(&x1,4,0);   V_1[4] = gkyl_mat_get(&x1,4,0); 
  V[13] = gkyl_mat_get(&x1,5,0);   V_1[5] = gkyl_mat_get(&x1,5,0); 
  V[14] = gkyl_mat_get(&x1,6,0);   V_1[6] = gkyl_mat_get(&x1,6,0); 
  V[15] = gkyl_mat_get(&x1,7,0);   V_1[7] = gkyl_mat_get(&x1,7,0); 
 
  struct gkyl_mat x2 = gkyl_nmat_get(x, count+2); 
  double V_2[8] = {0.0}; 
  V[16] = gkyl_mat_get(&x2,0,0);   V_2[0] = gkyl_mat_get(&x2,0,0); 
  V[17] = gkyl_mat_get(&x2,1,0);   V_2[1] = gkyl_mat_get(&x2,1,0); 
  V[18] = gkyl_mat_get(&x2,2,0);   V_2[2] = gkyl_mat_get(&x2,2,0); 
  V[19] = gkyl_mat_get(&x2,3,0);   V_2[3] = gkyl_mat_get(&x2,3,0); 
  V[20] = gkyl_mat_get(&x2,4,0);   V_2[4] = gkyl_mat_get(&x2,4,0); 
  V[21] = gkyl_mat_get(&x2,5,0);   V_2[5] = gkyl_mat_get(&x2,5,0); 
  V[22] = gkyl_mat_get(&x2,6,0);   V_2[6] = gkyl_mat_get(&x2,6,0); 
  V[23] = gkyl_mat_get(&x2,7,0);   V_2[7] = gkyl_mat_get(&x2,7,0); 
 
  double V_sq[8] = {0.0}; 
  canonical_pb_vars_util_2x3v_ser_p2(h_ij, V, V, V_sq); 
 
  double Gamma2_inv[8] = {0.0}; 
  Gamma2_inv[0] = 2.0-1.0*V_sq[0]; 
  Gamma2_inv[1] = -1.0*V_sq[1]; 
  Gamma2_inv[2] = -1.0*V_sq[2]; 
  Gamma2_inv[3] = -1.0*V_sq[3]; 
  Gamma2_inv[4] = -1.0*V_sq[4]; 
  Gamma2_inv[5] = -1.0*V_sq[5]; 
  Gamma2_inv[6] = -1.0*V_sq[6]; 
  Gamma2_inv[7] = -1.0*V_sq[7]; 

  int cell_avg = 0;
  if ((-0.5999999999999995*Gamma2_inv[7])-0.5999999999999999*Gamma2_inv[6]+0.4472135954999579*Gamma2_inv[5]+0.4472135954999579*Gamma2_inv[4]+0.9*Gamma2_inv[3]-0.6708203932499369*Gamma2_inv[2]-0.6708203932499369*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if (0.75*Gamma2_inv[7]-0.5590169943749475*Gamma2_inv[5]+0.4472135954999579*Gamma2_inv[4]-0.6708203932499369*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if ((-0.5999999999999995*Gamma2_inv[7])+0.5999999999999999*Gamma2_inv[6]+0.4472135954999579*Gamma2_inv[5]+0.4472135954999579*Gamma2_inv[4]-0.9*Gamma2_inv[3]+0.6708203932499369*Gamma2_inv[2]-0.6708203932499369*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if (0.75*Gamma2_inv[6]+0.4472135954999579*Gamma2_inv[5]-0.5590169943749475*Gamma2_inv[4]-0.6708203932499369*Gamma2_inv[2]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if ((-0.5590169943749475*Gamma2_inv[5])-0.5590169943749475*Gamma2_inv[4]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if ((-0.75*Gamma2_inv[6])+0.4472135954999579*Gamma2_inv[5]-0.5590169943749475*Gamma2_inv[4]+0.6708203932499369*Gamma2_inv[2]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if (0.5999999999999995*Gamma2_inv[7]-0.5999999999999999*Gamma2_inv[6]+0.4472135954999579*Gamma2_inv[5]+0.4472135954999579*Gamma2_inv[4]-0.9*Gamma2_inv[3]-0.6708203932499369*Gamma2_inv[2]+0.6708203932499369*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if ((-0.75*Gamma2_inv[7])-0.5590169943749475*Gamma2_inv[5]+0.4472135954999579*Gamma2_inv[4]+0.6708203932499369*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  if (0.5999999999999995*Gamma2_inv[7]+0.5999999999999999*Gamma2_inv[6]+0.4472135954999579*Gamma2_inv[5]+0.4472135954999579*Gamma2_inv[4]+0.9*Gamma2_inv[3]+0.6708203932499369*Gamma2_inv[2]+0.6708203932499369*Gamma2_inv[1]+0.5*Gamma2_inv[0] < 0.0) cell_avg = 1; 
  const double *Hxx = &h_ij[0]; 
  const double *Hxy = &h_ij[8]; 
  const double *Hxz = &h_ij[16]; 
  const double *Hyy = &h_ij[24]; 
  const double *Hyz = &h_ij[32]; 
  const double *Hzz = &h_ij[40]; 

  if (cell_avg) { 
    double Gamma2_inv_lobatto[4] = {0.0}; 
    double Gamma2_inv_p1[4] = {0.0}; 
    double Gamma_inv_p1[4] = {0.0}; 
    double V0_quad = 0.0; 
    double hxx_quad = 0.0; 
    double V1_quad = 0.0; 
    double hxy_quad = 0.0; 
    double hyy_quad = 0.0; 
    double V2_quad = 0.0; 
    double hxz_quad = 0.0; 
    double hyz_quad = 0.0; 
    double hzz_quad = 0.0; 

    V0_quad = (-1.936491673103709*V_0[7])-1.936491673103709*V_0[6]+1.118033988749895*V_0[5]+1.118033988749895*V_0[4]+1.5*V_0[3]-0.8660254037844386*V_0[2]-0.8660254037844386*V_0[1]+0.5*V_0[0]; 
    V1_quad = (-1.936491673103709*V_1[7])-1.936491673103709*V_1[6]+1.118033988749895*V_1[5]+1.118033988749895*V_1[4]+1.5*V_1[3]-0.8660254037844386*V_1[2]-0.8660254037844386*V_1[1]+0.5*V_1[0]; 
    V2_quad = (-1.936491673103709*V_2[7])-1.936491673103709*V_2[6]+1.118033988749895*V_2[5]+1.118033988749895*V_2[4]+1.5*V_2[3]-0.8660254037844386*V_2[2]-0.8660254037844386*V_2[1]+0.5*V_2[0]; 
    hxx_quad = (-1.936491673103709*Hxx[7])-1.936491673103709*Hxx[6]+1.118033988749895*Hxx[5]+1.118033988749895*Hxx[4]+1.5*Hxx[3]-0.8660254037844386*Hxx[2]-0.8660254037844386*Hxx[1]+0.5*Hxx[0]; 
    hxy_quad = (-1.936491673103709*Hxy[7])-1.936491673103709*Hxy[6]+1.118033988749895*Hxy[5]+1.118033988749895*Hxy[4]+1.5*Hxy[3]-0.8660254037844386*Hxy[2]-0.8660254037844386*Hxy[1]+0.5*Hxy[0]; 
    hxz_quad = (-1.936491673103709*Hxz[7])-1.936491673103709*Hxz[6]+1.118033988749895*Hxz[5]+1.118033988749895*Hxz[4]+1.5*Hxz[3]-0.8660254037844386*Hxz[2]-0.8660254037844386*Hxz[1]+0.5*Hxz[0]; 
    hyy_quad = (-1.936491673103709*Hyy[7])-1.936491673103709*Hyy[6]+1.118033988749895*Hyy[5]+1.118033988749895*Hyy[4]+1.5*Hyy[3]-0.8660254037844386*Hyy[2]-0.8660254037844386*Hyy[1]+0.5*Hyy[0]; 
    hyz_quad = (-1.936491673103709*Hyz[7])-1.936491673103709*Hyz[6]+1.118033988749895*Hyz[5]+1.118033988749895*Hyz[4]+1.5*Hyz[3]-0.8660254037844386*Hyz[2]-0.8660254037844386*Hyz[1]+0.5*Hyz[0]; 
    hzz_quad = (-1.936491673103709*Hzz[7])-1.936491673103709*Hzz[6]+1.118033988749895*Hzz[5]+1.118033988749895*Hzz[4]+1.5*Hzz[3]-0.8660254037844386*Hzz[2]-0.8660254037844386*Hzz[1]+0.5*Hzz[0]; 
    Gamma2_inv_lobatto[0] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad - 2.0*hyz_quad*V1_quad*V2_quad - hzz_quad*V2_quad*V2_quad - 2.0*hxz_quad*V0_quad*V2_quad; 
    if (Gamma2_inv_lobatto[0] < 0.0) Gamma2_inv_lobatto[0] = 1.0e-16; 

    V0_quad = 1.936491673103709*V_0[7]-1.936491673103709*V_0[6]+1.118033988749895*V_0[5]+1.118033988749895*V_0[4]-1.5*V_0[3]-0.8660254037844386*V_0[2]+0.8660254037844386*V_0[1]+0.5*V_0[0]; 
    V1_quad = 1.936491673103709*V_1[7]-1.936491673103709*V_1[6]+1.118033988749895*V_1[5]+1.118033988749895*V_1[4]-1.5*V_1[3]-0.8660254037844386*V_1[2]+0.8660254037844386*V_1[1]+0.5*V_1[0]; 
    V2_quad = 1.936491673103709*V_2[7]-1.936491673103709*V_2[6]+1.118033988749895*V_2[5]+1.118033988749895*V_2[4]-1.5*V_2[3]-0.8660254037844386*V_2[2]+0.8660254037844386*V_2[1]+0.5*V_2[0]; 
    hxx_quad = 1.936491673103709*Hxx[7]-1.936491673103709*Hxx[6]+1.118033988749895*Hxx[5]+1.118033988749895*Hxx[4]-1.5*Hxx[3]-0.8660254037844386*Hxx[2]+0.8660254037844386*Hxx[1]+0.5*Hxx[0]; 
    hxy_quad = 1.936491673103709*Hxy[7]-1.936491673103709*Hxy[6]+1.118033988749895*Hxy[5]+1.118033988749895*Hxy[4]-1.5*Hxy[3]-0.8660254037844386*Hxy[2]+0.8660254037844386*Hxy[1]+0.5*Hxy[0]; 
    hxz_quad = 1.936491673103709*Hxz[7]-1.936491673103709*Hxz[6]+1.118033988749895*Hxz[5]+1.118033988749895*Hxz[4]-1.5*Hxz[3]-0.8660254037844386*Hxz[2]+0.8660254037844386*Hxz[1]+0.5*Hxz[0]; 
    hyy_quad = 1.936491673103709*Hyy[7]-1.936491673103709*Hyy[6]+1.118033988749895*Hyy[5]+1.118033988749895*Hyy[4]-1.5*Hyy[3]-0.8660254037844386*Hyy[2]+0.8660254037844386*Hyy[1]+0.5*Hyy[0]; 
    hyz_quad = 1.936491673103709*Hyz[7]-1.936491673103709*Hyz[6]+1.118033988749895*Hyz[5]+1.118033988749895*Hyz[4]-1.5*Hyz[3]-0.8660254037844386*Hyz[2]+0.8660254037844386*Hyz[1]+0.5*Hyz[0]; 
    hzz_quad = 1.936491673103709*Hzz[7]-1.936491673103709*Hzz[6]+1.118033988749895*Hzz[5]+1.118033988749895*Hzz[4]-1.5*Hzz[3]-0.8660254037844386*Hzz[2]+0.8660254037844386*Hzz[1]+0.5*Hzz[0]; 
    Gamma2_inv_lobatto[1] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad - 2.0*hyz_quad*V1_quad*V2_quad - hzz_quad*V2_quad*V2_quad - 2.0*hxz_quad*V0_quad*V2_quad; 
    if (Gamma2_inv_lobatto[1] < 0.0) Gamma2_inv_lobatto[1] = 1.0e-16; 

    V0_quad = (-1.936491673103709*V_0[7])+1.936491673103709*V_0[6]+1.118033988749895*V_0[5]+1.118033988749895*V_0[4]-1.5*V_0[3]+0.8660254037844386*V_0[2]-0.8660254037844386*V_0[1]+0.5*V_0[0]; 
    V1_quad = (-1.936491673103709*V_1[7])+1.936491673103709*V_1[6]+1.118033988749895*V_1[5]+1.118033988749895*V_1[4]-1.5*V_1[3]+0.8660254037844386*V_1[2]-0.8660254037844386*V_1[1]+0.5*V_1[0]; 
    V2_quad = (-1.936491673103709*V_2[7])+1.936491673103709*V_2[6]+1.118033988749895*V_2[5]+1.118033988749895*V_2[4]-1.5*V_2[3]+0.8660254037844386*V_2[2]-0.8660254037844386*V_2[1]+0.5*V_2[0]; 
    hxx_quad = (-1.936491673103709*Hxx[7])+1.936491673103709*Hxx[6]+1.118033988749895*Hxx[5]+1.118033988749895*Hxx[4]-1.5*Hxx[3]+0.8660254037844386*Hxx[2]-0.8660254037844386*Hxx[1]+0.5*Hxx[0]; 
    hxy_quad = (-1.936491673103709*Hxy[7])+1.936491673103709*Hxy[6]+1.118033988749895*Hxy[5]+1.118033988749895*Hxy[4]-1.5*Hxy[3]+0.8660254037844386*Hxy[2]-0.8660254037844386*Hxy[1]+0.5*Hxy[0]; 
    hxz_quad = (-1.936491673103709*Hxz[7])+1.936491673103709*Hxz[6]+1.118033988749895*Hxz[5]+1.118033988749895*Hxz[4]-1.5*Hxz[3]+0.8660254037844386*Hxz[2]-0.8660254037844386*Hxz[1]+0.5*Hxz[0]; 
    hyy_quad = (-1.936491673103709*Hyy[7])+1.936491673103709*Hyy[6]+1.118033988749895*Hyy[5]+1.118033988749895*Hyy[4]-1.5*Hyy[3]+0.8660254037844386*Hyy[2]-0.8660254037844386*Hyy[1]+0.5*Hyy[0]; 
    hyz_quad = (-1.936491673103709*Hyz[7])+1.936491673103709*Hyz[6]+1.118033988749895*Hyz[5]+1.118033988749895*Hyz[4]-1.5*Hyz[3]+0.8660254037844386*Hyz[2]-0.8660254037844386*Hyz[1]+0.5*Hyz[0]; 
    hzz_quad = (-1.936491673103709*Hzz[7])+1.936491673103709*Hzz[6]+1.118033988749895*Hzz[5]+1.118033988749895*Hzz[4]-1.5*Hzz[3]+0.8660254037844386*Hzz[2]-0.8660254037844386*Hzz[1]+0.5*Hzz[0]; 
    Gamma2_inv_lobatto[2] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad - 2.0*hyz_quad*V1_quad*V2_quad - hzz_quad*V2_quad*V2_quad - 2.0*hxz_quad*V0_quad*V2_quad; 
    if (Gamma2_inv_lobatto[2] < 0.0) Gamma2_inv_lobatto[2] = 1.0e-16; 

    V0_quad = 1.936491673103709*V_0[7]+1.936491673103709*V_0[6]+1.118033988749895*V_0[5]+1.118033988749895*V_0[4]+1.5*V_0[3]+0.8660254037844386*V_0[2]+0.8660254037844386*V_0[1]+0.5*V_0[0]; 
    V1_quad = 1.936491673103709*V_1[7]+1.936491673103709*V_1[6]+1.118033988749895*V_1[5]+1.118033988749895*V_1[4]+1.5*V_1[3]+0.8660254037844386*V_1[2]+0.8660254037844386*V_1[1]+0.5*V_1[0]; 
    V2_quad = 1.936491673103709*V_2[7]+1.936491673103709*V_2[6]+1.118033988749895*V_2[5]+1.118033988749895*V_2[4]+1.5*V_2[3]+0.8660254037844386*V_2[2]+0.8660254037844386*V_2[1]+0.5*V_2[0]; 
    hxx_quad = 1.936491673103709*Hxx[7]+1.936491673103709*Hxx[6]+1.118033988749895*Hxx[5]+1.118033988749895*Hxx[4]+1.5*Hxx[3]+0.8660254037844386*Hxx[2]+0.8660254037844386*Hxx[1]+0.5*Hxx[0]; 
    hxy_quad = 1.936491673103709*Hxy[7]+1.936491673103709*Hxy[6]+1.118033988749895*Hxy[5]+1.118033988749895*Hxy[4]+1.5*Hxy[3]+0.8660254037844386*Hxy[2]+0.8660254037844386*Hxy[1]+0.5*Hxy[0]; 
    hxz_quad = 1.936491673103709*Hxz[7]+1.936491673103709*Hxz[6]+1.118033988749895*Hxz[5]+1.118033988749895*Hxz[4]+1.5*Hxz[3]+0.8660254037844386*Hxz[2]+0.8660254037844386*Hxz[1]+0.5*Hxz[0]; 
    hyy_quad = 1.936491673103709*Hyy[7]+1.936491673103709*Hyy[6]+1.118033988749895*Hyy[5]+1.118033988749895*Hyy[4]+1.5*Hyy[3]+0.8660254037844386*Hyy[2]+0.8660254037844386*Hyy[1]+0.5*Hyy[0]; 
    hyz_quad = 1.936491673103709*Hyz[7]+1.936491673103709*Hyz[6]+1.118033988749895*Hyz[5]+1.118033988749895*Hyz[4]+1.5*Hyz[3]+0.8660254037844386*Hyz[2]+0.8660254037844386*Hyz[1]+0.5*Hyz[0]; 
    hzz_quad = 1.936491673103709*Hzz[7]+1.936491673103709*Hzz[6]+1.118033988749895*Hzz[5]+1.118033988749895*Hzz[4]+1.5*Hzz[3]+0.8660254037844386*Hzz[2]+0.8660254037844386*Hzz[1]+0.5*Hzz[0]; 
    Gamma2_inv_lobatto[3] = 1.0 - hxx_quad*V0_quad*V0_quad - 2.0*hxy_quad*V0_quad*V1_quad - hyy_quad*V1_quad*V1_quad - 2.0*hyz_quad*V1_quad*V2_quad - hzz_quad*V2_quad*V2_quad - 2.0*hxz_quad*V0_quad*V2_quad; 
    if (Gamma2_inv_lobatto[3] < 0.0) Gamma2_inv_lobatto[3] = 1.0e-16; 

    Gamma2_inv_p1[0] = 0.5*Gamma2_inv_lobatto[3]+0.5*Gamma2_inv_lobatto[2]+0.5*Gamma2_inv_lobatto[1]+0.5*Gamma2_inv_lobatto[0]; 
    Gamma2_inv_p1[1] = 0.2886751345948129*Gamma2_inv_lobatto[3]-0.2886751345948129*Gamma2_inv_lobatto[2]+0.2886751345948129*Gamma2_inv_lobatto[1]-0.2886751345948129*Gamma2_inv_lobatto[0]; 
    Gamma2_inv_p1[2] = 0.2886751345948129*Gamma2_inv_lobatto[3]+0.2886751345948129*Gamma2_inv_lobatto[2]-0.2886751345948129*Gamma2_inv_lobatto[1]-0.2886751345948129*Gamma2_inv_lobatto[0]; 
    Gamma2_inv_p1[3] = 0.1666666666666667*Gamma2_inv_lobatto[3]-0.1666666666666667*Gamma2_inv_lobatto[2]-0.1666666666666667*Gamma2_inv_lobatto[1]+0.1666666666666667*Gamma2_inv_lobatto[0]; 
    ser_2x_p1_sqrt(Gamma2_inv_p1, Gamma_inv_p1); 
    n[0] = 0.5*Gamma_inv_p1[3]*M0[3]+0.5*Gamma_inv_p1[2]*M0[2]+0.5*Gamma_inv_p1[1]*M0[1]+0.5*Gamma_inv_p1[0]*M0[0]; 
    n[1] = 0.447213595499958*Gamma_inv_p1[3]*M0[6]+0.4472135954999579*Gamma_inv_p1[1]*M0[4]+0.5*Gamma_inv_p1[2]*M0[3]+0.5*M0[2]*Gamma_inv_p1[3]+0.5*Gamma_inv_p1[0]*M0[1]+0.5*M0[0]*Gamma_inv_p1[1]; 
    n[2] = 0.447213595499958*Gamma_inv_p1[3]*M0[7]+0.4472135954999579*Gamma_inv_p1[2]*M0[5]+0.5*Gamma_inv_p1[1]*M0[3]+0.5*M0[1]*Gamma_inv_p1[3]+0.5*Gamma_inv_p1[0]*M0[2]+0.5*M0[0]*Gamma_inv_p1[2]; 
    n[3] = 0.447213595499958*Gamma_inv_p1[2]*M0[7]+0.447213595499958*Gamma_inv_p1[1]*M0[6]+0.4472135954999579*Gamma_inv_p1[3]*M0[5]+0.4472135954999579*Gamma_inv_p1[3]*M0[4]+0.5*Gamma_inv_p1[0]*M0[3]+0.5*M0[0]*Gamma_inv_p1[3]+0.5*Gamma_inv_p1[1]*M0[2]+0.5*M0[1]*Gamma_inv_p1[2]; 
    n[4] = 0.5000000000000001*Gamma_inv_p1[2]*M0[6]+0.5*Gamma_inv_p1[0]*M0[4]+0.4472135954999579*Gamma_inv_p1[3]*M0[3]+0.4472135954999579*Gamma_inv_p1[1]*M0[1]; 
    n[5] = 0.5000000000000001*Gamma_inv_p1[1]*M0[7]+0.5*Gamma_inv_p1[0]*M0[5]+0.4472135954999579*Gamma_inv_p1[3]*M0[3]+0.4472135954999579*Gamma_inv_p1[2]*M0[2]; 
    n[6] = 0.4*Gamma_inv_p1[3]*M0[7]+0.5*Gamma_inv_p1[0]*M0[6]+0.5000000000000001*Gamma_inv_p1[2]*M0[4]+0.447213595499958*Gamma_inv_p1[1]*M0[3]+0.447213595499958*M0[1]*Gamma_inv_p1[3]; 
    n[7] = 0.5*Gamma_inv_p1[0]*M0[7]+0.4*Gamma_inv_p1[3]*M0[6]+0.5000000000000001*Gamma_inv_p1[1]*M0[5]+0.447213595499958*Gamma_inv_p1[2]*M0[3]+0.447213595499958*M0[2]*Gamma_inv_p1[3]; 
  } 
  else { 
    double Gamma_inv[8] = {0.0}; 
    ser_2x_p2_sqrt(Gamma2_inv, Gamma_inv); 
    n[0] = 0.5*Gamma_inv[7]*M0[7]+0.5*Gamma_inv[6]*M0[6]+0.5*Gamma_inv[5]*M0[5]+0.5*Gamma_inv[4]*M0[4]+0.5*Gamma_inv[3]*M0[3]+0.5*Gamma_inv[2]*M0[2]+0.5*Gamma_inv[1]*M0[1]+0.5*Gamma_inv[0]*M0[0]; 
    n[1] = 0.5000000000000001*Gamma_inv[5]*M0[7]+0.5000000000000001*M0[5]*Gamma_inv[7]+0.447213595499958*Gamma_inv[3]*M0[6]+0.447213595499958*M0[3]*Gamma_inv[6]+0.4472135954999579*Gamma_inv[1]*M0[4]+0.4472135954999579*M0[1]*Gamma_inv[4]+0.5*Gamma_inv[2]*M0[3]+0.5*M0[2]*Gamma_inv[3]+0.5*Gamma_inv[0]*M0[1]+0.5*M0[0]*Gamma_inv[1]; 
    n[2] = 0.447213595499958*Gamma_inv[3]*M0[7]+0.447213595499958*M0[3]*Gamma_inv[7]+0.5000000000000001*Gamma_inv[4]*M0[6]+0.5000000000000001*M0[4]*Gamma_inv[6]+0.4472135954999579*Gamma_inv[2]*M0[5]+0.4472135954999579*M0[2]*Gamma_inv[5]+0.5*Gamma_inv[1]*M0[3]+0.5*M0[1]*Gamma_inv[3]+0.5*Gamma_inv[0]*M0[2]+0.5*M0[0]*Gamma_inv[2]; 
    n[3] = 0.4*Gamma_inv[6]*M0[7]+0.447213595499958*Gamma_inv[2]*M0[7]+0.4*M0[6]*Gamma_inv[7]+0.447213595499958*M0[2]*Gamma_inv[7]+0.447213595499958*Gamma_inv[1]*M0[6]+0.447213595499958*M0[1]*Gamma_inv[6]+0.4472135954999579*Gamma_inv[3]*M0[5]+0.4472135954999579*M0[3]*Gamma_inv[5]+0.4472135954999579*Gamma_inv[3]*M0[4]+0.4472135954999579*M0[3]*Gamma_inv[4]+0.5*Gamma_inv[0]*M0[3]+0.5*M0[0]*Gamma_inv[3]+0.5*Gamma_inv[1]*M0[2]+0.5*M0[1]*Gamma_inv[2]; 
    n[4] = 0.4472135954999579*Gamma_inv[7]*M0[7]+0.31943828249997*Gamma_inv[6]*M0[6]+0.5000000000000001*Gamma_inv[2]*M0[6]+0.5000000000000001*M0[2]*Gamma_inv[6]+0.31943828249997*Gamma_inv[4]*M0[4]+0.5*Gamma_inv[0]*M0[4]+0.5*M0[0]*Gamma_inv[4]+0.4472135954999579*Gamma_inv[3]*M0[3]+0.4472135954999579*Gamma_inv[1]*M0[1]; 
    n[5] = 0.31943828249997*Gamma_inv[7]*M0[7]+0.5000000000000001*Gamma_inv[1]*M0[7]+0.5000000000000001*M0[1]*Gamma_inv[7]+0.4472135954999579*Gamma_inv[6]*M0[6]+0.31943828249997*Gamma_inv[5]*M0[5]+0.5*Gamma_inv[0]*M0[5]+0.5*M0[0]*Gamma_inv[5]+0.4472135954999579*Gamma_inv[3]*M0[3]+0.4472135954999579*Gamma_inv[2]*M0[2]; 
    n[6] = 0.4*Gamma_inv[3]*M0[7]+0.4*M0[3]*Gamma_inv[7]+0.4472135954999579*Gamma_inv[5]*M0[6]+0.31943828249997*Gamma_inv[4]*M0[6]+0.5*Gamma_inv[0]*M0[6]+0.4472135954999579*M0[5]*Gamma_inv[6]+0.31943828249997*M0[4]*Gamma_inv[6]+0.5*M0[0]*Gamma_inv[6]+0.5000000000000001*Gamma_inv[2]*M0[4]+0.5000000000000001*M0[2]*Gamma_inv[4]+0.447213595499958*Gamma_inv[1]*M0[3]+0.447213595499958*M0[1]*Gamma_inv[3]; 
    n[7] = 0.31943828249997*Gamma_inv[5]*M0[7]+0.4472135954999579*Gamma_inv[4]*M0[7]+0.5*Gamma_inv[0]*M0[7]+0.31943828249997*M0[5]*Gamma_inv[7]+0.4472135954999579*M0[4]*Gamma_inv[7]+0.5*M0[0]*Gamma_inv[7]+0.4*Gamma_inv[3]*M0[6]+0.4*M0[3]*Gamma_inv[6]+0.5000000000000001*Gamma_inv[1]*M0[5]+0.5000000000000001*M0[1]*Gamma_inv[5]+0.447213595499958*Gamma_inv[2]*M0[3]+0.447213595499958*M0[2]*Gamma_inv[3]; 
  } 

} 
 
