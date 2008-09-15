#include "FSM_weighted_transition_index_comparator.h"
#include "FSM_weighted_transition_index_if.h"

#include <assert.h>

bool FSM_weighted_transition_index_comparator::operator()(FSM_weighted_transition_index_if* p_op1,FSM_weighted_transition_index_if* p_op2)
{
  assert(p_op1 && p_op2);
  return (*p_op1)<(*p_op2);
}

//EOF
