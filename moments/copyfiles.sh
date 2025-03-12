#!/bin/sh

CP_CMD=cp
G0=/home/gandalf/research/gkyl-project/g0-branches/dir-reorg-fixes/gkylzero

# data
mkdir -p data/unit
$CP_CMD $G0/data/unit/euler_riem_2d_hllc-euler_1.gkyl data/unit/
$CP_CMD $G0/data/unit/ser-euler_riem_2d_hllc-euler_1.gkyl data/unit/

# kernels
mkdir -p kernels/basis
$CP_CMD $G0/kernels/basis/*.h kernels/basis/
$CP_CMD $G0/kernels/basis/*.c kernels/basis/

# minus
mkdir -p minus
$CP_CMD -r $G0/minus .

# zero
mkdir -p zero
$CP_CMD $G0/zero/alloc.c zero/
$CP_CMD $G0/zero/array.c zero/
$CP_CMD $G0/zero/array_ops.c zero/
$CP_CMD $G0/zero/array_rio.c zero/
$CP_CMD $G0/zero/array_rio_format_desc.c zero/
$CP_CMD $G0/zero/basis.c zero/
$CP_CMD $G0/zero/cart_modal_gkhybrid.c zero/
$CP_CMD $G0/zero/cart_modal_hybrid.c zero/
$CP_CMD $G0/zero/cart_modal_serendip.c zero/
$CP_CMD $G0/zero/cart_modal_tensor.c zero/
$CP_CMD $G0/zero/comm.c zero/
$CP_CMD $G0/zero/dynvec.c zero/
$CP_CMD $G0/zero/eval_offset_fd.c zero/
$CP_CMD $G0/zero/fv_proj.c zero/
$CP_CMD $G0/zero/gauss_quad_data.c zero/
$CP_CMD $G0/zero/gkyl_alloc.h zero/
$CP_CMD $G0/zero/gkyl_alloc_flags_priv.h zero/
$CP_CMD $G0/zero/gkyl_array.h zero/
$CP_CMD $G0/zero/gkyl_array_ops.h zero/
$CP_CMD $G0/zero/gkyl_array_ops_priv.h zero/
$CP_CMD $G0/zero/gkyl_array_rio.h zero/
$CP_CMD $G0/zero/gkyl_array_rio_format_desc.h zero/
$CP_CMD $G0/zero/gkyl_array_rio_priv.h zero/
$CP_CMD $G0/zero/gkyl_basis.h zero/
$CP_CMD $G0/zero/gkyl_cart_modal_gkhybrid_priv.h zero/
$CP_CMD $G0/zero/gkyl_cart_modal_hybrid_priv.h zero/
$CP_CMD $G0/zero/gkyl_cart_modal_serendip_priv.h zero/
$CP_CMD $G0/zero/gkyl_cart_modal_tensor_priv.h zero/
$CP_CMD $G0/zero/gkyl_comm.h zero/
$CP_CMD $G0/zero/gkyl_comm_io.h zero/
$CP_CMD $G0/zero/gkyl_comm_priv.h zero/
$CP_CMD $G0/zero/gkyl_const.h zero/
$CP_CMD $G0/zero/gkyl_dynvec.h zero/
$CP_CMD $G0/zero/gkyl_elem_type.h zero/
$CP_CMD $G0/zero/gkyl_elem_type_priv.h zero/
$CP_CMD $G0/zero/gkyl_eqn_type.h zero/
$CP_CMD $G0/zero/gkyl_eval_offset_fd.h zero/
$CP_CMD $G0/zero/gkyl_evalf_def.h zero/
$CP_CMD $G0/zero/gkyl_fv_proj.h zero/
$CP_CMD $G0/zero/gkyl_gauss_quad_data.h zero/
$CP_CMD $G0/zero/gkyl_mpi_comm.h zero/
$CP_CMD $G0/zero/gkyl_mpi_comm_priv.h zero/
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
$CP_CMD $G0/zero/mpi_comm.c zero/
$CP_CMD $G0/zero/null_comm.c zero/
$CP_CMD $G0/zero/proj_on_basis.c zero/
$CP_CMD $G0/zero/range.c zero/
$CP_CMD $G0/zero/rect_decomp.c zero/
$CP_CMD $G0/zero/rect_grid.c zero/
$CP_CMD $G0/zero/rrobin_decomp.c zero/
$CP_CMD $G0/zero/util.c zero/

# unit
mkdir -p unit
$CP_CMD $G0/unit/ctest_array.c unit/
$CP_CMD $G0/unit/ctest_basis.c unit/
$CP_CMD $G0/unit/ctest_dynvec.c unit/
$CP_CMD $G0/unit/ctest_eval_offset_fd.c unit/
$CP_CMD $G0/unit/ctest_fv_proj.c unit/
$CP_CMD $G0/unit/ctest_null_comm.c unit/
$CP_CMD $G0/unit/ctest_proj_on_basis.c unit/
$CP_CMD $G0/unit/ctest_range.c unit/
$CP_CMD $G0/unit/ctest_rect_grid.c unit/
$CP_CMD $G0/unit/mctest_mpi_comm.c unit/
$CP_CMD $G0/unit/mctest_mpi_comm_read.c unit/
