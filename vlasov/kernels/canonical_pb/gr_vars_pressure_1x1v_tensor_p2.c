#include <gkyl_canonical_pb_gr_Gamma_kernels.h> 
#include <gkyl_binop_mul_ser.h> 
GKYL_CU_DH void gr_vars_pressure_1x1v_tensor_p2(const double *w, const double *dxv, const double *h_ij_inv, const double *u_i, const double *u_i_sq, const double *GammaV, const double *GammaV_sq, const double *f, double* GKYL_RESTRICT gr_pressure) 
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
 
  double p_sq[9] = {0.0};
  const double *Hxx = &h_ij_inv[0]; 

  p_sq[0] = 1.414213562373095*Hxx[0]*wx1_sq+0.1178511301977579*Hxx[0]*dv1_sq; 
  p_sq[1] = 1.414213562373095*Hxx[1]*wx1_sq+0.1178511301977579*Hxx[1]*dv1_sq; 
  p_sq[2] = 0.8164965809277261*Hxx[0]*dv1*wx1; 
  p_sq[3] = 0.8164965809277261*Hxx[1]*dv1*wx1; 
  p_sq[4] = 1.414213562373095*Hxx[2]*wx1_sq+0.1178511301977579*Hxx[2]*dv1_sq; 
  p_sq[5] = 0.105409255338946*Hxx[0]*dv1_sq; 
  p_sq[6] = 0.816496580927726*Hxx[2]*dv1*wx1; 
  p_sq[7] = 0.105409255338946*Hxx[1]*dv1_sq; 
  p_sq[8] = 0.105409255338946*Hxx[2]*dv1_sq; 

  double gamma_nodal[9] = {0.0};
  double gamma_inv_nodal[9] = {0.0};
  double gamma[9] = {0.0};
  double gamma_inv[9] = {0.0};

  gamma_nodal[0] = sqrt(1.0 + 2.5*p_sq[8]-1.936491673103709*p_sq[7]-1.936491673103709*p_sq[6]+1.118033988749895*p_sq[5]+1.118033988749895*p_sq[4]+1.5*p_sq[3]-0.8660254037844386*p_sq[2]-0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[0] = 1.0/gamma_nodal[0];
  gamma_nodal[1] = sqrt(1.0 + (-1.25*p_sq[8])+0.9682458365518543*p_sq[6]+1.118033988749895*p_sq[5]-0.5590169943749475*p_sq[4]-0.8660254037844386*p_sq[2]+0.5*p_sq[0]);
  gamma_inv_nodal[1] = 1.0/gamma_nodal[1];
  gamma_nodal[2] = sqrt(1.0 + 2.5*p_sq[8]+1.936491673103709*p_sq[7]-1.936491673103709*p_sq[6]+1.118033988749895*p_sq[5]+1.118033988749895*p_sq[4]-1.5*p_sq[3]-0.8660254037844386*p_sq[2]+0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[2] = 1.0/gamma_nodal[2];
  gamma_nodal[3] = sqrt(1.0 + (-1.25*p_sq[8])+0.9682458365518543*p_sq[7]-0.5590169943749475*p_sq[5]+1.118033988749895*p_sq[4]-0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[3] = 1.0/gamma_nodal[3];
  gamma_nodal[4] = sqrt(1.0 + 0.625*p_sq[8]-0.5590169943749475*p_sq[5]-0.5590169943749475*p_sq[4]+0.5*p_sq[0]);
  gamma_inv_nodal[4] = 1.0/gamma_nodal[4];
  gamma_nodal[5] = sqrt(1.0 + (-1.25*p_sq[8])-0.9682458365518543*p_sq[7]-0.5590169943749475*p_sq[5]+1.118033988749895*p_sq[4]+0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[5] = 1.0/gamma_nodal[5];
  gamma_nodal[6] = sqrt(1.0 + 2.5*p_sq[8]-1.936491673103709*p_sq[7]+1.936491673103709*p_sq[6]+1.118033988749895*p_sq[5]+1.118033988749895*p_sq[4]-1.5*p_sq[3]+0.8660254037844386*p_sq[2]-0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[6] = 1.0/gamma_nodal[6];
  gamma_nodal[7] = sqrt(1.0 + (-1.25*p_sq[8])-0.9682458365518543*p_sq[6]+1.118033988749895*p_sq[5]-0.5590169943749475*p_sq[4]+0.8660254037844386*p_sq[2]+0.5*p_sq[0]);
  gamma_inv_nodal[7] = 1.0/gamma_nodal[7];
  gamma_nodal[8] = sqrt(1.0 + 2.5*p_sq[8]+1.936491673103709*p_sq[7]+1.936491673103709*p_sq[6]+1.118033988749895*p_sq[5]+1.118033988749895*p_sq[4]+1.5*p_sq[3]+0.8660254037844386*p_sq[2]+0.8660254037844386*p_sq[1]+0.5*p_sq[0]);
  gamma_inv_nodal[8] = 1.0/gamma_nodal[8];

  gamma[0] = 0.05555555555555555*gamma_nodal[8]+0.2222222222222222*gamma_nodal[7]+0.05555555555555555*gamma_nodal[6]+0.2222222222222222*gamma_nodal[5]+0.8888888888888888*gamma_nodal[4]+0.2222222222222222*gamma_nodal[3]+0.05555555555555555*gamma_nodal[2]+0.2222222222222222*gamma_nodal[1]+0.05555555555555555*gamma_nodal[0]; 
  gamma[1] = 0.09622504486493764*gamma_nodal[8]-0.09622504486493764*gamma_nodal[6]+0.3849001794597506*gamma_nodal[5]-0.3849001794597506*gamma_nodal[3]+0.09622504486493764*gamma_nodal[2]-0.09622504486493764*gamma_nodal[0]; 
  gamma[2] = 0.09622504486493764*gamma_nodal[8]+0.3849001794597506*gamma_nodal[7]+0.09622504486493764*gamma_nodal[6]-0.09622504486493764*gamma_nodal[2]-0.3849001794597506*gamma_nodal[1]-0.09622504486493764*gamma_nodal[0]; 
  gamma[3] = 0.1666666666666667*gamma_nodal[8]-0.1666666666666667*gamma_nodal[6]-0.1666666666666667*gamma_nodal[2]+0.1666666666666667*gamma_nodal[0]; 
  gamma[4] = 0.04969039949999532*gamma_nodal[8]-0.09938079899999064*gamma_nodal[7]+0.04969039949999532*gamma_nodal[6]+0.1987615979999813*gamma_nodal[5]-0.3975231959999626*gamma_nodal[4]+0.1987615979999813*gamma_nodal[3]+0.04969039949999532*gamma_nodal[2]-0.09938079899999064*gamma_nodal[1]+0.04969039949999532*gamma_nodal[0]; 
  gamma[5] = 0.04969039949999532*gamma_nodal[8]+0.1987615979999813*gamma_nodal[7]+0.04969039949999532*gamma_nodal[6]-0.09938079899999064*gamma_nodal[5]-0.3975231959999626*gamma_nodal[4]-0.09938079899999064*gamma_nodal[3]+0.04969039949999532*gamma_nodal[2]+0.1987615979999813*gamma_nodal[1]+0.04969039949999532*gamma_nodal[0]; 
  gamma[6] = 0.08606629658238703*gamma_nodal[8]-0.1721325931647741*gamma_nodal[7]+0.08606629658238703*gamma_nodal[6]-0.08606629658238703*gamma_nodal[2]+0.1721325931647741*gamma_nodal[1]-0.08606629658238703*gamma_nodal[0]; 
  gamma[7] = 0.08606629658238703*gamma_nodal[8]-0.08606629658238703*gamma_nodal[6]-0.1721325931647741*gamma_nodal[5]+0.1721325931647741*gamma_nodal[3]+0.08606629658238703*gamma_nodal[2]-0.08606629658238703*gamma_nodal[0]; 
  gamma[8] = 0.04444444444444445*gamma_nodal[8]-0.08888888888888889*gamma_nodal[7]+0.04444444444444445*gamma_nodal[6]-0.08888888888888889*gamma_nodal[5]+0.1777777777777778*gamma_nodal[4]-0.08888888888888889*gamma_nodal[3]+0.04444444444444445*gamma_nodal[2]-0.08888888888888889*gamma_nodal[1]+0.04444444444444445*gamma_nodal[0]; 

  gamma_inv[0] = 0.05555555555555555*gamma_inv_nodal[8]+0.2222222222222222*gamma_inv_nodal[7]+0.05555555555555555*gamma_inv_nodal[6]+0.2222222222222222*gamma_inv_nodal[5]+0.8888888888888888*gamma_inv_nodal[4]+0.2222222222222222*gamma_inv_nodal[3]+0.05555555555555555*gamma_inv_nodal[2]+0.2222222222222222*gamma_inv_nodal[1]+0.05555555555555555*gamma_inv_nodal[0]; 
  gamma_inv[1] = 0.09622504486493764*gamma_inv_nodal[8]-0.09622504486493764*gamma_inv_nodal[6]+0.3849001794597506*gamma_inv_nodal[5]-0.3849001794597506*gamma_inv_nodal[3]+0.09622504486493764*gamma_inv_nodal[2]-0.09622504486493764*gamma_inv_nodal[0]; 
  gamma_inv[2] = 0.09622504486493764*gamma_inv_nodal[8]+0.3849001794597506*gamma_inv_nodal[7]+0.09622504486493764*gamma_inv_nodal[6]-0.09622504486493764*gamma_inv_nodal[2]-0.3849001794597506*gamma_inv_nodal[1]-0.09622504486493764*gamma_inv_nodal[0]; 
  gamma_inv[3] = 0.1666666666666667*gamma_inv_nodal[8]-0.1666666666666667*gamma_inv_nodal[6]-0.1666666666666667*gamma_inv_nodal[2]+0.1666666666666667*gamma_inv_nodal[0]; 
  gamma_inv[4] = 0.04969039949999532*gamma_inv_nodal[8]-0.09938079899999064*gamma_inv_nodal[7]+0.04969039949999532*gamma_inv_nodal[6]+0.1987615979999813*gamma_inv_nodal[5]-0.3975231959999626*gamma_inv_nodal[4]+0.1987615979999813*gamma_inv_nodal[3]+0.04969039949999532*gamma_inv_nodal[2]-0.09938079899999064*gamma_inv_nodal[1]+0.04969039949999532*gamma_inv_nodal[0]; 
  gamma_inv[5] = 0.04969039949999532*gamma_inv_nodal[8]+0.1987615979999813*gamma_inv_nodal[7]+0.04969039949999532*gamma_inv_nodal[6]-0.09938079899999064*gamma_inv_nodal[5]-0.3975231959999626*gamma_inv_nodal[4]-0.09938079899999064*gamma_inv_nodal[3]+0.04969039949999532*gamma_inv_nodal[2]+0.1987615979999813*gamma_inv_nodal[1]+0.04969039949999532*gamma_inv_nodal[0]; 
  gamma_inv[6] = 0.08606629658238703*gamma_inv_nodal[8]-0.1721325931647741*gamma_inv_nodal[7]+0.08606629658238703*gamma_inv_nodal[6]-0.08606629658238703*gamma_inv_nodal[2]+0.1721325931647741*gamma_inv_nodal[1]-0.08606629658238703*gamma_inv_nodal[0]; 
  gamma_inv[7] = 0.08606629658238703*gamma_inv_nodal[8]-0.08606629658238703*gamma_inv_nodal[6]-0.1721325931647741*gamma_inv_nodal[5]+0.1721325931647741*gamma_inv_nodal[3]+0.08606629658238703*gamma_inv_nodal[2]-0.08606629658238703*gamma_inv_nodal[0]; 
  gamma_inv[8] = 0.04444444444444445*gamma_inv_nodal[8]-0.08888888888888889*gamma_inv_nodal[7]+0.04444444444444445*gamma_inv_nodal[6]-0.08888888888888889*gamma_inv_nodal[5]+0.1777777777777778*gamma_inv_nodal[4]-0.08888888888888889*gamma_inv_nodal[3]+0.04444444444444445*gamma_inv_nodal[2]-0.08888888888888889*gamma_inv_nodal[1]+0.04444444444444445*gamma_inv_nodal[0]; 

  double temp[9] = {0.0}; 
  double temp_sq[9] = {0.0}; 
  double p_fac[9] = {0.0}; 
  double Hxx_sq[3] = {0.0}; 
  binop_mul_1d_ser_p2(Hxx, Hxx, Hxx_sq); 
  temp[0] = 1.414213562373095*V_0[0]*wx1; 
  temp[1] = 1.414213562373095*V_0[1]*wx1; 
  temp[2] = 0.408248290463863*V_0[0]*dv1; 
  temp[3] = 0.408248290463863*V_0[1]*dv1; 
  temp[4] = 1.414213562373095*V_0[2]*wx1; 
  temp[6] = 0.408248290463863*V_0[2]*dv1; 

  temp_sq[0] = 1.414213562373095*V_0_sq[0]*wx1_sq+0.1178511301977579*V_0_sq[0]*dv1_sq; 
  temp_sq[1] = 1.414213562373095*V_0_sq[1]*wx1_sq+0.1178511301977579*V_0_sq[1]*dv1_sq; 
  temp_sq[2] = 0.8164965809277261*V_0_sq[0]*dv1*wx1; 
  temp_sq[3] = 0.8164965809277261*V_0_sq[1]*dv1*wx1; 
  temp_sq[4] = 1.414213562373095*V_0_sq[2]*wx1_sq+0.1178511301977579*V_0_sq[2]*dv1_sq; 
  temp_sq[5] = 0.105409255338946*V_0_sq[0]*dv1_sq; 
  temp_sq[6] = 0.816496580927726*V_0_sq[2]*dv1*wx1; 
  temp_sq[7] = 0.105409255338946*V_0_sq[1]*dv1_sq; 
  temp_sq[8] = 0.105409255338946*V_0_sq[2]*dv1_sq; 

  p_fac[0] = 0.5*gamma_inv[8]*temp_sq[8]+0.5*gamma_inv[7]*temp_sq[7]+0.5*gamma_inv[6]*temp_sq[6]+0.5*gamma_inv[5]*temp_sq[5]+0.7071067811865475*GammaV_sq[2]*gamma[4]+0.5*gamma_inv[4]*temp_sq[4]-1.414213562373095*GammaV[2]*temp[4]+0.5*gamma_inv[3]*temp_sq[3]+0.5*gamma_inv[2]*temp_sq[2]+0.7071067811865475*GammaV_sq[1]*gamma[1]+0.5*gamma_inv[1]*temp_sq[1]-1.414213562373095*GammaV[1]*temp[1]+0.7071067811865475*GammaV_sq[0]*gamma[0]+0.5*gamma_inv[0]*temp_sq[0]-1.414213562373095*GammaV[0]*temp[0]-1.0*gamma_inv[0]; 
  p_fac[1] = 0.447213595499958*gamma_inv[7]*temp_sq[8]+0.447213595499958*temp_sq[7]*gamma_inv[8]+0.5000000000000001*gamma_inv[5]*temp_sq[7]+0.5000000000000001*temp_sq[5]*gamma_inv[7]+0.447213595499958*gamma_inv[3]*temp_sq[6]+0.447213595499958*temp_sq[3]*gamma_inv[6]+0.6324555320336759*GammaV_sq[1]*gamma[4]+0.4472135954999579*gamma_inv[1]*temp_sq[4]-1.264911064067352*GammaV[1]*temp[4]+0.4472135954999579*temp_sq[1]*gamma_inv[4]+0.5*gamma_inv[2]*temp_sq[3]+0.5*temp_sq[2]*gamma_inv[3]+0.6324555320336759*gamma[1]*GammaV_sq[2]-1.264911064067352*temp[1]*GammaV[2]+0.7071067811865475*GammaV_sq[0]*gamma[1]+0.5*gamma_inv[0]*temp_sq[1]-1.414213562373095*GammaV[0]*temp[1]+0.5*temp_sq[0]*gamma_inv[1]-1.0*gamma_inv[1]+0.7071067811865475*gamma[0]*GammaV_sq[1]-1.414213562373095*temp[0]*GammaV[1]; 
  p_fac[2] = 0.447213595499958*gamma_inv[6]*temp_sq[8]+0.447213595499958*temp_sq[6]*gamma_inv[8]+0.447213595499958*gamma_inv[3]*temp_sq[7]+0.447213595499958*temp_sq[3]*gamma_inv[7]+0.7071067811865475*GammaV_sq[2]*gamma[6]+0.5000000000000001*gamma_inv[4]*temp_sq[6]-1.414213562373095*GammaV[2]*temp[6]+0.5000000000000001*temp_sq[4]*gamma_inv[6]+0.4472135954999579*gamma_inv[2]*temp_sq[5]+0.4472135954999579*temp_sq[2]*gamma_inv[5]+0.7071067811865475*GammaV_sq[1]*gamma[3]+0.5*gamma_inv[1]*temp_sq[3]-1.414213562373095*GammaV[1]*temp[3]+0.5*temp_sq[1]*gamma_inv[3]+0.7071067811865475*GammaV_sq[0]*gamma[2]+0.5*gamma_inv[0]*temp_sq[2]-1.414213562373095*GammaV[0]*temp[2]+0.5*temp_sq[0]*gamma_inv[2]-1.0*gamma_inv[2]; 
  p_fac[3] = 0.4*gamma_inv[3]*temp_sq[8]+0.4*temp_sq[3]*gamma_inv[8]+0.4*gamma_inv[6]*temp_sq[7]+0.447213595499958*gamma_inv[2]*temp_sq[7]+0.4*temp_sq[6]*gamma_inv[7]+0.447213595499958*temp_sq[2]*gamma_inv[7]+0.632455532033676*GammaV_sq[1]*gamma[6]+0.447213595499958*gamma_inv[1]*temp_sq[6]-1.264911064067352*GammaV[1]*temp[6]+0.447213595499958*temp_sq[1]*gamma_inv[6]+0.4472135954999579*gamma_inv[3]*temp_sq[5]+0.4472135954999579*temp_sq[3]*gamma_inv[5]+0.4472135954999579*gamma_inv[3]*temp_sq[4]+0.4472135954999579*temp_sq[3]*gamma_inv[4]+0.6324555320336759*GammaV_sq[2]*gamma[3]+0.7071067811865475*GammaV_sq[0]*gamma[3]+0.5*gamma_inv[0]*temp_sq[3]-1.264911064067352*GammaV[2]*temp[3]-1.414213562373095*GammaV[0]*temp[3]+0.5*temp_sq[0]*gamma_inv[3]-1.0*gamma_inv[3]+0.7071067811865475*GammaV_sq[1]*gamma[2]+0.5*gamma_inv[1]*temp_sq[2]-1.414213562373095*GammaV[1]*temp[2]+0.5*temp_sq[1]*gamma_inv[2]; 
  p_fac[4] = 0.31943828249997*gamma_inv[8]*temp_sq[8]+0.5*gamma_inv[5]*temp_sq[8]+0.5*temp_sq[5]*gamma_inv[8]+0.4472135954999579*gamma_inv[7]*temp_sq[7]+0.31943828249997*gamma_inv[6]*temp_sq[6]+0.5000000000000001*gamma_inv[2]*temp_sq[6]+0.5000000000000001*temp_sq[2]*gamma_inv[6]+0.4517539514526256*GammaV_sq[2]*gamma[4]+0.7071067811865475*GammaV_sq[0]*gamma[4]+0.31943828249997*gamma_inv[4]*temp_sq[4]+0.5*gamma_inv[0]*temp_sq[4]-0.9035079029052515*GammaV[2]*temp[4]-1.414213562373095*GammaV[0]*temp[4]+0.5*temp_sq[0]*gamma_inv[4]-1.0*gamma_inv[4]+0.4472135954999579*gamma_inv[3]*temp_sq[3]+0.7071067811865475*gamma[0]*GammaV_sq[2]-1.414213562373095*temp[0]*GammaV[2]+0.6324555320336759*GammaV_sq[1]*gamma[1]+0.4472135954999579*gamma_inv[1]*temp_sq[1]-1.264911064067352*GammaV[1]*temp[1]; 
  p_fac[5] = 0.7071067811865475*GammaV_sq[2]*gamma[8]+0.31943828249997*gamma_inv[8]*temp_sq[8]+0.5*gamma_inv[4]*temp_sq[8]+0.5*temp_sq[4]*gamma_inv[8]+0.7071067811865475*GammaV_sq[1]*gamma[7]+0.31943828249997*gamma_inv[7]*temp_sq[7]+0.5000000000000001*gamma_inv[1]*temp_sq[7]+0.5000000000000001*temp_sq[1]*gamma_inv[7]+0.4472135954999579*gamma_inv[6]*temp_sq[6]+0.7071067811865475*GammaV_sq[0]*gamma[5]+0.31943828249997*gamma_inv[5]*temp_sq[5]+0.5*gamma_inv[0]*temp_sq[5]+0.5*temp_sq[0]*gamma_inv[5]-1.0*gamma_inv[5]+0.4472135954999579*gamma_inv[3]*temp_sq[3]+0.4472135954999579*gamma_inv[2]*temp_sq[2]; 
  p_fac[6] = 0.2857142857142857*gamma_inv[6]*temp_sq[8]+0.447213595499958*gamma_inv[2]*temp_sq[8]+0.2857142857142857*temp_sq[6]*gamma_inv[8]+0.447213595499958*temp_sq[2]*gamma_inv[8]+0.4*gamma_inv[3]*temp_sq[7]+0.4*temp_sq[3]*gamma_inv[7]+0.4517539514526256*GammaV_sq[2]*gamma[6]+0.7071067811865475*GammaV_sq[0]*gamma[6]+0.4472135954999579*gamma_inv[5]*temp_sq[6]+0.31943828249997*gamma_inv[4]*temp_sq[6]+0.5*gamma_inv[0]*temp_sq[6]-0.9035079029052515*GammaV[2]*temp[6]-1.414213562373095*GammaV[0]*temp[6]+0.4472135954999579*temp_sq[5]*gamma_inv[6]+0.31943828249997*temp_sq[4]*gamma_inv[6]+0.5*temp_sq[0]*gamma_inv[6]-1.0*gamma_inv[6]+0.5000000000000001*gamma_inv[2]*temp_sq[4]+0.5000000000000001*temp_sq[2]*gamma_inv[4]+0.632455532033676*GammaV_sq[1]*gamma[3]+0.447213595499958*gamma_inv[1]*temp_sq[3]-1.264911064067352*GammaV[1]*temp[3]+0.447213595499958*temp_sq[1]*gamma_inv[3]+0.7071067811865475*GammaV_sq[2]*gamma[2]-1.414213562373095*GammaV[2]*temp[2]; 
  p_fac[7] = 0.632455532033676*GammaV_sq[1]*gamma[8]+0.2857142857142857*gamma_inv[7]*temp_sq[8]+0.447213595499958*gamma_inv[1]*temp_sq[8]+0.2857142857142857*temp_sq[7]*gamma_inv[8]+0.447213595499958*temp_sq[1]*gamma_inv[8]+0.6324555320336759*GammaV_sq[2]*gamma[7]+0.7071067811865475*GammaV_sq[0]*gamma[7]+0.31943828249997*gamma_inv[5]*temp_sq[7]+0.4472135954999579*gamma_inv[4]*temp_sq[7]+0.5*gamma_inv[0]*temp_sq[7]+0.31943828249997*temp_sq[5]*gamma_inv[7]+0.4472135954999579*temp_sq[4]*gamma_inv[7]+0.5*temp_sq[0]*gamma_inv[7]-1.0*gamma_inv[7]+0.4*gamma_inv[3]*temp_sq[6]+0.4*temp_sq[3]*gamma_inv[6]+0.7071067811865475*GammaV_sq[1]*gamma[5]+0.5000000000000001*gamma_inv[1]*temp_sq[5]+0.5000000000000001*temp_sq[1]*gamma_inv[5]+0.447213595499958*gamma_inv[2]*temp_sq[3]+0.447213595499958*temp_sq[2]*gamma_inv[3]; 
  p_fac[8] = 0.4517539514526256*GammaV_sq[2]*gamma[8]+0.7071067811865475*GammaV_sq[0]*gamma[8]+0.2040816326530612*gamma_inv[8]*temp_sq[8]+0.31943828249997*gamma_inv[5]*temp_sq[8]+0.31943828249997*gamma_inv[4]*temp_sq[8]+0.5*gamma_inv[0]*temp_sq[8]+0.31943828249997*temp_sq[5]*gamma_inv[8]+0.31943828249997*temp_sq[4]*gamma_inv[8]+0.5*temp_sq[0]*gamma_inv[8]-1.0*gamma_inv[8]+0.632455532033676*GammaV_sq[1]*gamma[7]+0.2857142857142857*gamma_inv[7]*temp_sq[7]+0.447213595499958*gamma_inv[1]*temp_sq[7]+0.447213595499958*temp_sq[1]*gamma_inv[7]+0.2857142857142857*gamma_inv[6]*temp_sq[6]+0.447213595499958*gamma_inv[2]*temp_sq[6]+0.447213595499958*temp_sq[2]*gamma_inv[6]+0.7071067811865475*GammaV_sq[2]*gamma[5]+0.5*gamma_inv[4]*temp_sq[5]+0.5*temp_sq[4]*gamma_inv[5]+0.4*gamma_inv[3]*temp_sq[3]; 

  gr_pressure[0] += (0.7071067811865475*f[8]*p_fac[8]+0.7071067811865475*f[7]*p_fac[7]+0.7071067811865475*f[6]*p_fac[6]+0.7071067811865475*f[5]*p_fac[5]+0.7071067811865475*f[4]*p_fac[4]+0.7071067811865475*f[3]*p_fac[3]+0.7071067811865475*f[2]*p_fac[2]+0.7071067811865475*f[1]*p_fac[1]+0.7071067811865475*f[0]*p_fac[0])*volFact; 
  gr_pressure[1] += (0.632455532033676*f[7]*p_fac[8]+0.632455532033676*p_fac[7]*f[8]+0.7071067811865475*f[5]*p_fac[7]+0.7071067811865475*p_fac[5]*f[7]+0.632455532033676*f[3]*p_fac[6]+0.632455532033676*p_fac[3]*f[6]+0.6324555320336759*f[1]*p_fac[4]+0.6324555320336759*p_fac[1]*f[4]+0.7071067811865475*f[2]*p_fac[3]+0.7071067811865475*p_fac[2]*f[3]+0.7071067811865475*f[0]*p_fac[1]+0.7071067811865475*p_fac[0]*f[1])*volFact; 
  gr_pressure[2] += (0.4517539514526256*f[8]*p_fac[8]+0.7071067811865475*f[5]*p_fac[8]+0.7071067811865475*p_fac[5]*f[8]+0.6324555320336759*f[7]*p_fac[7]+0.4517539514526256*f[6]*p_fac[6]+0.7071067811865475*f[2]*p_fac[6]+0.7071067811865475*p_fac[2]*f[6]+0.4517539514526256*f[4]*p_fac[4]+0.7071067811865475*f[0]*p_fac[4]+0.7071067811865475*p_fac[0]*f[4]+0.6324555320336759*f[3]*p_fac[3]+0.6324555320336759*f[1]*p_fac[1])*volFact; 
} 
