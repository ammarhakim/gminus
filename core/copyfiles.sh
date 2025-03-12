#!/bin/sh

CP_CMD=cp
G0=/home/gandalf/research/gkyl-project/g0-branches/dir-reorg-fixes/gkylzero

# data
mkdir -p data/unit
cp $G0/data/unit/euler_riem_2d_hllc-euler_1.gkyl data/unit/
cp $G0/data/unit/ser-euler_riem_2d_hllc-euler_1.gkyl data/unit/

# kernels
mkdir -p kernels/basis
cp $G0/kernels/basis/*.h kernels/basis/
cp $G0/kernels/basis/*.c kernels/basis/

# minus
mkdir -p minus
cp -r $G0/minus .

# zero
mkdir -p zero
cp $G0/zero/alloc.c zero/
cp $G0/zero/array.c zero/
cp $G0/zero/array_ops.c zero/
cp $G0/zero/array_rio.c zero/
cp $G0/zero/array_rio_format_desc.c zero/
cp $G0/zero/basis.c zero/
cp $G0/zero/cart_modal_gkhybrid.c zero/
cp $G0/zero/cart_modal_hybrid.c zero/
cp $G0/zero/cart_modal_serendip.c zero/
cp $G0/zero/cart_modal_tensor.c zero/
cp $G0/zero/comm.c zero/
cp $G0/zero/dynvec.c zero/
cp $G0/zero/eval_offset_fd.c zero/
cp $G0/zero/fv_proj.c zero/
cp $G0/zero/gauss_quad_data.c zero/
cp $G0/zero/gkyl_alloc.h zero/
cp $G0/zero/gkyl_alloc_flags_priv.h zero/
cp $G0/zero/gkyl_array.h zero/
cp $G0/zero/gkyl_array_ops.h zero/
cp $G0/zero/gkyl_array_ops_priv.h zero/
cp $G0/zero/gkyl_array_rio.h zero/
cp $G0/zero/gkyl_array_rio_format_desc.h zero/
cp $G0/zero/gkyl_array_rio_priv.h zero/
cp $G0/zero/gkyl_basis.h zero/
cp $G0/zero/gkyl_cart_modal_gkhybrid_priv.h zero/
cp $G0/zero/gkyl_cart_modal_hybrid_priv.h zero/
cp $G0/zero/gkyl_cart_modal_serendip_priv.h zero/
cp $G0/zero/gkyl_cart_modal_tensor_priv.h zero/
cp $G0/zero/gkyl_comm.h zero/
cp $G0/zero/gkyl_comm_io.h zero/
cp $G0/zero/gkyl_comm_priv.h zero/
cp $G0/zero/gkyl_const.h zero/
cp $G0/zero/gkyl_dynvec.h zero/
cp $G0/zero/gkyl_elem_type.h zero/
cp $G0/zero/gkyl_elem_type_priv.h zero/
cp $G0/zero/gkyl_eqn_type.h zero/
cp $G0/zero/gkyl_eval_offset_fd.h zero/
cp $G0/zero/gkyl_evalf_def.h zero/
cp $G0/zero/gkyl_fv_proj.h zero/
cp $G0/zero/gkyl_gauss_quad_data.h zero/
cp $G0/zero/gkyl_mpi_comm.h zero/
cp $G0/zero/gkyl_mpi_comm_priv.h zero/
cp $G0/zero/gkyl_null_comm.h zero/
cp $G0/zero/gkyl_null_comm_priv.h zero/
cp $G0/zero/gkyl_proj_on_basis.h zero/
cp $G0/zero/gkyl_range.h zero/
cp $G0/zero/gkyl_rect_decomp.h zero/
cp $G0/zero/gkyl_rect_grid.h zero/
cp $G0/zero/gkyl_rect_grid_priv.h zero/
cp $G0/zero/gkyl_ref_count.h zero/
cp $G0/zero/gkyl_rrobin_decomp.h zero/
cp $G0/zero/gkyl_util.h zero/
cp $G0/zero/gkyl_vargm.h zero/
cp $G0/zero/mpi_comm.c zero/
cp $G0/zero/null_comm.c zero/
cp $G0/zero/proj_on_basis.c zero/
cp $G0/zero/range.c zero/
cp $G0/zero/rect_decomp.c zero/
cp $G0/zero/rect_grid.c zero/
cp $G0/zero/rrobin_decomp.c zero/
cp $G0/zero/util.c zero/

# unit
mkdir -p unit
cp $G0/unit/ctest_array.c unit/
cp $G0/unit/ctest_basis.c unit/
cp $G0/unit/ctest_dynvec.c unit/
cp $G0/unit/ctest_eval_offset_fd.c unit/
cp $G0/unit/ctest_fv_proj.c unit/
cp $G0/unit/ctest_null_comm.c unit/
cp $G0/unit/ctest_proj_on_basis.c unit/
cp $G0/unit/ctest_range.c unit/
cp $G0/unit/ctest_rect_grid.c unit/
cp $G0/unit/mctest_mpi_comm.c unit/
cp $G0/unit/mctest_mpi_comm_read.c unit/
