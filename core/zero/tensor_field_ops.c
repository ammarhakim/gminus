#include <gkyl_tensor_field_ops_priv.h>
#include <gkyl_tensor_field_ops.h>
#include <gkyl_tensor_field.h>

#include <assert.h>

void 
gkyl_tensor_field_lower_idx(struct gkyl_tensor_field *metric, int lowered_idx, struct gkyl_tensor_field *ten)
{
  // Check that we are lowering a contravariant index
  assert( ten->iloc[lowered_idx] == GKYL_TENSOR_INDEX_UPPER );
  assert( metric->iloc[0]  == GKYL_TENSOR_INDEX_LOWER );
  assert( metric->iloc[1]  == GKYL_TENSOR_INDEX_LOWER );
  gkyl_tensor_field_raise_or_lower_idx(metric, lowered_idx, ten);
  ten->iloc[lowered_idx] = GKYL_TENSOR_INDEX_LOWER;
}

void 
gkyl_tensor_field_raise_idx(struct gkyl_tensor_field *metric, int raised_idx, struct gkyl_tensor_field *ten)
{
  // Check that we are lowering a contravariant index
  assert( ten->iloc[raised_idx] == GKYL_TENSOR_INDEX_LOWER );
  assert( metric->iloc[0]  == GKYL_TENSOR_INDEX_UPPER );
  assert( metric->iloc[1]  == GKYL_TENSOR_INDEX_UPPER );
  gkyl_tensor_field_raise_or_lower_idx(metric, raised_idx, ten);
  ten->iloc[raised_idx] = GKYL_TENSOR_INDEX_UPPER;
}

