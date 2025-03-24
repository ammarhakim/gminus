#!/bin/sh

CP_CMD=cp
RM_CMD=rm
G0=../../gkylzero

# data
mkdir -p data/unit
$CP_CMD $G0/data/unit/euler_riem_2d_hllc-euler_1.gkyl data/unit/
$CP_CMD $G0/data/unit/ser-euler_riem_2d_hllc-euler_1.gkyl data/unit/

$RM_CMD $G0/data/unit/euler_riem_2d_hllc-euler_1.gkyl
$RM_CMD $G0/data/unit/ser-euler_riem_2d_hllc-euler_1.gkyl

# kernels
mkdir -p kernels/basis
$CP_CMD $G0/kernels/basis/*.h kernels/basis/
$CP_CMD $G0/kernels/basis/*.c kernels/basis/

$RM_CMD $G0/kernels/basis/*.h
$RM_CMD $G0/kernels/basis/*.c

# minus
mkdir -p minus
$CP_CMD -r $G0/minus .

$RM_CMD -r $G0/minus

# zero
mkdir -p zero
$CP_CMD $G0/zero/alloc.c zero/
$CP_CMD $G0/zero/array.c zero/
$CP_CMD $G0/zero/array_ops.c zero/
$CP_CMD $G0/zero/array_reduce.c zero/
$CP_CMD $G0/zero/array_reduce_cu.cu zero/
$CP_CMD $G0/zero/array_rio.c zero/
$CP_CMD $G0/zero/array_rio_format_desc.c zero/
$CP_CMD $G0/zero/basis.c zero/
$CP_CMD $G0/zero/block_geom.c zero/
$CP_CMD $G0/zero/block_topo.c zero/
$CP_CMD $G0/zero/cart_modal_gkhybrid.c zero/
$CP_CMD $G0/zero/cart_modal_hybrid.c zero/
$CP_CMD $G0/zero/cart_modal_serendip.c zero/
$CP_CMD $G0/zero/cart_modal_tensor.c zero/
$CP_CMD $G0/zero/comm.c zero/
$CP_CMD $G0/zero/dynvec.c zero/
$CP_CMD $G0/zero/eval_offset_fd.c zero/
$CP_CMD $G0/zero/eval_on_nodes.c zero/
$CP_CMD $G0/zero/fv_proj.c zero/
$CP_CMD $G0/zero/gauss_quad_data.c zero/
$CP_CMD $G0/zero/gkyl_alloc.h zero/
$CP_CMD $G0/zero/gkyl_alloc_flags_priv.h zero/
$CP_CMD $G0/zero/gkyl_array.h zero/
$CP_CMD $G0/zero/gkyl_array_ops.h zero/
$CP_CMD $G0/zero/gkyl_array_ops_priv.h zero/
$CP_CMD $G0/zero/gkyl_array_reduce.h zero/
$CP_CMD $G0/zero/gkyl_array_reduce_priv.h zero/
$CP_CMD $G0/zero/gkyl_array_rio.h zero/
$CP_CMD $G0/zero/gkyl_array_rio_format_desc.h zero/
$CP_CMD $G0/zero/gkyl_array_rio_priv.h zero/
$CP_CMD $G0/zero/gkyl_basis.h zero/
$CP_CMD $G0/zero/gkyl_block_geom.h zero/
$CP_CMD $G0/zero/gkyl_block_topo.h zero/
$CP_CMD $G0/zero/gkyl_cart_modal_gkhybrid_priv.h zero/
$CP_CMD $G0/zero/gkyl_cart_modal_hybrid_priv.h zero/
$CP_CMD $G0/zero/gkyl_cart_modal_serendip_priv.h zero/
$CP_CMD $G0/zero/gkyl_cart_modal_tensor_priv.h zero/
$CP_CMD $G0/zero/gkyl_comm.h zero/
$CP_CMD $G0/zero/gkyl_comm_io.h zero/
$CP_CMD $G0/zero/gkyl_comm_priv.h zero/
$CP_CMD $G0/zero/gkyl_const.h zero/
$CP_CMD $G0/zero/gkyl_dflt.h zero/
$CP_CMD $G0/zero/gkyl_dynvec.h zero/
$CP_CMD $G0/zero/gkyl_elem_type.h zero/
$CP_CMD $G0/zero/gkyl_elem_type_priv.h zero/
$CP_CMD $G0/zero/gkyl_eqn_type.h zero/
$CP_CMD $G0/zero/gkyl_eval_offset_fd.h zero/
$CP_CMD $G0/zero/gkyl_eval_on_nodes.h zero/
$CP_CMD $G0/zero/gkyl_evalf_def.h zero/
$CP_CMD $G0/zero/gkyl_fv_proj.h zero/
$CP_CMD $G0/zero/gkyl_gauss_quad_data.h zero/
$CP_CMD $G0/zero/gkyl_lua_utils.h zero/
$CP_CMD $G0/zero/gkyl_mat.h zero/
$CP_CMD $G0/zero/gkyl_mat_priv.h zero/
$CP_CMD $G0/zero/gkyl_mat_triples.h zero/
$CP_CMD $G0/zero/gkyl_math.h zero/
$CP_CMD $G0/zero/gkyl_mpi_comm.h zero/
$CP_CMD $G0/zero/gkyl_mpi_comm_priv.h zero/
$CP_CMD $G0/zero/gkyl_multib_comm_conn.h zero/
$CP_CMD $G0/zero/gkyl_multib_comm_conn_priv.h zero/
$CP_CMD $G0/zero/gkyl_null_comm.h zero/
$CP_CMD $G0/zero/gkyl_null_comm_priv.h zero/
$CP_CMD $G0/zero/gkyl_proj_on_basis.h zero/
$CP_CMD $G0/zero/gkyl_range.h zero/
$CP_CMD $G0/zero/gkyl_rect_decomp.h zero/
$CP_CMD $G0/zero/gkyl_rect_grid.h zero/
$CP_CMD $G0/zero/gkyl_rect_grid_priv.h zero/
$CP_CMD $G0/zero/gkyl_ref_count.h zero/
$CP_CMD $G0/zero/gkyl_rrobin_decomp.h zero/
$CP_CMD $G0/zero/gkyl_util.h zero/
$CP_CMD $G0/zero/gkyl_vargm.h zero/
$CP_CMD $G0/zero/lua_utils.c zero/
$CP_CMD $G0/zero/mat.c zero/
$CP_CMD $G0/zero/mat_triples.c zero/
$CP_CMD $G0/zero/math.c zero/
$CP_CMD $G0/zero/mpi_comm.c zero/
$CP_CMD $G0/zero/multib_comm_conn.c zero/
$CP_CMD $G0/zero/multib_comm_conn_mpi.c zero/
$CP_CMD $G0/zero/multib_comm_conn_nccl.c zero/
$CP_CMD $G0/zero/multib_comm_conn_null.c zero/
$CP_CMD $G0/zero/null_comm.c zero/
$CP_CMD $G0/zero/proj_on_basis.c zero/
$CP_CMD $G0/zero/range.c zero/
$CP_CMD $G0/zero/rect_decomp.c zero/
$CP_CMD $G0/zero/rect_grid.c zero/
$CP_CMD $G0/zero/rrobin_decomp.c zero/
$CP_CMD $G0/zero/util.c zero/

$RM_CMD $G0/zero/alloc.c
$RM_CMD $G0/zero/array.c
$RM_CMD $G0/zero/array_ops.c
$RM_CMD $G0/zero/array_reduce.c
$RM_CMD $G0/zero/array_reduce_cu.cu
$RM_CMD $G0/zero/array_rio.c
$RM_CMD $G0/zero/array_rio_format_desc.c
$RM_CMD $G0/zero/basis.c
$RM_CMD $G0/zero/block_geom.c
$RM_CMD $G0/zero/block_topo.c
$RM_CMD $G0/zero/cart_modal_gkhybrid.c
$RM_CMD $G0/zero/cart_modal_hybrid.c
$RM_CMD $G0/zero/cart_modal_serendip.c
$RM_CMD $G0/zero/cart_modal_tensor.c
$RM_CMD $G0/zero/comm.c
$RM_CMD $G0/zero/dynvec.c
$RM_CMD $G0/zero/eval_offset_fd.c
$RM_CMD $G0/zero/eval_on_nodes.c
$RM_CMD $G0/zero/fv_proj.c
$RM_CMD $G0/zero/gauss_quad_data.c
$RM_CMD $G0/zero/gkyl_alloc.h
$RM_CMD $G0/zero/gkyl_alloc_flags_priv.h
$RM_CMD $G0/zero/gkyl_array.h
$RM_CMD $G0/zero/gkyl_array_ops.h
$RM_CMD $G0/zero/gkyl_array_ops_priv.h
$RM_CMD $G0/zero/gkyl_array_reduce.h
$RM_CMD $G0/zero/gkyl_array_reduce_priv.h
$RM_CMD $G0/zero/gkyl_array_rio.h
$RM_CMD $G0/zero/gkyl_array_rio_format_desc.h
$RM_CMD $G0/zero/gkyl_array_rio_priv.h
$RM_CMD $G0/zero/gkyl_basis.h
$RM_CMD $G0/zero/gkyl_block_geom.h
$RM_CMD $G0/zero/gkyl_block_topo.h
$RM_CMD $G0/zero/gkyl_cart_modal_gkhybrid_priv.h
$RM_CMD $G0/zero/gkyl_cart_modal_hybrid_priv.h
$RM_CMD $G0/zero/gkyl_cart_modal_serendip_priv.h
$RM_CMD $G0/zero/gkyl_cart_modal_tensor_priv.h
$RM_CMD $G0/zero/gkyl_comm.h
$RM_CMD $G0/zero/gkyl_comm_io.h
$RM_CMD $G0/zero/gkyl_comm_priv.h
$RM_CMD $G0/zero/gkyl_const.h
$RM_CMD $G0/zero/gkyl_dflt.h
$RM_CMD $G0/zero/gkyl_dynvec.h
$RM_CMD $G0/zero/gkyl_elem_type.h
$RM_CMD $G0/zero/gkyl_elem_type_priv.h
$RM_CMD $G0/zero/gkyl_eqn_type.h
$RM_CMD $G0/zero/gkyl_eval_offset_fd.h
$RM_CMD $G0/zero/gkyl_eval_on_nodes.h
$RM_CMD $G0/zero/gkyl_evalf_def.h
$RM_CMD $G0/zero/gkyl_fv_proj.h
$RM_CMD $G0/zero/gkyl_gauss_quad_data.h
$RM_CMD $G0/zero/gkyl_lua_utils.h
$RM_CMD $G0/zero/gkyl_mat.h
$RM_CMD $G0/zero/gkyl_mat_priv.h
$RM_CMD $G0/zero/gkyl_mat_triples.h
$RM_CMD $G0/zero/gkyl_math.h
$RM_CMD $G0/zero/gkyl_mpi_comm.h
$RM_CMD $G0/zero/gkyl_mpi_comm_priv.h
$RM_CMD $G0/zero/gkyl_multib_comm_conn.h
$RM_CMD $G0/zero/gkyl_multib_comm_conn_priv.h
$RM_CMD $G0/zero/gkyl_null_comm.h
$RM_CMD $G0/zero/gkyl_null_comm_priv.h
$RM_CMD $G0/zero/gkyl_proj_on_basis.h
$RM_CMD $G0/zero/gkyl_range.h
$RM_CMD $G0/zero/gkyl_rect_decomp.h
$RM_CMD $G0/zero/gkyl_rect_grid.h
$RM_CMD $G0/zero/gkyl_rect_grid_priv.h
$RM_CMD $G0/zero/gkyl_ref_count.h
$RM_CMD $G0/zero/gkyl_rrobin_decomp.h
$RM_CMD $G0/zero/gkyl_util.h
$RM_CMD $G0/zero/gkyl_vargm.h
$RM_CMD $G0/zero/lua_utils.c
$RM_CMD $G0/zero/mat.c
$RM_CMD $G0/zero/mat_triples.c
$RM_CMD $G0/zero/math.c
$RM_CMD $G0/zero/mpi_comm.c
$RM_CMD $G0/zero/multib_comm_conn.c
$RM_CMD $G0/zero/multib_comm_conn_mpi.c
$RM_CMD $G0/zero/multib_comm_conn_nccl.c
$RM_CMD $G0/zero/multib_comm_conn_null.c
$RM_CMD $G0/zero/null_comm.c
$RM_CMD $G0/zero/proj_on_basis.c
$RM_CMD $G0/zero/range.c
$RM_CMD $G0/zero/rect_decomp.c
$RM_CMD $G0/zero/rect_grid.c
$RM_CMD $G0/zero/rrobin_decomp.c
$RM_CMD $G0/zero/util.c

# app
mkdir -p apps
$CP_CMD $G0/apps/app_priv.c apps/
$CP_CMD $G0/apps/gkyl_app.h apps/
$CP_CMD $G0/apps/gkyl_app_priv.h apps/
$CP_CMD $G0/apps/gkyl_lw_priv.h apps/
$CP_CMD $G0/apps/gkyl_zero_lw.h apps/
$CP_CMD $G0/apps/lw_priv.c apps/
$CP_CMD $G0/apps/zero_lw.c apps/

$RM_CMD $G0/apps/app_priv.c
$RM_CMD $G0/apps/gkyl_app.h
$RM_CMD $G0/apps/gkyl_app_priv.h
$RM_CMD $G0/apps/gkyl_lw_priv.h
$RM_CMD $G0/apps/gkyl_zero_lw.h
$RM_CMD $G0/apps/lw_priv.c
$RM_CMD $G0/apps/zero_lw.c

# unit
mkdir -p unit
$CP_CMD $G0/unit/ctest_array.c unit/
$CP_CMD $G0/unit/ctest_array_reduce.c unit/
$CP_CMD $G0/unit/ctest_basis.c unit/
$CP_CMD $G0/unit/ctest_block_geom.c unit/
$CP_CMD $G0/unit/ctest_block_topo.c unit/
$CP_CMD $G0/unit/ctest_dynvec.c unit/
$CP_CMD $G0/unit/ctest_eval_offset_fd.c unit/
$CP_CMD $G0/unit/ctest_eval_on_nodes.c unit/
$CP_CMD $G0/unit/ctest_fv_proj.c unit/
$CP_CMD $G0/unit/ctest_mat.c unit/
$CP_CMD $G0/unit/ctest_mat_triples.c unit/
$CP_CMD $G0/unit/ctest_multib_comm_conn.c unit/
$CP_CMD $G0/unit/ctest_null_comm.c unit/
$CP_CMD $G0/unit/ctest_proj_on_basis.c unit/
$CP_CMD $G0/unit/ctest_range.c unit/
$CP_CMD $G0/unit/ctest_rect_grid.c unit/
$CP_CMD $G0/unit/lctest_lua_utils.c unit/
$CP_CMD $G0/unit/mctest_mpi_comm.c unit/
$CP_CMD $G0/unit/mctest_mpi_comm_read.c unit/
$CP_CMD $G0/unit/mctest_multib_sync.c unit/

$RM_CMD $G0/unit/ctest_array.c
$RM_CMD $G0/unit/ctest_array_reduce.c
$RM_CMD $G0/unit/ctest_basis.c
$RM_CMD $G0/unit/ctest_block_geom.c
$RM_CMD $G0/unit/ctest_block_topo.c
$RM_CMD $G0/unit/ctest_dynvec.c
$RM_CMD $G0/unit/ctest_eval_offset_fd.c
$RM_CMD $G0/unit/ctest_eval_on_nodes.c
$RM_CMD $G0/unit/ctest_fv_proj.c
$RM_CMD $G0/unit/ctest_mat.c
$RM_CMD $G0/unit/ctest_mat_triples.c
$RM_CMD $G0/unit/ctest_multib_comm_conn.c
$RM_CMD $G0/unit/ctest_null_comm.c
$RM_CMD $G0/unit/ctest_proj_on_basis.c
$RM_CMD $G0/unit/ctest_range.c
$RM_CMD $G0/unit/ctest_rect_grid.c
$RM_CMD $G0/unit/lctest_lua_utils.c
$RM_CMD $G0/unit/mctest_mpi_comm.c
$RM_CMD $G0/unit/mctest_mpi_comm_read.c
$RM_CMD $G0/unit/mctest_multib_sync.c