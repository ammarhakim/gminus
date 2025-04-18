#include <gkyl_canonical_pb_gr_Gamma_kernels.h> 
#include <gkyl_binop_mul_ser.h> 
GKYL_CU_DH void gr_vars_pressure_1x2v_ser_p1(const double *w, const double *dxv, const double *h_ij_inv, const double *u_i, const double *u_i_sq, const double *GammaV, const double *GammaV_sq, const double *f, double* GKYL_RESTRICT gr_pressure) 
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
  double p_fac1[8] = {0.0};
  double p_fac2[8] = {0.0};
  double p_fac3[8] = {0.0};
  double temp1[8] = {0.0};
  double temp2[8] = {0.0};
  double temp3[8] = {0.0};
  double temp4[8] = {0.0};
  double temp_sq1[8] = {0.0};
  double temp_sq2[8] = {0.0};
  double temp_sq3[8] = {0.0};
  double temp_sq4[8] = {0.0};
  double temp_sq5[8] = {0.0};
  double temp_sq6[8] = {0.0};
  double temp_sq7[8] = {0.0};

  temp1[0] = 1.414213562373095*Hxx[1]*V_0[1]*wx1+1.414213562373095*Hxx[0]*V_0[0]*wx1; 
  temp1[1] = 1.414213562373095*Hxx[0]*V_0[1]*wx1+1.414213562373095*V_0[0]*Hxx[1]*wx1; 
  temp1[2] = 0.408248290463863*Hxx[1]*V_0[1]*dv1+0.408248290463863*Hxx[0]*V_0[0]*dv1; 
  temp1[4] = 0.408248290463863*Hxx[0]*V_0[1]*dv1+0.408248290463863*V_0[0]*Hxx[1]*dv1; 

  temp2[0] = 1.414213562373095*Hxy[1]*V_0[1]*wx2+1.414213562373095*Hxy[0]*V_0[0]*wx2; 
  temp2[1] = 1.414213562373095*Hxy[0]*V_0[1]*wx2+1.414213562373095*V_0[0]*Hxy[1]*wx2; 
  temp2[3] = 0.408248290463863*Hxy[1]*V_0[1]*dv2+0.408248290463863*Hxy[0]*V_0[0]*dv2; 
  temp2[5] = 0.408248290463863*Hxy[0]*V_0[1]*dv2+0.408248290463863*V_0[0]*Hxy[1]*dv2; 

  temp3[0] = 1.414213562373095*Hxy[1]*V_1[1]*wx1+1.414213562373095*Hxy[0]*V_1[0]*wx1; 
  temp3[1] = 1.414213562373095*Hxy[0]*V_1[1]*wx1+1.414213562373095*V_1[0]*Hxy[1]*wx1; 
  temp3[2] = 0.408248290463863*Hxy[1]*V_1[1]*dv1+0.408248290463863*Hxy[0]*V_1[0]*dv1; 
  temp3[4] = 0.408248290463863*Hxy[0]*V_1[1]*dv1+0.408248290463863*V_1[0]*Hxy[1]*dv1; 

  temp4[0] = 1.414213562373095*Hyy[1]*V_1[1]*wx2+1.414213562373095*Hyy[0]*V_1[0]*wx2; 
  temp4[1] = 1.414213562373095*Hyy[0]*V_1[1]*wx2+1.414213562373095*V_1[0]*Hyy[1]*wx2; 
  temp4[3] = 0.408248290463863*Hyy[1]*V_1[1]*dv2+0.408248290463863*Hyy[0]*V_1[0]*dv2; 
  temp4[5] = 0.408248290463863*Hyy[0]*V_1[1]*dv2+0.408248290463863*V_1[0]*Hyy[1]*dv2; 

  temp_sq1[0] = 1.414213562373095*Hxx_sq[1]*V_0_sq[1]*wx1_sq+1.414213562373095*Hxx_sq[0]*V_0_sq[0]*wx1_sq+0.1178511301977579*Hxx_sq[1]*V_0_sq[1]*dv1_sq+0.1178511301977579*Hxx_sq[0]*V_0_sq[0]*dv1_sq; 
  temp_sq1[1] = 1.414213562373095*Hxx_sq[0]*V_0_sq[1]*wx1_sq+1.414213562373095*V_0_sq[0]*Hxx_sq[1]*wx1_sq+0.1178511301977579*Hxx_sq[0]*V_0_sq[1]*dv1_sq+0.1178511301977579*V_0_sq[0]*Hxx_sq[1]*dv1_sq; 
  temp_sq1[2] = 0.8164965809277261*Hxx_sq[1]*V_0_sq[1]*dv1*wx1+0.8164965809277261*Hxx_sq[0]*V_0_sq[0]*dv1*wx1; 
  temp_sq1[4] = 0.8164965809277261*Hxx_sq[0]*V_0_sq[1]*dv1*wx1+0.8164965809277261*V_0_sq[0]*Hxx_sq[1]*dv1*wx1; 

  temp_sq2[0] = 1.414213562373095*Hyy_sq[1]*V_1_sq[1]*wx2_sq+1.414213562373095*Hyy_sq[0]*V_1_sq[0]*wx2_sq+0.1178511301977579*Hyy_sq[1]*V_1_sq[1]*dv2_sq+0.1178511301977579*Hyy_sq[0]*V_1_sq[0]*dv2_sq; 
  temp_sq2[1] = 1.414213562373095*Hyy_sq[0]*V_1_sq[1]*wx2_sq+1.414213562373095*V_1_sq[0]*Hyy_sq[1]*wx2_sq+0.1178511301977579*Hyy_sq[0]*V_1_sq[1]*dv2_sq+0.1178511301977579*V_1_sq[0]*Hyy_sq[1]*dv2_sq; 
  temp_sq2[3] = 0.8164965809277261*Hyy_sq[1]*V_1_sq[1]*dv2*wx2+0.8164965809277261*Hyy_sq[0]*V_1_sq[0]*dv2*wx2; 
  temp_sq2[5] = 0.8164965809277261*Hyy_sq[0]*V_1_sq[1]*dv2*wx2+0.8164965809277261*V_1_sq[0]*Hyy_sq[1]*dv2*wx2; 

  temp_sq3[0] = 2.545584412271571*Hxx[1]*Hxy[1]*V_0[1]*V_1[1]*wx1_sq+1.414213562373095*Hxx[0]*Hxy[0]*V_0[1]*V_1[1]*wx1_sq+1.414213562373095*Hxx[0]*V_0[0]*Hxy[1]*V_1[1]*wx1_sq+1.414213562373095*Hxy[0]*V_0[0]*Hxx[1]*V_1[1]*wx1_sq+1.414213562373095*Hxx[0]*V_1[0]*Hxy[1]*V_0[1]*wx1_sq+1.414213562373095*Hxy[0]*V_1[0]*Hxx[1]*V_0[1]*wx1_sq+1.414213562373095*V_0[0]*V_1[0]*Hxx[1]*Hxy[1]*wx1_sq+1.414213562373095*Hxx[0]*Hxy[0]*V_0[0]*V_1[0]*wx1_sq+0.2121320343559642*Hxx[1]*Hxy[1]*V_0[1]*V_1[1]*dv1_sq+0.1178511301977579*Hxx[0]*Hxy[0]*V_0[1]*V_1[1]*dv1_sq+0.1178511301977579*Hxx[0]*V_0[0]*Hxy[1]*V_1[1]*dv1_sq+0.1178511301977579*Hxy[0]*V_0[0]*Hxx[1]*V_1[1]*dv1_sq+0.1178511301977579*Hxx[0]*V_1[0]*Hxy[1]*V_0[1]*dv1_sq+0.1178511301977579*Hxy[0]*V_1[0]*Hxx[1]*V_0[1]*dv1_sq+0.1178511301977579*V_0[0]*V_1[0]*Hxx[1]*Hxy[1]*dv1_sq+0.1178511301977579*Hxx[0]*Hxy[0]*V_0[0]*V_1[0]*dv1_sq; 
  temp_sq3[1] = 2.545584412271571*Hxx[0]*Hxy[1]*V_0[1]*V_1[1]*wx1_sq+2.545584412271571*Hxy[0]*Hxx[1]*V_0[1]*V_1[1]*wx1_sq+2.545584412271571*V_0[0]*Hxx[1]*Hxy[1]*V_1[1]*wx1_sq+1.414213562373095*Hxx[0]*Hxy[0]*V_0[0]*V_1[1]*wx1_sq+2.545584412271571*V_1[0]*Hxx[1]*Hxy[1]*V_0[1]*wx1_sq+1.414213562373095*Hxx[0]*Hxy[0]*V_1[0]*V_0[1]*wx1_sq+1.414213562373095*Hxx[0]*V_0[0]*V_1[0]*Hxy[1]*wx1_sq+1.414213562373095*Hxy[0]*V_0[0]*V_1[0]*Hxx[1]*wx1_sq+0.2121320343559642*Hxx[0]*Hxy[1]*V_0[1]*V_1[1]*dv1_sq+0.2121320343559642*Hxy[0]*Hxx[1]*V_0[1]*V_1[1]*dv1_sq+0.2121320343559642*V_0[0]*Hxx[1]*Hxy[1]*V_1[1]*dv1_sq+0.1178511301977579*Hxx[0]*Hxy[0]*V_0[0]*V_1[1]*dv1_sq+0.2121320343559642*V_1[0]*Hxx[1]*Hxy[1]*V_0[1]*dv1_sq+0.1178511301977579*Hxx[0]*Hxy[0]*V_1[0]*V_0[1]*dv1_sq+0.1178511301977579*Hxx[0]*V_0[0]*V_1[0]*Hxy[1]*dv1_sq+0.1178511301977579*Hxy[0]*V_0[0]*V_1[0]*Hxx[1]*dv1_sq; 
  temp_sq3[2] = 1.469693845669907*Hxx[1]*Hxy[1]*V_0[1]*V_1[1]*dv1*wx1+0.8164965809277261*Hxx[0]*Hxy[0]*V_0[1]*V_1[1]*dv1*wx1+0.8164965809277261*Hxx[0]*V_0[0]*Hxy[1]*V_1[1]*dv1*wx1+0.8164965809277261*Hxy[0]*V_0[0]*Hxx[1]*V_1[1]*dv1*wx1+0.8164965809277261*Hxx[0]*V_1[0]*Hxy[1]*V_0[1]*dv1*wx1+0.8164965809277261*Hxy[0]*V_1[0]*Hxx[1]*V_0[1]*dv1*wx1+0.8164965809277261*V_0[0]*V_1[0]*Hxx[1]*Hxy[1]*dv1*wx1+0.8164965809277261*Hxx[0]*Hxy[0]*V_0[0]*V_1[0]*dv1*wx1; 
  temp_sq3[4] = 1.469693845669907*Hxx[0]*Hxy[1]*V_0[1]*V_1[1]*dv1*wx1+1.469693845669907*Hxy[0]*Hxx[1]*V_0[1]*V_1[1]*dv1*wx1+1.469693845669907*V_0[0]*Hxx[1]*Hxy[1]*V_1[1]*dv1*wx1+0.8164965809277261*Hxx[0]*Hxy[0]*V_0[0]*V_1[1]*dv1*wx1+1.469693845669907*V_1[0]*Hxx[1]*Hxy[1]*V_0[1]*dv1*wx1+0.8164965809277261*Hxx[0]*Hxy[0]*V_1[0]*V_0[1]*dv1*wx1+0.8164965809277261*Hxx[0]*V_0[0]*V_1[0]*Hxy[1]*dv1*wx1+0.8164965809277261*Hxy[0]*V_0[0]*V_1[0]*Hxx[1]*dv1*wx1; 

  temp_sq4[0] = 2.545584412271571*Hxy[1]*Hyy[1]*V_0[1]*V_1[1]*wx2_sq+1.414213562373095*Hxy[0]*Hyy[0]*V_0[1]*V_1[1]*wx2_sq+1.414213562373095*Hxy[0]*V_0[0]*Hyy[1]*V_1[1]*wx2_sq+1.414213562373095*Hyy[0]*V_0[0]*Hxy[1]*V_1[1]*wx2_sq+1.414213562373095*Hxy[0]*V_1[0]*Hyy[1]*V_0[1]*wx2_sq+1.414213562373095*Hyy[0]*V_1[0]*Hxy[1]*V_0[1]*wx2_sq+1.414213562373095*V_0[0]*V_1[0]*Hxy[1]*Hyy[1]*wx2_sq+1.414213562373095*Hxy[0]*Hyy[0]*V_0[0]*V_1[0]*wx2_sq+0.2121320343559642*Hxy[1]*Hyy[1]*V_0[1]*V_1[1]*dv2_sq+0.1178511301977579*Hxy[0]*Hyy[0]*V_0[1]*V_1[1]*dv2_sq+0.1178511301977579*Hxy[0]*V_0[0]*Hyy[1]*V_1[1]*dv2_sq+0.1178511301977579*Hyy[0]*V_0[0]*Hxy[1]*V_1[1]*dv2_sq+0.1178511301977579*Hxy[0]*V_1[0]*Hyy[1]*V_0[1]*dv2_sq+0.1178511301977579*Hyy[0]*V_1[0]*Hxy[1]*V_0[1]*dv2_sq+0.1178511301977579*V_0[0]*V_1[0]*Hxy[1]*Hyy[1]*dv2_sq+0.1178511301977579*Hxy[0]*Hyy[0]*V_0[0]*V_1[0]*dv2_sq; 
  temp_sq4[1] = 2.545584412271571*Hxy[0]*Hyy[1]*V_0[1]*V_1[1]*wx2_sq+2.545584412271571*Hyy[0]*Hxy[1]*V_0[1]*V_1[1]*wx2_sq+2.545584412271571*V_0[0]*Hxy[1]*Hyy[1]*V_1[1]*wx2_sq+1.414213562373095*Hxy[0]*Hyy[0]*V_0[0]*V_1[1]*wx2_sq+2.545584412271571*V_1[0]*Hxy[1]*Hyy[1]*V_0[1]*wx2_sq+1.414213562373095*Hxy[0]*Hyy[0]*V_1[0]*V_0[1]*wx2_sq+1.414213562373095*Hxy[0]*V_0[0]*V_1[0]*Hyy[1]*wx2_sq+1.414213562373095*Hyy[0]*V_0[0]*V_1[0]*Hxy[1]*wx2_sq+0.2121320343559642*Hxy[0]*Hyy[1]*V_0[1]*V_1[1]*dv2_sq+0.2121320343559642*Hyy[0]*Hxy[1]*V_0[1]*V_1[1]*dv2_sq+0.2121320343559642*V_0[0]*Hxy[1]*Hyy[1]*V_1[1]*dv2_sq+0.1178511301977579*Hxy[0]*Hyy[0]*V_0[0]*V_1[1]*dv2_sq+0.2121320343559642*V_1[0]*Hxy[1]*Hyy[1]*V_0[1]*dv2_sq+0.1178511301977579*Hxy[0]*Hyy[0]*V_1[0]*V_0[1]*dv2_sq+0.1178511301977579*Hxy[0]*V_0[0]*V_1[0]*Hyy[1]*dv2_sq+0.1178511301977579*Hyy[0]*V_0[0]*V_1[0]*Hxy[1]*dv2_sq; 
  temp_sq4[3] = 1.469693845669907*Hxy[1]*Hyy[1]*V_0[1]*V_1[1]*dv2*wx2+0.8164965809277261*Hxy[0]*Hyy[0]*V_0[1]*V_1[1]*dv2*wx2+0.8164965809277261*Hxy[0]*V_0[0]*Hyy[1]*V_1[1]*dv2*wx2+0.8164965809277261*Hyy[0]*V_0[0]*Hxy[1]*V_1[1]*dv2*wx2+0.8164965809277261*Hxy[0]*V_1[0]*Hyy[1]*V_0[1]*dv2*wx2+0.8164965809277261*Hyy[0]*V_1[0]*Hxy[1]*V_0[1]*dv2*wx2+0.8164965809277261*V_0[0]*V_1[0]*Hxy[1]*Hyy[1]*dv2*wx2+0.8164965809277261*Hxy[0]*Hyy[0]*V_0[0]*V_1[0]*dv2*wx2; 
  temp_sq4[5] = 1.469693845669907*Hxy[0]*Hyy[1]*V_0[1]*V_1[1]*dv2*wx2+1.469693845669907*Hyy[0]*Hxy[1]*V_0[1]*V_1[1]*dv2*wx2+1.469693845669907*V_0[0]*Hxy[1]*Hyy[1]*V_1[1]*dv2*wx2+0.8164965809277261*Hxy[0]*Hyy[0]*V_0[0]*V_1[1]*dv2*wx2+1.469693845669907*V_1[0]*Hxy[1]*Hyy[1]*V_0[1]*dv2*wx2+0.8164965809277261*Hxy[0]*Hyy[0]*V_1[0]*V_0[1]*dv2*wx2+0.8164965809277261*Hxy[0]*V_0[0]*V_1[0]*Hyy[1]*dv2*wx2+0.8164965809277261*Hyy[0]*V_0[0]*V_1[0]*Hxy[1]*dv2*wx2; 

  temp_sq5[0] = 1.414213562373095*Hxy_sq[1]*V_1_sq[1]*wx1_sq+1.414213562373095*Hxy_sq[0]*V_1_sq[0]*wx1_sq+0.1178511301977579*Hxy_sq[1]*V_1_sq[1]*dv1_sq+0.1178511301977579*Hxy_sq[0]*V_1_sq[0]*dv1_sq; 
  temp_sq5[1] = 1.414213562373095*Hxy_sq[0]*V_1_sq[1]*wx1_sq+1.414213562373095*V_1_sq[0]*Hxy_sq[1]*wx1_sq+0.1178511301977579*Hxy_sq[0]*V_1_sq[1]*dv1_sq+0.1178511301977579*V_1_sq[0]*Hxy_sq[1]*dv1_sq; 
  temp_sq5[2] = 0.8164965809277261*Hxy_sq[1]*V_1_sq[1]*dv1*wx1+0.8164965809277261*Hxy_sq[0]*V_1_sq[0]*dv1*wx1; 
  temp_sq5[4] = 0.8164965809277261*Hxy_sq[0]*V_1_sq[1]*dv1*wx1+0.8164965809277261*V_1_sq[0]*Hxy_sq[1]*dv1*wx1; 

  temp_sq6[0] = 2.0*Hxy_sq[0]*V_0[1]*V_1[1]*wx1*wx2+2.0*V_0[0]*Hxy_sq[1]*V_1[1]*wx1*wx2+2.0*V_1[0]*Hxy_sq[1]*V_0[1]*wx1*wx2+2.0*Hxy_sq[0]*V_0[0]*V_1[0]*wx1*wx2; 
  temp_sq6[1] = 3.6*Hxy_sq[1]*V_0[1]*V_1[1]*wx1*wx2+2.0*Hxy_sq[0]*V_0[0]*V_1[1]*wx1*wx2+2.0*Hxy_sq[0]*V_1[0]*V_0[1]*wx1*wx2+2.0*V_0[0]*V_1[0]*Hxy_sq[1]*wx1*wx2; 
  temp_sq6[2] = 0.5773502691896258*Hxy_sq[0]*V_0[1]*V_1[1]*dv1*wx2+0.5773502691896258*V_0[0]*Hxy_sq[1]*V_1[1]*dv1*wx2+0.5773502691896258*V_1[0]*Hxy_sq[1]*V_0[1]*dv1*wx2+0.5773502691896258*Hxy_sq[0]*V_0[0]*V_1[0]*dv1*wx2; 
  temp_sq6[3] = 0.5773502691896258*Hxy_sq[0]*V_0[1]*V_1[1]*dv2*wx1+0.5773502691896258*V_0[0]*Hxy_sq[1]*V_1[1]*dv2*wx1+0.5773502691896258*V_1[0]*Hxy_sq[1]*V_0[1]*dv2*wx1+0.5773502691896258*Hxy_sq[0]*V_0[0]*V_1[0]*dv2*wx1; 
  temp_sq6[4] = 1.039230484541326*Hxy_sq[1]*V_0[1]*V_1[1]*dv1*wx2+0.5773502691896258*Hxy_sq[0]*V_0[0]*V_1[1]*dv1*wx2+0.5773502691896258*Hxy_sq[0]*V_1[0]*V_0[1]*dv1*wx2+0.5773502691896258*V_0[0]*V_1[0]*Hxy_sq[1]*dv1*wx2; 
  temp_sq6[5] = 1.039230484541326*Hxy_sq[1]*V_0[1]*V_1[1]*dv2*wx1+0.5773502691896258*Hxy_sq[0]*V_0[0]*V_1[1]*dv2*wx1+0.5773502691896258*Hxy_sq[0]*V_1[0]*V_0[1]*dv2*wx1+0.5773502691896258*V_0[0]*V_1[0]*Hxy_sq[1]*dv2*wx1; 
  temp_sq6[6] = 0.1666666666666667*Hxy_sq[0]*V_0[1]*V_1[1]*dv1*dv2+0.1666666666666667*V_0[0]*Hxy_sq[1]*V_1[1]*dv1*dv2+0.1666666666666667*V_1[0]*Hxy_sq[1]*V_0[1]*dv1*dv2+0.1666666666666667*Hxy_sq[0]*V_0[0]*V_1[0]*dv1*dv2; 
  temp_sq6[7] = 0.3*Hxy_sq[1]*V_0[1]*V_1[1]*dv1*dv2+0.1666666666666667*Hxy_sq[0]*V_0[0]*V_1[1]*dv1*dv2+0.1666666666666667*Hxy_sq[0]*V_1[0]*V_0[1]*dv1*dv2+0.1666666666666667*V_0[0]*V_1[0]*Hxy_sq[1]*dv1*dv2; 

  temp_sq7[0] = 1.414213562373095*Hxy_sq[1]*V_0_sq[1]*wx2_sq+1.414213562373095*Hxy_sq[0]*V_0_sq[0]*wx2_sq+0.1178511301977579*Hxy_sq[1]*V_0_sq[1]*dv2_sq+0.1178511301977579*Hxy_sq[0]*V_0_sq[0]*dv2_sq; 
  temp_sq7[1] = 1.414213562373095*Hxy_sq[0]*V_0_sq[1]*wx2_sq+1.414213562373095*V_0_sq[0]*Hxy_sq[1]*wx2_sq+0.1178511301977579*Hxy_sq[0]*V_0_sq[1]*dv2_sq+0.1178511301977579*V_0_sq[0]*Hxy_sq[1]*dv2_sq; 
  temp_sq7[3] = 0.8164965809277261*Hxy_sq[1]*V_0_sq[1]*dv2*wx2+0.8164965809277261*Hxy_sq[0]*V_0_sq[0]*dv2*wx2; 
  temp_sq7[5] = 0.8164965809277261*Hxy_sq[0]*V_0_sq[1]*dv2*wx2+0.8164965809277261*V_0_sq[0]*Hxy_sq[1]*dv2*wx2; 

  temp[0] = temp1[0] + temp2[0] + temp3[0] + temp4[0]; 
  temp[1] = temp1[1] + temp2[1] + temp3[1] + temp4[1]; 
  temp[2] = temp1[2] + temp2[2] + temp3[2] + temp4[2]; 
  temp[3] = temp1[3] + temp2[3] + temp3[3] + temp4[3]; 
  temp[4] = temp1[4] + temp2[4] + temp3[4] + temp4[4]; 
  temp[5] = temp1[5] + temp2[5] + temp3[5] + temp4[5]; 
  temp[6] = temp1[6] + temp2[6] + temp3[6] + temp4[6]; 
  temp[7] = temp1[7] + temp2[7] + temp3[7] + temp4[7]; 

  temp_sq[0] = temp_sq1[0] + temp_sq2[0] + temp_sq3[0] + temp_sq4[0] + temp_sq5[0] + temp_sq6[0] + temp_sq7[0];
  temp_sq[1] = temp_sq1[1] + temp_sq2[1] + temp_sq3[1] + temp_sq4[1] + temp_sq5[1] + temp_sq6[1] + temp_sq7[1];
  temp_sq[2] = temp_sq1[2] + temp_sq2[2] + temp_sq3[2] + temp_sq4[2] + temp_sq5[2] + temp_sq6[2] + temp_sq7[2];
  temp_sq[3] = temp_sq1[3] + temp_sq2[3] + temp_sq3[3] + temp_sq4[3] + temp_sq5[3] + temp_sq6[3] + temp_sq7[3];
  temp_sq[4] = temp_sq1[4] + temp_sq2[4] + temp_sq3[4] + temp_sq4[4] + temp_sq5[4] + temp_sq6[4] + temp_sq7[4];
  temp_sq[5] = temp_sq1[5] + temp_sq2[5] + temp_sq3[5] + temp_sq4[5] + temp_sq5[5] + temp_sq6[5] + temp_sq7[5];
  temp_sq[6] = temp_sq1[6] + temp_sq2[6] + temp_sq3[6] + temp_sq4[6] + temp_sq5[6] + temp_sq6[6] + temp_sq7[6];
  temp_sq[7] = temp_sq1[7] + temp_sq2[7] + temp_sq3[7] + temp_sq4[7] + temp_sq5[7] + temp_sq6[7] + temp_sq7[7];

  p_fac1[0] = 0.7071067811865475*GammaV_sq[1]*gamma[1]+0.7071067811865475*GammaV_sq[0]*gamma[0]; 
  p_fac1[1] = 0.7071067811865475*GammaV_sq[0]*gamma[1]+0.7071067811865475*gamma[0]*GammaV_sq[1]; 
  p_fac1[2] = 0.7071067811865475*GammaV_sq[1]*gamma[4]+0.7071067811865475*GammaV_sq[0]*gamma[2]; 
  p_fac1[3] = 0.7071067811865475*GammaV_sq[1]*gamma[5]+0.7071067811865475*GammaV_sq[0]*gamma[3]; 
  p_fac1[4] = 0.7071067811865475*GammaV_sq[0]*gamma[4]+0.7071067811865475*GammaV_sq[1]*gamma[2]; 
  p_fac1[5] = 0.7071067811865475*GammaV_sq[0]*gamma[5]+0.7071067811865475*GammaV_sq[1]*gamma[3]; 
  p_fac1[6] = 0.7071067811865475*GammaV_sq[1]*gamma[7]+0.7071067811865475*GammaV_sq[0]*gamma[6]; 
  p_fac1[7] = 0.7071067811865475*GammaV_sq[0]*gamma[7]+0.7071067811865475*GammaV_sq[1]*gamma[6]; 

  p_fac2[0] = (-1.414213562373095*GammaV[1]*temp[1])-1.414213562373095*GammaV[0]*temp[0]; 
  p_fac2[1] = (-1.414213562373095*GammaV[0]*temp[1])-1.414213562373095*temp[0]*GammaV[1]; 
  p_fac2[2] = (-1.414213562373095*GammaV[1]*temp[4])-1.414213562373095*GammaV[0]*temp[2]; 
  p_fac2[3] = (-1.414213562373095*GammaV[1]*temp[5])-1.414213562373095*GammaV[0]*temp[3]; 
  p_fac2[4] = (-1.414213562373095*GammaV[0]*temp[4])-1.414213562373095*GammaV[1]*temp[2]; 
  p_fac2[5] = (-1.414213562373095*GammaV[0]*temp[5])-1.414213562373095*GammaV[1]*temp[3]; 
  p_fac2[6] = (-1.414213562373095*GammaV[1]*temp[7])-1.414213562373095*GammaV[0]*temp[6]; 
  p_fac2[7] = (-1.414213562373095*GammaV[0]*temp[7])-1.414213562373095*GammaV[1]*temp[6]; 

  p_fac3[0] = 0.3535533905932737*gamma_inv[7]*temp_sq[7]+0.3535533905932737*gamma_inv[6]*temp_sq[6]+0.3535533905932737*gamma_inv[5]*temp_sq[5]+0.3535533905932737*gamma_inv[4]*temp_sq[4]+0.3535533905932737*gamma_inv[3]*temp_sq[3]+0.3535533905932737*gamma_inv[2]*temp_sq[2]+0.3535533905932737*gamma_inv[1]*temp_sq[1]+0.3535533905932737*gamma_inv[0]*temp_sq[0]-1.0*gamma_inv[0]; 
  p_fac3[1] = 0.3535533905932737*gamma_inv[6]*temp_sq[7]+0.3535533905932737*temp_sq[6]*gamma_inv[7]+0.3535533905932737*gamma_inv[3]*temp_sq[5]+0.3535533905932737*temp_sq[3]*gamma_inv[5]+0.3535533905932737*gamma_inv[2]*temp_sq[4]+0.3535533905932737*temp_sq[2]*gamma_inv[4]+0.3535533905932737*gamma_inv[0]*temp_sq[1]+0.3535533905932737*temp_sq[0]*gamma_inv[1]-1.0*gamma_inv[1]; 
  p_fac3[2] = 0.3535533905932737*gamma_inv[5]*temp_sq[7]+0.3535533905932737*temp_sq[5]*gamma_inv[7]+0.3535533905932737*gamma_inv[3]*temp_sq[6]+0.3535533905932737*temp_sq[3]*gamma_inv[6]+0.3535533905932737*gamma_inv[1]*temp_sq[4]+0.3535533905932737*temp_sq[1]*gamma_inv[4]+0.3535533905932737*gamma_inv[0]*temp_sq[2]+0.3535533905932737*temp_sq[0]*gamma_inv[2]-1.0*gamma_inv[2]; 
  p_fac3[3] = 0.3535533905932737*gamma_inv[4]*temp_sq[7]+0.3535533905932737*temp_sq[4]*gamma_inv[7]+0.3535533905932737*gamma_inv[2]*temp_sq[6]+0.3535533905932737*temp_sq[2]*gamma_inv[6]+0.3535533905932737*gamma_inv[1]*temp_sq[5]+0.3535533905932737*temp_sq[1]*gamma_inv[5]+0.3535533905932737*gamma_inv[0]*temp_sq[3]+0.3535533905932737*temp_sq[0]*gamma_inv[3]-1.0*gamma_inv[3]; 
  p_fac3[4] = 0.3535533905932737*gamma_inv[3]*temp_sq[7]+0.3535533905932737*temp_sq[3]*gamma_inv[7]+0.3535533905932737*gamma_inv[5]*temp_sq[6]+0.3535533905932737*temp_sq[5]*gamma_inv[6]+0.3535533905932737*gamma_inv[0]*temp_sq[4]+0.3535533905932737*temp_sq[0]*gamma_inv[4]-1.0*gamma_inv[4]+0.3535533905932737*gamma_inv[1]*temp_sq[2]+0.3535533905932737*temp_sq[1]*gamma_inv[2]; 
  p_fac3[5] = 0.3535533905932737*gamma_inv[2]*temp_sq[7]+0.3535533905932737*temp_sq[2]*gamma_inv[7]+0.3535533905932737*gamma_inv[4]*temp_sq[6]+0.3535533905932737*temp_sq[4]*gamma_inv[6]+0.3535533905932737*gamma_inv[0]*temp_sq[5]+0.3535533905932737*temp_sq[0]*gamma_inv[5]-1.0*gamma_inv[5]+0.3535533905932737*gamma_inv[1]*temp_sq[3]+0.3535533905932737*temp_sq[1]*gamma_inv[3]; 
  p_fac3[6] = 0.3535533905932737*gamma_inv[1]*temp_sq[7]+0.3535533905932737*temp_sq[1]*gamma_inv[7]+0.3535533905932737*gamma_inv[0]*temp_sq[6]+0.3535533905932737*temp_sq[0]*gamma_inv[6]-1.0*gamma_inv[6]+0.3535533905932737*gamma_inv[4]*temp_sq[5]+0.3535533905932737*temp_sq[4]*gamma_inv[5]+0.3535533905932737*gamma_inv[2]*temp_sq[3]+0.3535533905932737*temp_sq[2]*gamma_inv[3]; 
  p_fac3[7] = 0.3535533905932737*gamma_inv[0]*temp_sq[7]+0.3535533905932737*temp_sq[0]*gamma_inv[7]-1.0*gamma_inv[7]+0.3535533905932737*gamma_inv[1]*temp_sq[6]+0.3535533905932737*temp_sq[1]*gamma_inv[6]+0.3535533905932737*gamma_inv[2]*temp_sq[5]+0.3535533905932737*temp_sq[2]*gamma_inv[5]+0.3535533905932737*gamma_inv[3]*temp_sq[4]+0.3535533905932737*temp_sq[3]*gamma_inv[4]; 

  p_fac[0] = p_fac1[0] + p_fac2[0] + p_fac3[0];
  p_fac[1] = p_fac1[1] + p_fac2[1] + p_fac3[1];
  p_fac[2] = p_fac1[2] + p_fac2[2] + p_fac3[2];
  p_fac[3] = p_fac1[3] + p_fac2[3] + p_fac3[3];
  p_fac[4] = p_fac1[4] + p_fac2[4] + p_fac3[4];
  p_fac[5] = p_fac1[5] + p_fac2[5] + p_fac3[5];
  p_fac[6] = p_fac1[6] + p_fac2[6] + p_fac3[6];
  p_fac[7] = p_fac1[7] + p_fac2[7] + p_fac3[7];

  gr_pressure[0] += (0.3535533905932737*f[7]*p_fac[7]+0.3535533905932737*f[6]*p_fac[6]+0.3535533905932737*f[5]*p_fac[5]+0.3535533905932737*f[4]*p_fac[4]+0.3535533905932737*f[3]*p_fac[3]+0.3535533905932737*f[2]*p_fac[2]+0.3535533905932737*f[1]*p_fac[1]+0.3535533905932737*f[0]*p_fac[0])*volFact; 
  gr_pressure[1] += (0.3535533905932737*f[6]*p_fac[7]+0.3535533905932737*p_fac[6]*f[7]+0.3535533905932737*f[3]*p_fac[5]+0.3535533905932737*p_fac[3]*f[5]+0.3535533905932737*f[2]*p_fac[4]+0.3535533905932737*p_fac[2]*f[4]+0.3535533905932737*f[0]*p_fac[1]+0.3535533905932737*p_fac[0]*f[1])*volFact; 
} 
