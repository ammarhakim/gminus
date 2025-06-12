#include <acutest.h>
#include <mpack.h>

#include <gkyl_tensor_field.h>
#include <gkyl_tensor_field_ops.h>
#include <gkyl_util.h>

// This test is intended to verify: verify: h^ij h_jk = \delta^i_k = \delta_i^k raised in place
void test_tensor_field_raise_idx()
{

  int rank = 2; 
  int ndim = 3;
  int size = 10;

  enum gkyl_tensor_index_loc iloc_cov[GKYL_MAX_DIM];
  enum gkyl_tensor_index_loc iloc_contra[GKYL_MAX_DIM];
  for (int i=0; i<rank; ++i) { 
    iloc_cov[i] = GKYL_TENSOR_INDEX_LOWER;
    iloc_contra[i] = GKYL_TENSOR_INDEX_UPPER;
  }

  // Diagonal metric example. metric_ij = diag(0.5, 0.5, 0.5) and metric_ij_inv( 2, 2, 2 )
  // This test is intended to verify: h^ij h_jk = \delta^i_k
  struct gkyl_tensor_field *diag_metric_cov = gkyl_tensor_field_new(rank,ndim,size,iloc_cov);
  struct gkyl_tensor_field *diag_metric_contra = gkyl_tensor_field_new(rank,ndim,size,iloc_contra);

  int idx[GKYL_MAX_DIM] = {0.0, 0.0}; 
  for (unsigned i=0; i<size; ++i){
    for (unsigned j=0; j<ndim; ++j){
      for (unsigned k=0; k<ndim; ++k){
        double val = 0;
        idx[0] = j; idx[1] = k;
        if (j == k) {
          val = 0.5;
          gkyl_tensor_field_elem_set(diag_metric_cov, i, idx, val);
          gkyl_tensor_field_elem_set(diag_metric_contra, i, idx, 1.0/val);
        } 
        else {
          gkyl_tensor_field_elem_set(diag_metric_cov, i, idx, 0.0);
          gkyl_tensor_field_elem_set(diag_metric_contra, i, idx, 0.0);
        }
      }
    }
  }

  // Compute h^ij h_jk
  int idx_to_raise = 0;
  gkyl_tensor_field_raise_idx(diag_metric_contra,idx_to_raise, diag_metric_cov); 

  // test that the result is delta^i_j
  for (unsigned i=0; i<size; ++i){
    for (unsigned j=0; j<ndim; ++j){
      for (unsigned k=0; k<ndim; ++k){
        idx[0] = j; idx[1] = k;
        const double val = gkyl_tensor_field_elem_fetch(diag_metric_cov, i, idx);
        if (j == k) TEST_CHECK( val == 1.0 );
        if (j != k) TEST_CHECK( val == 0.0 );
      }
    }
  }

  TEST_CHECK( diag_metric_contra->iloc[0] == GKYL_TENSOR_INDEX_UPPER );
  TEST_CHECK( diag_metric_contra->iloc[1] == GKYL_TENSOR_INDEX_UPPER );
  TEST_CHECK( diag_metric_cov->iloc[0] == GKYL_TENSOR_INDEX_UPPER );
  TEST_CHECK( diag_metric_cov->iloc[1] == GKYL_TENSOR_INDEX_LOWER );

  gkyl_tensor_field_release(diag_metric_cov);
  gkyl_tensor_field_release(diag_metric_contra);
}

// This test is intended to verify: h_ij h^jk = \delta_i^k raised in place
void test_tensor_field_lower_idx()
{

  int rank = 2; 
  int ndim = 3;
  int size = 10;

  enum gkyl_tensor_index_loc iloc_cov[GKYL_MAX_DIM];
  enum gkyl_tensor_index_loc iloc_contra[GKYL_MAX_DIM];
  for (int i=0; i<rank; ++i) { 
    iloc_cov[i] = GKYL_TENSOR_INDEX_LOWER;
    iloc_contra[i] = GKYL_TENSOR_INDEX_UPPER;
  }

  // Diagonal metric example. metric_ij = diag(0.5, 0.5, 0.5) and metric_ij_inv( 2, 2, 2 )
  struct gkyl_tensor_field *diag_metric_cov = gkyl_tensor_field_new(rank,ndim,size,iloc_cov);
  struct gkyl_tensor_field *diag_metric_contra = gkyl_tensor_field_new(rank,ndim,size,iloc_contra);

  int idx[GKYL_MAX_DIM] = {0.0, 0.0}; 
  for (unsigned i=0; i<size; ++i){
    for (unsigned j=0; j<ndim; ++j){
      for (unsigned k=0; k<ndim; ++k){
        double val = 0;
        idx[0] = j; idx[1] = k;
        if (j == k) {
          val = 0.5;
          gkyl_tensor_field_elem_set(diag_metric_cov, i, idx, val);
          gkyl_tensor_field_elem_set(diag_metric_contra, i, idx, 1.0/val);
        } 
        else {
          gkyl_tensor_field_elem_set(diag_metric_cov, i, idx, 0.0);
          gkyl_tensor_field_elem_set(diag_metric_contra, i, idx, 0.0);
        }
      }
    }
  }

  // Compute h^ij h_jk
  int idx_to_raise = 0;
  gkyl_tensor_field_lower_idx(diag_metric_cov, idx_to_raise, diag_metric_contra); 

  // test that the result is delta^i_j
  for (unsigned i=0; i<size; ++i){
    for (unsigned j=0; j<ndim; ++j){
      for (unsigned k=0; k<ndim; ++k){
        idx[0] = j; idx[1] = k;
        const double val = gkyl_tensor_field_elem_fetch(diag_metric_contra, i, idx);
        if (j == k) TEST_CHECK( val == 1.0 );
        if (j != k) TEST_CHECK( val == 0.0 );
      }
    }
  }

  TEST_CHECK( diag_metric_contra->iloc[0] == GKYL_TENSOR_INDEX_LOWER );
  TEST_CHECK( diag_metric_contra->iloc[1] == GKYL_TENSOR_INDEX_UPPER );
  TEST_CHECK( diag_metric_cov->iloc[0] == GKYL_TENSOR_INDEX_LOWER );
  TEST_CHECK( diag_metric_cov->iloc[1] == GKYL_TENSOR_INDEX_LOWER );

  gkyl_tensor_field_release(diag_metric_cov);
  gkyl_tensor_field_release(diag_metric_contra);
}

TEST_LIST = {
  { "test_tensor_field_raise_idx", test_tensor_field_raise_idx },  
  { "test_tensor_field_lower_idx", test_tensor_field_lower_idx },  
  { NULL, NULL },
};
