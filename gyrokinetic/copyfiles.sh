#!/bin/sh

CP_CMD=cp
RM_CMD=rm
G0=../../gkylzero

# data
mkdir -p data/adas
$CP_CMD $G0/data/adas/adas_to_numpy.py data/adas/
$CP_CMD $G0/data/adas/adf11.py data/adas/
$CP_CMD $G0/data/adas/download_adas.py data/adas/
$CP_CMD $G0/data/adas/radiation_fit_parameters.txt data/adas/
$CP_CMD $G0/data/adas/read_adas.c data/adas/
$CP_CMD $G0/data/adas/read_adas.h data/adas/
$CP_CMD $G0/data/adas/read_radiation.py data/adas/
$CP_CMD $G0/data/adas/README.md data/adas/

$RM_CMD $G0/data/adas/adas_to_numpy.py
$RM_CMD $G0/data/adas/adf11.py
$RM_CMD $G0/data/adas/download_adas.py
$RM_CMD $G0/data/adas/radiation_fit_parameters.txt
$RM_CMD $G0/data/adas/read_adas.c
$RM_CMD $G0/data/adas/read_adas.h
$RM_CMD $G0/data/adas/read_radiation.py
$RM_CMD $G0/data/adas/README.md

# kernels
mkdir -p kernels/ambi_bolt_potential
$CP_CMD $G0/kernels/ambi_bolt_potential/*.h kernels/ambi_bolt_potential/
$CP_CMD $G0/kernels/ambi_bolt_potential/*.c kernels/ambi_bolt_potential/
mkdir -p kernels/bgk
$CP_CMD $G0/kernels/bgk/*.h kernels/bgk/
$CP_CMD $G0/kernels/bgk/*.c kernels/bgk/
mkdir -p kernels/deflate_geo
$CP_CMD $G0/kernels/deflate_geo/*.h kernels/deflate_geo/
$CP_CMD $G0/kernels/deflate_geo/*.c kernels/deflate_geo/
mkdir -p kernels/deflate_surf
$CP_CMD $G0/kernels/deflate_surf/*.h kernels/deflate_surf/
$CP_CMD $G0/kernels/deflate_surf/*.c kernels/deflate_surf/
mkdir -p kernels/derived_geo
$CP_CMD $G0/kernels/derived_geo/*.h kernels/derived_geo/
$CP_CMD $G0/kernels/derived_geo/*.c kernels/derived_geo/
mkdir -p kernels/dg_diffusion_gyrokinetic
$CP_CMD $G0/kernels/dg_diffusion_gyrokinetic/*.h kernels/dg_diffusion_gyrokinetic/
$CP_CMD $G0/kernels/dg_diffusion_gyrokinetic/*.c kernels/dg_diffusion_gyrokinetic/
mkdir -p kernels/fem_parproj
$CP_CMD $G0/kernels/fem_parproj/*.h kernels/fem_parproj/
$CP_CMD $G0/kernels/fem_parproj/*.c kernels/fem_parproj/
mkdir -p kernels/fem_poisson_perp
$CP_CMD $G0/kernels/fem_poisson_perp/*.h kernels/fem_poisson_perp/
$CP_CMD $G0/kernels/fem_poisson_perp/*.c kernels/fem_poisson_perp/
mkdir -p kernels/gyrokinetic
$CP_CMD $G0/kernels/gyrokinetic/*.h kernels/gyrokinetic/
$CP_CMD $G0/kernels/gyrokinetic/*.c kernels/gyrokinetic/
mkdir -p kernels/gyrokinetic_pol_density
$CP_CMD $G0/kernels/gyrokinetic_pol_density/*.h kernels/gyrokinetic_pol_density/
$CP_CMD $G0/kernels/gyrokinetic_pol_density/*.c kernels/gyrokinetic_pol_density/
mkdir -p kernels/inflate_surf
$CP_CMD $G0/kernels/inflate_surf/*.h kernels/inflate_surf/
$CP_CMD $G0/kernels/inflate_surf/*.c kernels/inflate_surf/
mkdir -p kernels/neutral
$CP_CMD $G0/kernels/neutral/*.h kernels/neutral/
$CP_CMD $G0/kernels/neutral/*.c kernels/neutral/
mkdir -p kernels/positivity_shift
$CP_CMD $G0/kernels/positivity_shift/*.h kernels/positivity_shift/
$CP_CMD $G0/kernels/positivity_shift/*.c kernels/positivity_shift/
mkdir -p kernels/rad
$CP_CMD $G0/kernels/rad/*.h kernels/rad/
$CP_CMD $G0/kernels/rad/*.c kernels/rad/
mkdir -p kernels/translate_dim
$CP_CMD $G0/kernels/translate_dim/*.h kernels/translate_dim/
$CP_CMD $G0/kernels/translate_dim/*.c kernels/translate_dim/
mkdir -p kernels/twistshift
$CP_CMD $G0/kernels/twistshift/*.h kernels/twistshift/
$CP_CMD $G0/kernels/twistshift/*.c kernels/twistshift/

$RM_CMD $G0/kernels/ambi_bolt_potential/*.h
$RM_CMD $G0/kernels/ambi_bolt_potential/*.c
$RM_CMD $G0/kernels/bgk/*.h
$RM_CMD $G0/kernels/bgk/*.c
$RM_CMD $G0/kernels/deflate_geo/*.h
$RM_CMD $G0/kernels/deflate_geo/*.c
$RM_CMD $G0/kernels/deflate_surf/*.h
$RM_CMD $G0/kernels/deflate_surf/*.c
$RM_CMD $G0/kernels/derived_geo/*.h
$RM_CMD $G0/kernels/derived_geo/*.c
$RM_CMD $G0/kernels/dg_diffusion_gyrokinetic/*.h
$RM_CMD $G0/kernels/dg_diffusion_gyrokinetic/*.c
$RM_CMD $G0/kernels/fem_parproj/*.h
$RM_CMD $G0/kernels/fem_parproj/*.c
$RM_CMD $G0/kernels/fem_poisson_perp/*.h
$RM_CMD $G0/kernels/fem_poisson_perp/*.c
$RM_CMD $G0/kernels/gyrokinetic/*.h
$RM_CMD $G0/kernels/gyrokinetic/*.c
$RM_CMD $G0/kernels/gyrokinetic_pol_density/*.h
$RM_CMD $G0/kernels/gyrokinetic_pol_density/*.c
$RM_CMD $G0/kernels/inflate_surf/*.h
$RM_CMD $G0/kernels/inflate_surf/*.c
$RM_CMD $G0/kernels/neutral/*.h
$RM_CMD $G0/kernels/neutral/*.c
$RM_CMD $G0/kernels/positivity_shift/*.h
$RM_CMD $G0/kernels/positivity_shift/*.c
$RM_CMD $G0/kernels/rad/*.h
$RM_CMD $G0/kernels/rad/*.c
$RM_CMD $G0/kernels/translate_dim/*.h
$RM_CMD $G0/kernels/translate_dim/*.c
$RM_CMD $G0/kernels/twistshift/*.h
$RM_CMD $G0/kernels/twistshift/*.c

# zero
mkdir -p zero
$CP_CMD $G0/zero/ambi_bolt_potential_cu.cu zero/
$CP_CMD $G0/zero/ambi_bolt_potential.c zero/
$CP_CMD $G0/zero/bc_block_tensor.c zero/
$CP_CMD $G0/zero/bc_sheath_gyrokinetic_cu.cu zero/
$CP_CMD $G0/zero/bc_sheath_gyrokinetic.c zero/
$CP_CMD $G0/zero/bc_twistshift_cu.cu zero/
$CP_CMD $G0/zero/bc_twistshift.c zero/
$CP_CMD $G0/zero/boundary_flux_cu.cu zero/
$CP_CMD $G0/zero/boundary_flux.c zero/
$CP_CMD $G0/zero/calc_bmag.c zero/
$CP_CMD $G0/zero/calc_derived_geo.c zero/
$CP_CMD $G0/zero/calc_metric.c zero/
$CP_CMD $G0/zero/deflate_geo.c zero/
$CP_CMD $G0/zero/deflate_zsurf_cu.cu zero/
$CP_CMD $G0/zero/deflate_zsurf.c zero/
$CP_CMD $G0/zero/deflated_dg_bin_ops.c zero/
$CP_CMD $G0/zero/deflated_fem_poisson.c zero/
$CP_CMD $G0/zero/dg_calc_gk_rad_vars_cu.cu zero/
$CP_CMD $G0/zero/dg_calc_gk_rad_vars.c zero/
$CP_CMD $G0/zero/dg_calc_gyrokinetic_vars_cu.cu zero/
$CP_CMD $G0/zero/dg_calc_gyrokinetic_vars.c zero/
$CP_CMD $G0/zero/dg_calc_vlasov_gen_geo_vars_cu.cu zero/
$CP_CMD $G0/zero/dg_calc_vlasov_gen_geo_vars.c zero/
$CP_CMD $G0/zero/dg_cx_cu.cu zero/
$CP_CMD $G0/zero/dg_cx.c zero/
$CP_CMD $G0/zero/dg_diffusion_gyrokinetic_cu.cu zero/
$CP_CMD $G0/zero/dg_diffusion_gyrokinetic.c zero/
$CP_CMD $G0/zero/dg_gyrokinetic_cu.cu zero/
$CP_CMD $G0/zero/dg_gyrokinetic.c zero/
$CP_CMD $G0/zero/dg_iz_cu.cu zero/
$CP_CMD $G0/zero/dg_iz.c zero/
$CP_CMD $G0/zero/dg_lbo_gyrokinetic_diff_cu.cu zero/
$CP_CMD $G0/zero/dg_lbo_gyrokinetic_diff.c zero/
$CP_CMD $G0/zero/dg_lbo_gyrokinetic_drag_cu.cu zero/
$CP_CMD $G0/zero/dg_lbo_gyrokinetic_drag.c zero/
$CP_CMD $G0/zero/dg_rad_gyrokinetic_drag_cu.cu zero/
$CP_CMD $G0/zero/dg_rad_gyrokinetic_drag.c zero/
$CP_CMD $G0/zero/dg_recomb_cu.cu zero/
$CP_CMD $G0/zero/dg_recomb.c zero/
$CP_CMD $G0/zero/dg_updater_bflux_gyrokinetic.c zero/
$CP_CMD $G0/zero/dg_updater_diffusion_gyrokinetic.c zero/
$CP_CMD $G0/zero/dg_updater_gyrokinetic.c zero/
$CP_CMD $G0/zero/dg_updater_lbo_gyrokinetic.c zero/
$CP_CMD $G0/zero/dg_updater_moment_gyrokinetic.c zero/
$CP_CMD $G0/zero/dg_updater_rad_gyrokinetic.c zero/
$CP_CMD $G0/zero/efit_utils.c zero/
$CP_CMD $G0/zero/efit.c zero/
$CP_CMD $G0/zero/fem_parproj_cu.cu zero/
$CP_CMD $G0/zero/fem_parproj.c zero/
$CP_CMD $G0/zero/fem_poisson_perp_cu.cu zero/
$CP_CMD $G0/zero/fem_poisson_perp.c zero/
$CP_CMD $G0/zero/gk_geometry_cu.cu zero/
$CP_CMD $G0/zero/gk_geometry_mapc2p.c zero/
$CP_CMD $G0/zero/gk_geometry_mirror.c zero/
$CP_CMD $G0/zero/gk_geometry_tok.c zero/
$CP_CMD $G0/zero/gk_geometry.c zero/
$CP_CMD $G0/zero/gk_maxwellian_correct_cu.cu zero/
$CP_CMD $G0/zero/gk_maxwellian_correct.c zero/
$CP_CMD $G0/zero/gk_maxwellian_moments.c zero/
$CP_CMD $G0/zero/gk_maxwellian_proj_on_basis_cu.cu zero/
$CP_CMD $G0/zero/gk_maxwellian_proj_on_basis.c zero/
$CP_CMD $G0/zero/gkgeom.c zero/
$CP_CMD $G0/zero/gkyl_ambi_bolt_potential_priv.h zero/
$CP_CMD $G0/zero/gkyl_ambi_bolt_potential.h zero/
$CP_CMD $G0/zero/gkyl_bc_block_tensor_priv.h zero/
$CP_CMD $G0/zero/gkyl_bc_block_tensor.h zero/
$CP_CMD $G0/zero/gkyl_bc_sheath_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_bc_sheath_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_bc_twistshift_priv.h zero/
$CP_CMD $G0/zero/gkyl_bc_twistshift.h zero/
$CP_CMD $G0/zero/gkyl_boundary_flux_priv.h zero/
$CP_CMD $G0/zero/gkyl_boundary_flux.h zero/
$CP_CMD $G0/zero/gkyl_calc_bmag_priv.h zero/
$CP_CMD $G0/zero/gkyl_calc_bmag.h zero/
$CP_CMD $G0/zero/gkyl_calc_derived_geo_priv.h zero/
$CP_CMD $G0/zero/gkyl_calc_derived_geo.h zero/
$CP_CMD $G0/zero/gkyl_calc_metric_priv.h zero/
$CP_CMD $G0/zero/gkyl_calc_metric.h zero/
$CP_CMD $G0/zero/gkyl_deflate_geo_priv.h zero/
$CP_CMD $G0/zero/gkyl_deflate_geo.h zero/
$CP_CMD $G0/zero/gkyl_deflate_zsurf_priv.h zero/
$CP_CMD $G0/zero/gkyl_deflate_zsurf.h zero/
$CP_CMD $G0/zero/gkyl_deflated_dg_bin_ops_priv.h zero/
$CP_CMD $G0/zero/gkyl_deflated_dg_bin_ops.h zero/
$CP_CMD $G0/zero/gkyl_deflated_fem_poisson_priv.h zero/
$CP_CMD $G0/zero/gkyl_deflated_fem_poisson.h zero/
$CP_CMD $G0/zero/gkyl_dg_calc_gk_rad_vars_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_calc_gk_rad_vars.h zero/
$CP_CMD $G0/zero/gkyl_dg_calc_gyrokinetic_vars_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_calc_gyrokinetic_vars.h zero/
$CP_CMD $G0/zero/gkyl_dg_calc_vlasov_gen_geo_vars_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_calc_vlasov_gen_geo_vars.h zero/
$CP_CMD $G0/zero/gkyl_dg_cx_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_cx.h zero/
$CP_CMD $G0/zero/gkyl_dg_diffusion_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_diffusion_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_dg_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_dg_iz_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_iz.h zero/
$CP_CMD $G0/zero/gkyl_dg_lbo_gyrokinetic_diff_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_lbo_gyrokinetic_diff.h zero/
$CP_CMD $G0/zero/gkyl_dg_lbo_gyrokinetic_drag_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_lbo_gyrokinetic_drag.h zero/
$CP_CMD $G0/zero/gkyl_dg_rad_gyrokinetic_drag_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_rad_gyrokinetic_drag.h zero/
$CP_CMD $G0/zero/gkyl_dg_recomb_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_recomb.h zero/
$CP_CMD $G0/zero/gkyl_dg_updater_bflux_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_updater_bflux_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_dg_updater_diffusion_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_updater_diffusion_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_dg_updater_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_dg_updater_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_dg_updater_lbo_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_dg_updater_moment_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_dg_updater_rad_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_efit_priv.h zero/
$CP_CMD $G0/zero/gkyl_efit.h zero/
$CP_CMD $G0/zero/gkyl_fem_parproj_priv.h zero/
$CP_CMD $G0/zero/gkyl_fem_parproj.h zero/
$CP_CMD $G0/zero/gkyl_fem_poisson_perp_priv.h zero/
$CP_CMD $G0/zero/gkyl_fem_poisson_perp.h zero/
$CP_CMD $G0/zero/gkyl_gk_geometry_mapc2p.h zero/
$CP_CMD $G0/zero/gkyl_gk_geometry_mirror.h zero/
$CP_CMD $G0/zero/gkyl_gk_geometry_tok.h zero/
$CP_CMD $G0/zero/gkyl_gk_geometry.h zero/
$CP_CMD $G0/zero/gkyl_gk_maxwellian_correct_priv.h zero/
$CP_CMD $G0/zero/gkyl_gk_maxwellian_correct.h zero/
$CP_CMD $G0/zero/gkyl_gk_maxwellian_moments_priv.h zero/
$CP_CMD $G0/zero/gkyl_gk_maxwellian_moments.h zero/
$CP_CMD $G0/zero/gkyl_gk_maxwellian_proj_on_basis_priv.h zero/
$CP_CMD $G0/zero/gkyl_gk_maxwellian_proj_on_basis.h zero/
$CP_CMD $G0/zero/gkyl_gkgeom.h zero/
$CP_CMD $G0/zero/gkyl_gyrokinetic_cross_prim_moms_bgk_priv.h zero/
$CP_CMD $G0/zero/gkyl_gyrokinetic_cross_prim_moms_bgk.h zero/
$CP_CMD $G0/zero/gkyl_gyrokinetic_pol_density_priv.h zero/
$CP_CMD $G0/zero/gkyl_gyrokinetic_pol_density.h zero/
$CP_CMD $G0/zero/gkyl_mirror_geo_priv.h zero/
$CP_CMD $G0/zero/gkyl_mirror_geo.h zero/
$CP_CMD $G0/zero/gkyl_mom_bcorr_lbo_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_mom_bcorr_lbo_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_mom_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_mom_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_position_map_priv.h zero/
$CP_CMD $G0/zero/gkyl_position_map.h zero/
$CP_CMD $G0/zero/gkyl_positivity_shift_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_positivity_shift_gyrokinetic.h zero/
$CP_CMD $G0/zero/gkyl_proj_powsqrt_on_basis_priv.h zero/
$CP_CMD $G0/zero/gkyl_proj_powsqrt_on_basis.h zero/
$CP_CMD $G0/zero/gkyl_radiation_read.h zero/
$CP_CMD $G0/zero/gkyl_rescale_ghost_jacf_priv.h zero/
$CP_CMD $G0/zero/gkyl_rescale_ghost_jacf.h zero/
$CP_CMD $G0/zero/gkyl_tok_calc_derived_geo_priv.h zero/
$CP_CMD $G0/zero/gkyl_tok_calc_derived_geo.h zero/
$CP_CMD $G0/zero/gkyl_tok_geo_priv.h zero/
$CP_CMD $G0/zero/gkyl_tok_geo.h zero/
$CP_CMD $G0/zero/gkyl_translate_dim_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_translate_dim_gyrokinetic.h zero/
$CP_CMD $G0/zero/gyrokinetic_cross_prim_moms_bgk_cu.cu zero/
$CP_CMD $G0/zero/gyrokinetic_cross_prim_moms_bgk.c zero/
$CP_CMD $G0/zero/gyrokinetic_pol_density_cu.cu zero/
$CP_CMD $G0/zero/gyrokinetic_pol_density.c zero/
$CP_CMD $G0/zero/mirror_geo_utils.c zero/
$CP_CMD $G0/zero/mirror_geo.c zero/
$CP_CMD $G0/zero/mom_gyrokinetic_cu.cu zero/
$CP_CMD $G0/zero/mom_gyrokinetic.c zero/
$CP_CMD $G0/zero/position_map.c zero/
$CP_CMD $G0/zero/positivity_shift_gyrokinetic_cu.cu zero/
$CP_CMD $G0/zero/positivity_shift_gyrokinetic.c zero/
$CP_CMD $G0/zero/proj_powsqrt_on_basis_cu.cu zero/
$CP_CMD $G0/zero/proj_powsqrt_on_basis.c zero/
$CP_CMD $G0/zero/radiation_read.c zero/
$CP_CMD $G0/zero/rescale_ghost_jacf_cu.cu zero/
$CP_CMD $G0/zero/rescale_ghost_jacf.c zero/
$CP_CMD $G0/zero/tok_calc_derived_geo.c zero/
$CP_CMD $G0/zero/tok_geo_utils.c zero/
$CP_CMD $G0/zero/tok_geo.c zero/
$CP_CMD $G0/zero/translate_dim_gyrokinetic_cu.cu zero/
$CP_CMD $G0/zero/translate_dim_gyrokinetic.c zero/
$CP_CMD $G0/zero/gkyl_prim_lbo_gyrokinetic_priv.h zero/
$CP_CMD $G0/zero/gkyl_prim_lbo_gyrokinetic.h zero/
$CP_CMD $G0/zero/mom_bcorr_lbo_gyrokinetic_cu.cu zero/
$CP_CMD $G0/zero/mom_bcorr_lbo_gyrokinetic.c zero/
$CP_CMD $G0/zero/prim_lbo_gyrokinetic_cu.cu zero/
$CP_CMD $G0/zero/prim_lbo_gyrokinetic.c zero/
$CP_CMD $G0/zero/mom_calc_bcorr_gyrokinetic.c zero/
$CP_CMD $G0/zero/prim_lbo_calc_gyrokinetic.c zero/
$CP_CMD $G0/zero/prim_lbo_cross_calc_gyrokinetic.c zero/

$RM_CMD $G0/zero/ambi_bolt_potential_cu.cu
$RM_CMD $G0/zero/ambi_bolt_potential.c
$RM_CMD $G0/zero/bc_block_tensor.c
$RM_CMD $G0/zero/bc_sheath_gyrokinetic_cu.cu
$RM_CMD $G0/zero/bc_sheath_gyrokinetic.c
$RM_CMD $G0/zero/bc_twistshift_cu.cu
$RM_CMD $G0/zero/bc_twistshift.c
$RM_CMD $G0/zero/boundary_flux_cu.cu
$RM_CMD $G0/zero/boundary_flux.c
$RM_CMD $G0/zero/calc_bmag.c
$RM_CMD $G0/zero/calc_derived_geo.c
$RM_CMD $G0/zero/calc_metric.c
$RM_CMD $G0/zero/deflate_geo.c
$RM_CMD $G0/zero/deflate_zsurf_cu.cu
$RM_CMD $G0/zero/deflate_zsurf.c
$RM_CMD $G0/zero/deflated_dg_bin_ops.c
$RM_CMD $G0/zero/deflated_fem_poisson.c
$RM_CMD $G0/zero/dg_calc_gk_rad_vars_cu.cu
$RM_CMD $G0/zero/dg_calc_gk_rad_vars.c
$RM_CMD $G0/zero/dg_calc_gyrokinetic_vars_cu.cu
$RM_CMD $G0/zero/dg_calc_gyrokinetic_vars.c
$RM_CMD $G0/zero/dg_calc_vlasov_gen_geo_vars_cu.cu
$RM_CMD $G0/zero/dg_calc_vlasov_gen_geo_vars.c
$RM_CMD $G0/zero/dg_cx_cu.cu
$RM_CMD $G0/zero/dg_cx.c
$RM_CMD $G0/zero/dg_diffusion_gyrokinetic_cu.cu
$RM_CMD $G0/zero/dg_diffusion_gyrokinetic.c
$RM_CMD $G0/zero/dg_gyrokinetic_cu.cu
$RM_CMD $G0/zero/dg_gyrokinetic.c
$RM_CMD $G0/zero/dg_iz_cu.cu
$RM_CMD $G0/zero/dg_iz.c
$RM_CMD $G0/zero/dg_lbo_gyrokinetic_diff_cu.cu
$RM_CMD $G0/zero/dg_lbo_gyrokinetic_diff.c
$RM_CMD $G0/zero/dg_lbo_gyrokinetic_drag_cu.cu
$RM_CMD $G0/zero/dg_lbo_gyrokinetic_drag.c
$RM_CMD $G0/zero/dg_rad_gyrokinetic_drag_cu.cu
$RM_CMD $G0/zero/dg_rad_gyrokinetic_drag.c
$RM_CMD $G0/zero/dg_recomb_cu.cu
$RM_CMD $G0/zero/dg_recomb.c
$RM_CMD $G0/zero/dg_updater_bflux_gyrokinetic.c
$RM_CMD $G0/zero/dg_updater_diffusion_gyrokinetic.c
$RM_CMD $G0/zero/dg_updater_gyrokinetic.c
$RM_CMD $G0/zero/dg_updater_lbo_gyrokinetic.c
$RM_CMD $G0/zero/dg_updater_moment_gyrokinetic.c
$RM_CMD $G0/zero/dg_updater_rad_gyrokinetic.c
$RM_CMD $G0/zero/efit_utils.c
$RM_CMD $G0/zero/efit.c
$RM_CMD $G0/zero/fem_parproj_cu.cu
$RM_CMD $G0/zero/fem_parproj.c
$RM_CMD $G0/zero/fem_poisson_perp_cu.cu
$RM_CMD $G0/zero/fem_poisson_perp.c
$RM_CMD $G0/zero/gk_geometry_cu.cu
$RM_CMD $G0/zero/gk_geometry_mapc2p.c
$RM_CMD $G0/zero/gk_geometry_mirror.c
$RM_CMD $G0/zero/gk_geometry_tok.c
$RM_CMD $G0/zero/gk_geometry.c
$RM_CMD $G0/zero/gk_maxwellian_correct_cu.cu
$RM_CMD $G0/zero/gk_maxwellian_correct.c
$RM_CMD $G0/zero/gk_maxwellian_moments.c
$RM_CMD $G0/zero/gk_maxwellian_proj_on_basis_cu.cu
$RM_CMD $G0/zero/gk_maxwellian_proj_on_basis.c
$RM_CMD $G0/zero/gkgeom.c
$RM_CMD $G0/zero/gkyl_ambi_bolt_potential_priv.h
$RM_CMD $G0/zero/gkyl_ambi_bolt_potential.h
$RM_CMD $G0/zero/gkyl_bc_block_tensor_priv.h
$RM_CMD $G0/zero/gkyl_bc_block_tensor.h
$RM_CMD $G0/zero/gkyl_bc_sheath_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_bc_sheath_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_bc_twistshift_priv.h
$RM_CMD $G0/zero/gkyl_bc_twistshift.h
$RM_CMD $G0/zero/gkyl_boundary_flux_priv.h
$RM_CMD $G0/zero/gkyl_boundary_flux.h
$RM_CMD $G0/zero/gkyl_calc_bmag_priv.h
$RM_CMD $G0/zero/gkyl_calc_bmag.h
$RM_CMD $G0/zero/gkyl_calc_derived_geo_priv.h
$RM_CMD $G0/zero/gkyl_calc_derived_geo.h
$RM_CMD $G0/zero/gkyl_calc_metric_priv.h
$RM_CMD $G0/zero/gkyl_calc_metric.h
$RM_CMD $G0/zero/gkyl_deflate_geo_priv.h
$RM_CMD $G0/zero/gkyl_deflate_geo.h
$RM_CMD $G0/zero/gkyl_deflate_zsurf_priv.h
$RM_CMD $G0/zero/gkyl_deflate_zsurf.h
$RM_CMD $G0/zero/gkyl_deflated_dg_bin_ops_priv.h
$RM_CMD $G0/zero/gkyl_deflated_dg_bin_ops.h
$RM_CMD $G0/zero/gkyl_deflated_fem_poisson_priv.h
$RM_CMD $G0/zero/gkyl_deflated_fem_poisson.h
$RM_CMD $G0/zero/gkyl_dg_calc_gk_rad_vars_priv.h
$RM_CMD $G0/zero/gkyl_dg_calc_gk_rad_vars.h
$RM_CMD $G0/zero/gkyl_dg_calc_gyrokinetic_vars_priv.h
$RM_CMD $G0/zero/gkyl_dg_calc_gyrokinetic_vars.h
$RM_CMD $G0/zero/gkyl_dg_calc_vlasov_gen_geo_vars_priv.h
$RM_CMD $G0/zero/gkyl_dg_calc_vlasov_gen_geo_vars.h
$RM_CMD $G0/zero/gkyl_dg_cx_priv.h
$RM_CMD $G0/zero/gkyl_dg_cx.h
$RM_CMD $G0/zero/gkyl_dg_diffusion_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_dg_diffusion_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_dg_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_dg_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_dg_iz_priv.h
$RM_CMD $G0/zero/gkyl_dg_iz.h
$RM_CMD $G0/zero/gkyl_dg_lbo_gyrokinetic_diff_priv.h
$RM_CMD $G0/zero/gkyl_dg_lbo_gyrokinetic_diff.h
$RM_CMD $G0/zero/gkyl_dg_lbo_gyrokinetic_drag_priv.h
$RM_CMD $G0/zero/gkyl_dg_lbo_gyrokinetic_drag.h
$RM_CMD $G0/zero/gkyl_dg_rad_gyrokinetic_drag_priv.h
$RM_CMD $G0/zero/gkyl_dg_rad_gyrokinetic_drag.h
$RM_CMD $G0/zero/gkyl_dg_recomb_priv.h
$RM_CMD $G0/zero/gkyl_dg_recomb.h
$RM_CMD $G0/zero/gkyl_dg_updater_bflux_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_dg_updater_bflux_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_dg_updater_diffusion_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_dg_updater_diffusion_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_dg_updater_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_dg_updater_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_dg_updater_lbo_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_dg_updater_moment_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_dg_updater_rad_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_efit_priv.h
$RM_CMD $G0/zero/gkyl_efit.h
$RM_CMD $G0/zero/gkyl_fem_parproj_priv.h
$RM_CMD $G0/zero/gkyl_fem_parproj.h
$RM_CMD $G0/zero/gkyl_fem_poisson_perp_priv.h
$RM_CMD $G0/zero/gkyl_fem_poisson_perp.h
$RM_CMD $G0/zero/gkyl_gk_geometry_mapc2p.h
$RM_CMD $G0/zero/gkyl_gk_geometry_mirror.h
$RM_CMD $G0/zero/gkyl_gk_geometry_tok.h
$RM_CMD $G0/zero/gkyl_gk_geometry.h
$RM_CMD $G0/zero/gkyl_gk_maxwellian_correct_priv.h
$RM_CMD $G0/zero/gkyl_gk_maxwellian_correct.h
$RM_CMD $G0/zero/gkyl_gk_maxwellian_moments_priv.h
$RM_CMD $G0/zero/gkyl_gk_maxwellian_moments.h
$RM_CMD $G0/zero/gkyl_gk_maxwellian_proj_on_basis_priv.h
$RM_CMD $G0/zero/gkyl_gk_maxwellian_proj_on_basis.h
$RM_CMD $G0/zero/gkyl_gkgeom.h
$RM_CMD $G0/zero/gkyl_gyrokinetic_cross_prim_moms_bgk_priv.h
$RM_CMD $G0/zero/gkyl_gyrokinetic_cross_prim_moms_bgk.h
$RM_CMD $G0/zero/gkyl_gyrokinetic_pol_density_priv.h
$RM_CMD $G0/zero/gkyl_gyrokinetic_pol_density.h
$RM_CMD $G0/zero/gkyl_mirror_geo_priv.h
$RM_CMD $G0/zero/gkyl_mirror_geo.h
$RM_CMD $G0/zero/gkyl_mom_bcorr_lbo_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_mom_bcorr_lbo_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_mom_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_mom_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_position_map_priv.h
$RM_CMD $G0/zero/gkyl_position_map.h
$RM_CMD $G0/zero/gkyl_positivity_shift_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_positivity_shift_gyrokinetic.h
$RM_CMD $G0/zero/gkyl_proj_powsqrt_on_basis_priv.h
$RM_CMD $G0/zero/gkyl_proj_powsqrt_on_basis.h
$RM_CMD $G0/zero/gkyl_radiation_read.h
$RM_CMD $G0/zero/gkyl_rescale_ghost_jacf_priv.h
$RM_CMD $G0/zero/gkyl_rescale_ghost_jacf.h
$RM_CMD $G0/zero/gkyl_tok_calc_derived_geo_priv.h
$RM_CMD $G0/zero/gkyl_tok_calc_derived_geo.h
$RM_CMD $G0/zero/gkyl_tok_geo_priv.h
$RM_CMD $G0/zero/gkyl_tok_geo.h
$RM_CMD $G0/zero/gkyl_translate_dim_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_translate_dim_gyrokinetic.h
$RM_CMD $G0/zero/gyrokinetic_cross_prim_moms_bgk_cu.cu
$RM_CMD $G0/zero/gyrokinetic_cross_prim_moms_bgk.c
$RM_CMD $G0/zero/gyrokinetic_pol_density_cu.cu
$RM_CMD $G0/zero/gyrokinetic_pol_density.c
$RM_CMD $G0/zero/mirror_geo_utils.c
$RM_CMD $G0/zero/mirror_geo.c
$RM_CMD $G0/zero/mom_gyrokinetic_cu.cu
$RM_CMD $G0/zero/mom_gyrokinetic.c
$RM_CMD $G0/zero/position_map.c
$RM_CMD $G0/zero/positivity_shift_gyrokinetic_cu.cu
$RM_CMD $G0/zero/positivity_shift_gyrokinetic.c
$RM_CMD $G0/zero/proj_powsqrt_on_basis_cu.cu
$RM_CMD $G0/zero/proj_powsqrt_on_basis.c
$RM_CMD $G0/zero/radiation_read.c
$RM_CMD $G0/zero/rescale_ghost_jacf_cu.cu
$RM_CMD $G0/zero/rescale_ghost_jacf.c
$RM_CMD $G0/zero/tok_calc_derived_geo.c
$RM_CMD $G0/zero/tok_geo_utils.c
$RM_CMD $G0/zero/tok_geo.c
$RM_CMD $G0/zero/translate_dim_gyrokinetic_cu.cu
$RM_CMD $G0/zero/translate_dim_gyrokinetic.c
$RM_CMD $G0/zero/gkyl_prim_lbo_gyrokinetic_priv.h
$RM_CMD $G0/zero/gkyl_prim_lbo_gyrokinetic.h
$RM_CMD $G0/zero/mom_bcorr_lbo_gyrokinetic_cu.cu
$RM_CMD $G0/zero/mom_bcorr_lbo_gyrokinetic.c
$RM_CMD $G0/zero/prim_lbo_gyrokinetic_cu.cu
$RM_CMD $G0/zero/prim_lbo_gyrokinetic.c
$RM_CMD $G0/zero/mom_calc_bcorr_gyrokinetic.c
$RM_CMD $G0/zero/prim_lbo_calc_gyrokinetic.c
$RM_CMD $G0/zero/prim_lbo_cross_calc_gyrokinetic.c

# app
mkdir -p apps
$CP_CMD $G0/apps/block_gk_geom.c apps/
$CP_CMD $G0/apps/gk_field.c apps/
$CP_CMD $G0/apps/gk_multib_field.c apps/
$CP_CMD $G0/apps/gk_neut_species_bgk.c apps/
$CP_CMD $G0/apps/gk_neut_species_lte.c apps/
$CP_CMD $G0/apps/gk_neut_species_moment.c apps/
$CP_CMD $G0/apps/gk_neut_species_projection.c apps/
$CP_CMD $G0/apps/gk_neut_species_react.c apps/
$CP_CMD $G0/apps/gk_neut_species_source.c apps/
$CP_CMD $G0/apps/gk_neut_species.c apps/
$CP_CMD $G0/apps/gk_species_bflux.c apps/
$CP_CMD $G0/apps/gk_species_bgk.c apps/
$CP_CMD $G0/apps/gk_species_lbo.c apps/
$CP_CMD $G0/apps/gk_species_lte.c apps/
$CP_CMD $G0/apps/gk_species_moment.c apps/
$CP_CMD $G0/apps/gk_species_projection.c apps/
$CP_CMD $G0/apps/gk_species_radiation.c apps/
$CP_CMD $G0/apps/gk_species_react.c apps/
$CP_CMD $G0/apps/gk_species_source.c apps/
$CP_CMD $G0/apps/gk_species.c apps/
$CP_CMD $G0/apps/gkyl_gk_block_geom.h apps/
$CP_CMD $G0/apps/gkyl_gyrokinetic_comms.h apps/
$CP_CMD $G0/apps/gkyl_gyrokinetic_lw.h apps/
$CP_CMD $G0/apps/gkyl_gyrokinetic_multib_priv.h apps/
$CP_CMD $G0/apps/gkyl_gyrokinetic_multib.h apps/
$CP_CMD $G0/apps/gkyl_gyrokinetic_priv.h apps/
$CP_CMD $G0/apps/gkyl_gyrokinetic.h apps/
$CP_CMD $G0/apps/gkyl_multib_conn.h apps/
$CP_CMD $G0/apps/gyrokinetic_comms.c apps/
$CP_CMD $G0/apps/gyrokinetic_lw.c apps/
$CP_CMD $G0/apps/gyrokinetic_multib_update_ssp_rk3.c apps/
$CP_CMD $G0/apps/gyrokinetic_multib.c apps/
$CP_CMD $G0/apps/gyrokinetic_update_implicit_coll.c apps/
$CP_CMD $G0/apps/gyrokinetic_update_op_split.c apps/
$CP_CMD $G0/apps/gyrokinetic_update_ssp_rk3.c apps/
$CP_CMD $G0/apps/gyrokinetic.c apps/
$CP_CMD $G0/apps/multib_conn.c apps/

$RM_CMD $G0/apps/block_gk_geom.c
$RM_CMD $G0/apps/gk_field.c
$RM_CMD $G0/apps/gk_multib_field.c
$RM_CMD $G0/apps/gk_neut_species_bgk.c
$RM_CMD $G0/apps/gk_neut_species_lte.c
$RM_CMD $G0/apps/gk_neut_species_moment.c
$RM_CMD $G0/apps/gk_neut_species_projection.c
$RM_CMD $G0/apps/gk_neut_species_react.c
$RM_CMD $G0/apps/gk_neut_species_source.c
$RM_CMD $G0/apps/gk_neut_species.c
$RM_CMD $G0/apps/gk_species_bflux.c
$RM_CMD $G0/apps/gk_species_bgk.c
$RM_CMD $G0/apps/gk_species_lbo.c
$RM_CMD $G0/apps/gk_species_lte.c
$RM_CMD $G0/apps/gk_species_moment.c
$RM_CMD $G0/apps/gk_species_projection.c
$RM_CMD $G0/apps/gk_species_radiation.c
$RM_CMD $G0/apps/gk_species_react.c
$RM_CMD $G0/apps/gk_species_source.c
$RM_CMD $G0/apps/gk_species.c
$RM_CMD $G0/apps/gkyl_gk_block_geom.h
$RM_CMD $G0/apps/gkyl_gyrokinetic_comms.h
$RM_CMD $G0/apps/gkyl_gyrokinetic_lw.h
$RM_CMD $G0/apps/gkyl_gyrokinetic_multib_priv.h
$RM_CMD $G0/apps/gkyl_gyrokinetic_multib.h
$RM_CMD $G0/apps/gkyl_gyrokinetic_priv.h
$RM_CMD $G0/apps/gkyl_gyrokinetic.h
$RM_CMD $G0/apps/gkyl_multib_conn.h
$RM_CMD $G0/apps/gyrokinetic_comms.c
$RM_CMD $G0/apps/gyrokinetic_lw.c
$RM_CMD $G0/apps/gyrokinetic_multib_update_ssp_rk3.c
$RM_CMD $G0/apps/gyrokinetic_multib.c
$RM_CMD $G0/apps/gyrokinetic_update_implicit_coll.c
$RM_CMD $G0/apps/gyrokinetic_update_op_split.c
$RM_CMD $G0/apps/gyrokinetic_update_ssp_rk3.c
$RM_CMD $G0/apps/gyrokinetic.c
$RM_CMD $G0/apps/multib_conn.c

# unit
mkdir -p unit

# C regression tests
mkdir -p creg
$CP_CMD $G0/regression/rt_gk_ar_react_nonuniformv_1x2v_p1.c creg/
$CP_CMD $G0/regression/rt_arg_parse.h creg/