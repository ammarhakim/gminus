#pragma once

#include <gkyl_tensor_field.h>


/**
 * Lowers the index of tensor using the associated metric
 * 
 * @param metric Metric written as a tensor field
 * @param lowered_idx Index to lower of ten
 * @param ten Tensor field
 */
void gkyl_tensor_field_lower_idx(struct gkyl_tensor_field *metric, int lowered_idx, struct gkyl_tensor_field *ten);

/**
 * Raises the index of tensor using the associated metric
 * 
 * @param metric Metric written as a tensor field
 * @param raised_idx Index to raise of ten
 * @param ten Tensor field
 */
void gkyl_tensor_field_raise_idx(struct gkyl_tensor_field *metric, int raised_idx, struct gkyl_tensor_field *ten);