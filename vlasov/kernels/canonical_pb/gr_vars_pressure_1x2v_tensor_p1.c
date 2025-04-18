#include <gkyl_canonical_pb_gr_Gamma_kernels.h> 
#include <gkyl_binop_mul_ser.h> 
GKYL_CU_DH void gr_vars_pressure_1x2v_tensor_p1(const double *w, const double *dxv, const double *h_ij_inv, const double *u_i, const double *u_i_sq, const double *GammaV, const double *GammaV_sq, const double *f, double* GKYL_RESTRICT gr_pressure) 
{ 
  // w:   Cell-center coordinates.
  // dxv: Cell spacing.
  // h_ij_inv:         Input volume expansion of the inverse metric tensor.
  //                   [Hxx, Hxy, Hxz, 
  //                     - , Hyy, Hyz, 
  //                     - ,  - , Hzz] 
  // u_i:         Spatial components of bulk four-velocity = GammaV*V_drift. 
  // u_i_sq:      Squared spatial components of bulk four-velocity = u_i^2. 
  // GammaV:      Bulk four-velocity Lorentz factor = sqrt(1 + |u_i|^2). 
  // GammaV_sq:   Squared bulk four-velocity Lorentz factor = 1 + |u_i|^2. 
  // f:           Input distribution function.
  // gr_pressure: Output relativistic pressure.
  const double volFact = dxv[1]*dxv[2]/4; 
 
  const double wx1 = w[1], dv1 = dxv[1]; 
  const double wx1_sq = wx1*wx1, dv1_sq = dv1*dv1; 
  const double *V_0 = &u_i[0]; 
  const double *V_0_sq = &u_i_sq[0]; 
 
  const double wx2 = w[2], dv2 = dxv[2]; 
  const double wx2_sq = wx2*wx2, dv2_sq = dv2*dv2; 
  const double *V_1 = &u_i[2]; 
  const double *V_1_sq = &u_i_sq[2]; 
 
  double p_sq[8] = {0.0};
  const double *Hxx = &h_ij_inv[0]; 
  const double *Hxy = &h_ij_inv[2]; 
  const double *Hyy = &h_ij_inv[4]; 

  p_sq[0] = 2.0*Hyy[0]*wx2_sq+4.0*Hxy[0]*wx1*wx2+2.0*Hxx[0]*wx1_sq+0.1666666666666667*Hyy[0]*dv2_sq+0.1666666666666667*Hxx[0]*dv1_sq; 
  p_sq[1] = 2.0*Hyy[1]*wx2_sq+4.0*Hxy[1]*wx1*wx2+2.0*Hxx[1]*wx1_sq+0.1666666666666667*Hyy[1]*dv2_sq+0.1666666666666667*Hxx[1]*dv1_sq; 
  p_sq[2] = 1.154700538379252*Hxy[0]*dv1*wx2+1.154700538379252*Hxx[0]*dv1*wx1; 
  p_sq[3] = 1.154700538379252*Hyy[0]*dv2*wx2+1.154700538379252*Hxy[0]*dv2*wx1; 
  p_sq[4] = 1.154700538379252*Hxy[1]*dv1*wx2+1.154700538379252*Hxx[1]*dv1*wx1; 
  p_sq[5] = 1.154700538379252*Hyy[1]*dv2*wx2+1.154700538379252*Hxy[1]*dv2*wx1; 
  p_sq[6] = 0.3333333333333333*Hxy[0]*dv1*dv2; 
  p_sq[7] = 0.3333333333333333*Hxy[1]*dv1*dv2; 

  double gamma_nodal[8] = {0.0};
  double gamma_inv_nodal[8] = {0.0};
  double gamma[8] = {0.0};
  double gamma_inv[8] = {0.0};

  gamma_nodal[0] = sqrt(1.0 + (-1.837117307087383*p_sq[7])+1.060660171779821*p_sq[6]+1.060660171779821*p_sq[5]+1.060660171779821*p_sq[4]-0.6123724356957944*p_sq[3]-0.6123724356957944*p_sq[2]-0.6123724356957944*p_sq[1]+0.3535533905932737*p_sq[0]);
  gamma_inv_nodal[0] = 1.0/gamma_nodal[0];
  gamma_nodal[1] = sqrt(1.0 + 1.837117307087383*p_sq[7]+1.060660171779821*p_sq[6]-1.060660171779821*p_sq[5]-1.060660171779821*p_sq[4]-0.6123724356957944*p_sq[3]-0.6123724356957944*p_sq[2]+0.6123724356957944*p_sq[1]+0.3535533905932737*p_sq[0]);
  gamma_inv_nodal[1] = 1.0/gamma_nodal[1];
  gamma_nodal[2] = sqrt(1.0 + 1.837117307087383*p_sq[7]-1.060660171779821*p_sq[6]+1.060660171779821*p_sq[5]-1.060660171779821*p_sq[4]-0.6123724356957944*p_sq[3]+0.6123724356957944*p_sq[2]-0.6123724356957944*p_sq[1]+0.3535533905932737*p_sq[0]);
  gamma_inv_nodal[2] = 1.0/gamma_nodal[2];
  gamma_nodal[3] = sqrt(1.0 + (-1.837117307087383*p_sq[7])-1.060660171779821*p_sq[6]-1.060660171779821*p_sq[5]+1.060660171779821*p_sq[4]-0.6123724356957944*p_sq[3]+0.6123724356957944*p_sq[2]+0.6123724356957944*p_sq[1]+0.3535533905932737*p_sq[0]);
  gamma_inv_nodal[3] = 1.0/gamma_nodal[3];
  gamma_nodal[4] = sqrt(1.0 + 1.837117307087383*p_sq[7]-1.060660171779821*p_sq[6]-1.060660171779821*p_sq[5]+1.060660171779821*p_sq[4]+0.6123724356957944*p_sq[3]-0.6123724356957944*p_sq[2]-0.6123724356957944*p_sq[1]+0.3535533905932737*p_sq[0]);
  gamma_inv_nodal[4] = 1.0/gamma_nodal[4];
  gamma_nodal[5] = sqrt(1.0 + (-1.837117307087383*p_sq[7])-1.060660171779821*p_sq[6]+1.060660171779821*p_sq[5]-1.060660171779821*p_sq[4]+0.6123724356957944*p_sq[3]-0.6123724356957944*p_sq[2]+0.6123724356957944*p_sq[1]+0.3535533905932737*p_sq[0]);
  gamma_inv_nodal[5] = 1.0/gamma_nodal[5];
  gamma_nodal[6] = sqrt(1.0 + (-1.837117307087383*p_sq[7])+1.060660171779821*p_sq[6]-1.060660171779821*p_sq[5]-1.060660171779821*p_sq[4]+0.6123724356957944*p_sq[3]+0.6123724356957944*p_sq[2]-0.6123724356957944*p_sq[1]+0.3535533905932737*p_sq[0]);
  gamma_inv_nodal[6] = 1.0/gamma_nodal[6];
  gamma_nodal[7] = sqrt(1.0 + 1.837117307087383*p_sq[7]+1.060660171779821*p_sq[6]+1.060660171779821*p_sq[5]+1.060660171779821*p_sq[4]+0.6123724356957944*p_sq[3]+0.6123724356957944*p_sq[2]+0.6123724356957944*p_sq[1]+0.3535533905932737*p_sq[0]);
  gamma_inv_nodal[7] = 1.0/gamma_nodal[7];

  gamma[0] = 0.3535533905932737*gamma_nodal[7]+0.3535533905932737*gamma_nodal[6]+0.3535533905932737*gamma_nodal[5]+0.3535533905932737*gamma_nodal[4]+0.3535533905932737*gamma_nodal[3]+0.3535533905932737*gamma_nodal[2]+0.3535533905932737*gamma_nodal[1]+0.3535533905932737*gamma_nodal[0]; 
  gamma[1] = 0.2041241452319315*gamma_nodal[7]-0.2041241452319315*gamma_nodal[6]+0.2041241452319315*gamma_nodal[5]-0.2041241452319315*gamma_nodal[4]+0.2041241452319315*gamma_nodal[3]-0.2041241452319315*gamma_nodal[2]+0.2041241452319315*gamma_nodal[1]-0.2041241452319315*gamma_nodal[0]; 
  gamma[2] = 0.2041241452319315*gamma_nodal[7]+0.2041241452319315*gamma_nodal[6]-0.2041241452319315*gamma_nodal[5]-0.2041241452319315*gamma_nodal[4]+0.2041241452319315*gamma_nodal[3]+0.2041241452319315*gamma_nodal[2]-0.2041241452319315*gamma_nodal[1]-0.2041241452319315*gamma_nodal[0]; 
  gamma[3] = 0.2041241452319315*gamma_nodal[7]+0.2041241452319315*gamma_nodal[6]+0.2041241452319315*gamma_nodal[5]+0.2041241452319315*gamma_nodal[4]-0.2041241452319315*gamma_nodal[3]-0.2041241452319315*gamma_nodal[2]-0.2041241452319315*gamma_nodal[1]-0.2041241452319315*gamma_nodal[0]; 
  gamma[4] = 0.1178511301977579*gamma_nodal[7]-0.1178511301977579*gamma_nodal[6]-0.1178511301977579*gamma_nodal[5]+0.1178511301977579*gamma_nodal[4]+0.1178511301977579*gamma_nodal[3]-0.1178511301977579*gamma_nodal[2]-0.1178511301977579*gamma_nodal[1]+0.1178511301977579*gamma_nodal[0]; 
  gamma[5] = 0.1178511301977579*gamma_nodal[7]-0.1178511301977579*gamma_nodal[6]+0.1178511301977579*gamma_nodal[5]-0.1178511301977579*gamma_nodal[4]-0.1178511301977579*gamma_nodal[3]+0.1178511301977579*gamma_nodal[2]-0.1178511301977579*gamma_nodal[1]+0.1178511301977579*gamma_nodal[0]; 
  gamma[6] = 0.1178511301977579*gamma_nodal[7]+0.1178511301977579*gamma_nodal[6]-0.1178511301977579*gamma_nodal[5]-0.1178511301977579*gamma_nodal[4]-0.1178511301977579*gamma_nodal[3]-0.1178511301977579*gamma_nodal[2]+0.1178511301977579*gamma_nodal[1]+0.1178511301977579*gamma_nodal[0]; 
  gamma[7] = 0.06804138174397717*gamma_nodal[7]-0.06804138174397717*gamma_nodal[6]-0.06804138174397717*gamma_nodal[5]+0.06804138174397717*gamma_nodal[4]-0.06804138174397717*gamma_nodal[3]+0.06804138174397717*gamma_nodal[2]+0.06804138174397717*gamma_nodal[1]-0.06804138174397717*gamma_nodal[0]; 

  gamma_inv[0] = 0.3535533905932737*gamma_inv_nodal[7]+0.3535533905932737*gamma_inv_nodal[6]+0.3535533905932737*gamma_inv_nodal[5]+0.3535533905932737*gamma_inv_nodal[4]+0.3535533905932737*gamma_inv_nodal[3]+0.3535533905932737*gamma_inv_nodal[2]+0.3535533905932737*gamma_inv_nodal[1]+0.3535533905932737*gamma_inv_nodal[0]; 
  gamma_inv[1] = 0.2041241452319315*gamma_inv_nodal[7]-0.2041241452319315*gamma_inv_nodal[6]+0.2041241452319315*gamma_inv_nodal[5]-0.2041241452319315*gamma_inv_nodal[4]+0.2041241452319315*gamma_inv_nodal[3]-0.2041241452319315*gamma_inv_nodal[2]+0.2041241452319315*gamma_inv_nodal[1]-0.2041241452319315*gamma_inv_nodal[0]; 
  gamma_inv[2] = 0.2041241452319315*gamma_inv_nodal[7]+0.2041241452319315*gamma_inv_nodal[6]-0.2041241452319315*gamma_inv_nodal[5]-0.2041241452319315*gamma_inv_nodal[4]+0.2041241452319315*gamma_inv_nodal[3]+0.2041241452319315*gamma_inv_nodal[2]-0.2041241452319315*gamma_inv_nodal[1]-0.2041241452319315*gamma_inv_nodal[0]; 
  gamma_inv[3] = 0.2041241452319315*gamma_inv_nodal[7]+0.2041241452319315*gamma_inv_nodal[6]+0.2041241452319315*gamma_inv_nodal[5]+0.2041241452319315*gamma_inv_nodal[4]-0.2041241452319315*gamma_inv_nodal[3]-0.2041241452319315*gamma_inv_nodal[2]-0.2041241452319315*gamma_inv_nodal[1]-0.2041241452319315*gamma_inv_nodal[0]; 
  gamma_inv[4] = 0.1178511301977579*gamma_inv_nodal[7]-0.1178511301977579*gamma_inv_nodal[6]-0.1178511301977579*gamma_inv_nodal[5]+0.1178511301977579*gamma_inv_nodal[4]+0.1178511301977579*gamma_inv_nodal[3]-0.1178511301977579*gamma_inv_nodal[2]-0.1178511301977579*gamma_inv_nodal[1]+0.1178511301977579*gamma_inv_nodal[0]; 
  gamma_inv[5] = 0.1178511301977579*gamma_inv_nodal[7]-0.1178511301977579*gamma_inv_nodal[6]+0.1178511301977579*gamma_inv_nodal[5]-0.1178511301977579*gamma_inv_nodal[4]-0.1178511301977579*gamma_inv_nodal[3]+0.1178511301977579*gamma_inv_nodal[2]-0.1178511301977579*gamma_inv_nodal[1]+0.1178511301977579*gamma_inv_nodal[0]; 
  gamma_inv[6] = 0.1178511301977579*gamma_inv_nodal[7]+0.1178511301977579*gamma_inv_nodal[6]-0.1178511301977579*gamma_inv_nodal[5]-0.1178511301977579*gamma_inv_nodal[4]-0.1178511301977579*gamma_inv_nodal[3]-0.1178511301977579*gamma_inv_nodal[2]+0.1178511301977579*gamma_inv_nodal[1]+0.1178511301977579*gamma_inv_nodal[0]; 
  gamma_inv[7] = 0.06804138174397717*gamma_inv_nodal[7]-0.06804138174397717*gamma_inv_nodal[6]-0.06804138174397717*gamma_inv_nodal[5]+0.06804138174397717*gamma_inv_nodal[4]-0.06804138174397717*gamma_inv_nodal[3]+0.06804138174397717*gamma_inv_nodal[2]+0.06804138174397717*gamma_inv_nodal[1]-0.06804138174397717*gamma_inv_nodal[0]; 

  double temp[8] = {0.0}; 
  double temp_sq[8] = {0.0}; 
  double p_fac[8] = {0.0}; 
  double Hxx_sq[2] = {0.0}; 
  double Hxy_sq[2] = {0.0}; 
  double Hyy_sq[2] = {0.0}; 
  binop_mul_1d_ser_p1(Hxx, Hxx, Hxx_sq); 
  binop_mul_1d_ser_p1(Hxy, Hxy, Hxy_sq); 
  binop_mul_1d_ser_p1(Hyy, Hyy, Hyy_sq); 
  temp[0] = 2.0*V_1[0]*wx2+2.0*V_0[0]*wx1; 
  temp[1] = 2.0*V_1[1]*wx2+2.0*V_0[1]*wx1; 
  temp[2] = 0.5773502691896258*V_0[0]*dv1; 
  temp[3] = 0.5773502691896258*V_1[0]*dv2; 
  temp[4] = 0.5773502691896258*V_0[1]*dv1; 
  temp[5] = 0.5773502691896258*V_1[1]*dv2; 

  temp_sq[0] = 2.0*V_1_sq[0]*wx2_sq+2.828427124746191*V_0[1]*V_1[1]*wx1*wx2+2.828427124746191*V_0[0]*V_1[0]*wx1*wx2+2.0*V_0_sq[0]*wx1_sq+0.1666666666666667*V_1_sq[0]*dv2_sq+0.1666666666666667*V_0_sq[0]*dv1_sq; 
  temp_sq[1] = 2.0*V_1_sq[1]*wx2_sq+2.828427124746191*V_0[0]*V_1[1]*wx1*wx2+2.828427124746191*V_1[0]*V_0[1]*wx1*wx2+2.0*V_0_sq[1]*wx1_sq+0.1666666666666667*V_1_sq[1]*dv2_sq+0.1666666666666667*V_0_sq[1]*dv1_sq; 
  temp_sq[2] = 0.8164965809277261*V_0[1]*V_1[1]*dv1*wx2+0.8164965809277261*V_0[0]*V_1[0]*dv1*wx2+1.154700538379252*V_0_sq[0]*dv1*wx1; 
  temp_sq[3] = 1.154700538379252*V_1_sq[0]*dv2*wx2+0.8164965809277261*V_0[1]*V_1[1]*dv2*wx1+0.8164965809277261*V_0[0]*V_1[0]*dv2*wx1; 
  temp_sq[4] = 0.8164965809277261*V_0[0]*V_1[1]*dv1*wx2+0.8164965809277261*V_1[0]*V_0[1]*dv1*wx2+1.154700538379252*V_0_sq[1]*dv1*wx1; 
  temp_sq[5] = 1.154700538379252*V_1_sq[1]*dv2*wx2+0.8164965809277261*V_0[0]*V_1[1]*dv2*wx1+0.8164965809277261*V_1[0]*V_0[1]*dv2*wx1; 
  temp_sq[6] = 0.2357022603955158*V_0[1]*V_1[1]*dv1*dv2+0.2357022603955158*V_0[0]*V_1[0]*dv1*dv2; 
  temp_sq[7] = 0.2357022603955158*V_0[0]*V_1[1]*dv1*dv2+0.2357022603955158*V_1[0]*V_0[1]*dv1*dv2; 

  p_fac[0] = 0.3535533905932737*gamma_inv[7]*temp_sq[7]+0.3535533905932737*gamma_inv[6]*temp_sq[6]+0.3535533905932737*gamma_inv[5]*temp_sq[5]+0.3535533905932737*gamma_inv[4]*temp_sq[4]+0.3535533905932737*gamma_inv[3]*temp_sq[3]+0.3535533905932737*gamma_inv[2]*temp_sq[2]+0.7071067811865475*GammaV_sq[1]*gamma[1]+0.3535533905932737*gamma_inv[1]*temp_sq[1]-1.414213562373095*GammaV[1]*temp[1]+0.7071067811865475*GammaV_sq[0]*gamma[0]+0.3535533905932737*gamma_inv[0]*temp_sq[0]-1.414213562373095*GammaV[0]*temp[0]-1.0*gamma_inv[0]; 
  p_fac[1] = 0.3535533905932737*gamma_inv[6]*temp_sq[7]+0.3535533905932737*temp_sq[6]*gamma_inv[7]+0.3535533905932737*gamma_inv[3]*temp_sq[5]+0.3535533905932737*temp_sq[3]*gamma_inv[5]+0.3535533905932737*gamma_inv[2]*temp_sq[4]+0.3535533905932737*temp_sq[2]*gamma_inv[4]+0.7071067811865475*GammaV_sq[0]*gamma[1]+0.3535533905932737*gamma_inv[0]*temp_sq[1]-1.414213562373095*GammaV[0]*temp[1]+0.3535533905932737*temp_sq[0]*gamma_inv[1]-1.0*gamma_inv[1]+0.7071067811865475*gamma[0]*GammaV_sq[1]-1.414213562373095*temp[0]*GammaV[1]; 
  p_fac[2] = 0.3535533905932737*gamma_inv[5]*temp_sq[7]+0.3535533905932737*temp_sq[5]*gamma_inv[7]+0.3535533905932737*gamma_inv[3]*temp_sq[6]+0.3535533905932737*temp_sq[3]*gamma_inv[6]+0.7071067811865475*GammaV_sq[1]*gamma[4]+0.3535533905932737*gamma_inv[1]*temp_sq[4]-1.414213562373095*GammaV[1]*temp[4]+0.3535533905932737*temp_sq[1]*gamma_inv[4]+0.7071067811865475*GammaV_sq[0]*gamma[2]+0.3535533905932737*gamma_inv[0]*temp_sq[2]-1.414213562373095*GammaV[0]*temp[2]+0.3535533905932737*temp_sq[0]*gamma_inv[2]-1.0*gamma_inv[2]; 
  p_fac[3] = 0.3535533905932737*gamma_inv[4]*temp_sq[7]+0.3535533905932737*temp_sq[4]*gamma_inv[7]+0.3535533905932737*gamma_inv[2]*temp_sq[6]+0.3535533905932737*temp_sq[2]*gamma_inv[6]+0.7071067811865475*GammaV_sq[1]*gamma[5]+0.3535533905932737*gamma_inv[1]*temp_sq[5]-1.414213562373095*GammaV[1]*temp[5]+0.3535533905932737*temp_sq[1]*gamma_inv[5]+0.7071067811865475*GammaV_sq[0]*gamma[3]+0.3535533905932737*gamma_inv[0]*temp_sq[3]-1.414213562373095*GammaV[0]*temp[3]+0.3535533905932737*temp_sq[0]*gamma_inv[3]-1.0*gamma_inv[3]; 
  p_fac[4] = 0.3535533905932737*gamma_inv[3]*temp_sq[7]+0.3535533905932737*temp_sq[3]*gamma_inv[7]+0.3535533905932737*gamma_inv[5]*temp_sq[6]+0.3535533905932737*temp_sq[5]*gamma_inv[6]+0.7071067811865475*GammaV_sq[0]*gamma[4]+0.3535533905932737*gamma_inv[0]*temp_sq[4]-1.414213562373095*GammaV[0]*temp[4]+0.3535533905932737*temp_sq[0]*gamma_inv[4]-1.0*gamma_inv[4]+0.7071067811865475*GammaV_sq[1]*gamma[2]+0.3535533905932737*gamma_inv[1]*temp_sq[2]-1.414213562373095*GammaV[1]*temp[2]+0.3535533905932737*temp_sq[1]*gamma_inv[2]; 
  p_fac[5] = 0.3535533905932737*gamma_inv[2]*temp_sq[7]+0.3535533905932737*temp_sq[2]*gamma_inv[7]+0.3535533905932737*gamma_inv[4]*temp_sq[6]+0.3535533905932737*temp_sq[4]*gamma_inv[6]+0.7071067811865475*GammaV_sq[0]*gamma[5]+0.3535533905932737*gamma_inv[0]*temp_sq[5]-1.414213562373095*GammaV[0]*temp[5]+0.3535533905932737*temp_sq[0]*gamma_inv[5]-1.0*gamma_inv[5]+0.7071067811865475*GammaV_sq[1]*gamma[3]+0.3535533905932737*gamma_inv[1]*temp_sq[3]-1.414213562373095*GammaV[1]*temp[3]+0.3535533905932737*temp_sq[1]*gamma_inv[3]; 
  p_fac[6] = 0.7071067811865475*GammaV_sq[1]*gamma[7]+0.3535533905932737*gamma_inv[1]*temp_sq[7]+0.3535533905932737*temp_sq[1]*gamma_inv[7]+0.7071067811865475*GammaV_sq[0]*gamma[6]+0.3535533905932737*gamma_inv[0]*temp_sq[6]+0.3535533905932737*temp_sq[0]*gamma_inv[6]-1.0*gamma_inv[6]+0.3535533905932737*gamma_inv[4]*temp_sq[5]+0.3535533905932737*temp_sq[4]*gamma_inv[5]+0.3535533905932737*gamma_inv[2]*temp_sq[3]+0.3535533905932737*temp_sq[2]*gamma_inv[3]; 
  p_fac[7] = 0.7071067811865475*GammaV_sq[0]*gamma[7]+0.3535533905932737*gamma_inv[0]*temp_sq[7]+0.3535533905932737*temp_sq[0]*gamma_inv[7]-1.0*gamma_inv[7]+0.7071067811865475*GammaV_sq[1]*gamma[6]+0.3535533905932737*gamma_inv[1]*temp_sq[6]+0.3535533905932737*temp_sq[1]*gamma_inv[6]+0.3535533905932737*gamma_inv[2]*temp_sq[5]+0.3535533905932737*temp_sq[2]*gamma_inv[5]+0.3535533905932737*gamma_inv[3]*temp_sq[4]+0.3535533905932737*temp_sq[3]*gamma_inv[4]; 

  gr_pressure[0] += (0.3535533905932737*f[7]*p_fac[7]+0.3535533905932737*f[6]*p_fac[6]+0.3535533905932737*f[5]*p_fac[5]+0.3535533905932737*f[4]*p_fac[4]+0.3535533905932737*f[3]*p_fac[3]+0.3535533905932737*f[2]*p_fac[2]+0.3535533905932737*f[1]*p_fac[1]+0.3535533905932737*f[0]*p_fac[0])*volFact; 
  gr_pressure[1] += (0.3535533905932737*f[6]*p_fac[7]+0.3535533905932737*p_fac[6]*f[7]+0.3535533905932737*f[3]*p_fac[5]+0.3535533905932737*p_fac[3]*f[5]+0.3535533905932737*f[2]*p_fac[4]+0.3535533905932737*p_fac[2]*f[4]+0.3535533905932737*f[0]*p_fac[1]+0.3535533905932737*p_fac[0]*f[1])*volFact; 
} 
