#include <gkyl_canonical_pb_gr_Gamma_kernels.h> 
#include <gkyl_binop_mul_ser.h> 
GKYL_CU_DH void gr_vars_pressure_1x1v_tensor_p1(const double *w, const double *dxv, const double *h_ij_inv, const double *u_i, const double *u_i_sq, const double *GammaV, const double *GammaV_sq, const double *f, double* GKYL_RESTRICT gr_pressure) 
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
  const double volFact = dxv[1]/2; 
 
  const double wx1 = w[1], dv1 = dxv[1]; 
  const double wx1_sq = wx1*wx1, dv1_sq = dv1*dv1; 
  const double *V_0 = &u_i[0]; 
  const double *V_0_sq = &u_i_sq[0]; 
 
  double p_sq[4] = {0.0};
  const double *Hxx = &h_ij_inv[0]; 

  p_sq[0] = 1.414213562373095*Hxx[0]*wx1_sq+0.1178511301977579*Hxx[0]*dv1_sq; 
  p_sq[1] = 1.414213562373095*Hxx[1]*wx1_sq+0.1178511301977579*Hxx[1]*dv1_sq; 
  p_sq[2] = 0.8164965809277261*Hxx[0]*dv1*wx1; 
  p_sq[3] = 0.8164965809277261*Hxx[1]*dv1*wx1; 

  double gamma_nodal[4] = {0.0};
  double gamma_inv_nodal[4] = {0.0};
  double gamma[4] = {0.0};
  double gamma_inv[4] = {0.0};

  gamma_nodal[0] = sqrt(1.0 + 1.5*p_sq[3]-0.8660254037844386*p_sq[2]-0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[0] = 1.0/gamma_nodal[0];
  gamma_nodal[1] = sqrt(1.0 + (-1.5*p_sq[3])-0.8660254037844386*p_sq[2]+0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[1] = 1.0/gamma_nodal[1];
  gamma_nodal[2] = sqrt(1.0 + (-1.5*p_sq[3])+0.8660254037844386*p_sq[2]-0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[2] = 1.0/gamma_nodal[2];
  gamma_nodal[3] = sqrt(1.0 + 1.5*p_sq[3]+0.8660254037844386*p_sq[2]+0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[3] = 1.0/gamma_nodal[3];

  gamma[0] = 0.5*gamma_nodal[3]+0.5*gamma_nodal[2]+0.5*gamma_nodal[1]+0.5*gamma_nodal[0]; 
  gamma[1] = 0.2886751345948129*gamma_nodal[3]-0.2886751345948129*gamma_nodal[2]+0.2886751345948129*gamma_nodal[1]-0.2886751345948129*gamma_nodal[0]; 
  gamma[2] = 0.2886751345948129*gamma_nodal[3]+0.2886751345948129*gamma_nodal[2]-0.2886751345948129*gamma_nodal[1]-0.2886751345948129*gamma_nodal[0]; 
  gamma[3] = 0.1666666666666667*gamma_nodal[3]-0.1666666666666667*gamma_nodal[2]-0.1666666666666667*gamma_nodal[1]+0.1666666666666667*gamma_nodal[0]; 

  gamma_inv[0] = 0.5*gamma_inv_nodal[3]+0.5*gamma_inv_nodal[2]+0.5*gamma_inv_nodal[1]+0.5*gamma_inv_nodal[0]; 
  gamma_inv[1] = 0.2886751345948129*gamma_inv_nodal[3]-0.2886751345948129*gamma_inv_nodal[2]+0.2886751345948129*gamma_inv_nodal[1]-0.2886751345948129*gamma_inv_nodal[0]; 
  gamma_inv[2] = 0.2886751345948129*gamma_inv_nodal[3]+0.2886751345948129*gamma_inv_nodal[2]-0.2886751345948129*gamma_inv_nodal[1]-0.2886751345948129*gamma_inv_nodal[0]; 
  gamma_inv[3] = 0.1666666666666667*gamma_inv_nodal[3]-0.1666666666666667*gamma_inv_nodal[2]-0.1666666666666667*gamma_inv_nodal[1]+0.1666666666666667*gamma_inv_nodal[0]; 

  double temp[4] = {0.0}; 
  double temp_sq[4] = {0.0}; 
  double p_fac[4] = {0.0}; 
  double Hxx_sq[2] = {0.0}; 
  binop_mul_1d_ser_p1(Hxx, Hxx, Hxx_sq); 
  temp[0] = 1.414213562373095*V_0[0]*wx1; 
  temp[1] = 1.414213562373095*V_0[1]*wx1; 
  temp[2] = 0.408248290463863*V_0[0]*dv1; 
  temp[3] = 0.408248290463863*V_0[1]*dv1; 

  temp_sq[0] = 1.414213562373095*V_0_sq[0]*wx1_sq+0.1178511301977579*V_0_sq[0]*dv1_sq; 
  temp_sq[1] = 1.414213562373095*V_0_sq[1]*wx1_sq+0.1178511301977579*V_0_sq[1]*dv1_sq; 
  temp_sq[2] = 0.8164965809277261*V_0_sq[0]*dv1*wx1; 
  temp_sq[3] = 0.8164965809277261*V_0_sq[1]*dv1*wx1; 

  p_fac[0] = 0.5*gamma_inv[3]*temp_sq[3]+0.5*gamma_inv[2]*temp_sq[2]+0.7071067811865475*GammaV_sq[1]*gamma[1]+0.5*gamma_inv[1]*temp_sq[1]-1.414213562373095*GammaV[1]*temp[1]+0.7071067811865475*GammaV_sq[0]*gamma[0]+0.5*gamma_inv[0]*temp_sq[0]-1.414213562373095*GammaV[0]*temp[0]-1.0*gamma_inv[0]; 
  p_fac[1] = 0.5*gamma_inv[2]*temp_sq[3]+0.5*temp_sq[2]*gamma_inv[3]+0.7071067811865475*GammaV_sq[0]*gamma[1]+0.5*gamma_inv[0]*temp_sq[1]-1.414213562373095*GammaV[0]*temp[1]+0.5*temp_sq[0]*gamma_inv[1]-1.0*gamma_inv[1]+0.7071067811865475*gamma[0]*GammaV_sq[1]-1.414213562373095*temp[0]*GammaV[1]; 
  p_fac[2] = 0.7071067811865475*GammaV_sq[1]*gamma[3]+0.5*gamma_inv[1]*temp_sq[3]-1.414213562373095*GammaV[1]*temp[3]+0.5*temp_sq[1]*gamma_inv[3]+0.7071067811865475*GammaV_sq[0]*gamma[2]+0.5*gamma_inv[0]*temp_sq[2]-1.414213562373095*GammaV[0]*temp[2]+0.5*temp_sq[0]*gamma_inv[2]-1.0*gamma_inv[2]; 
  p_fac[3] = 0.7071067811865475*GammaV_sq[0]*gamma[3]+0.5*gamma_inv[0]*temp_sq[3]-1.414213562373095*GammaV[0]*temp[3]+0.5*temp_sq[0]*gamma_inv[3]-1.0*gamma_inv[3]+0.7071067811865475*GammaV_sq[1]*gamma[2]+0.5*gamma_inv[1]*temp_sq[2]-1.414213562373095*GammaV[1]*temp[2]+0.5*temp_sq[1]*gamma_inv[2]; 

  gr_pressure[0] += (0.7071067811865475*f[3]*p_fac[3]+0.7071067811865475*f[2]*p_fac[2]+0.7071067811865475*f[1]*p_fac[1]+0.7071067811865475*f[0]*p_fac[0])*volFact; 
  gr_pressure[1] += (0.7071067811865475*f[2]*p_fac[3]+0.7071067811865475*p_fac[2]*f[3]+0.7071067811865475*f[0]*p_fac[1]+0.7071067811865475*p_fac[0]*f[1])*volFact; 
} 
