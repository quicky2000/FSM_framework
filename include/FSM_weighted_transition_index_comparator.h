#ifndef FSM_WEIGHTED_TRANSITION_INDEX_COMPARATOR_H
#define FSM_WEIGHTED_TRANSITION_INDEX_COMPARATOR_H

#include <functional>

class FSM_weighted_transition_index_if;

class FSM_weighted_transition_index_comparator:
public std::binary_function<FSM_weighted_transition_index_if*,FSM_weighted_transition_index_if*,bool>
{
  
 public:
  bool operator()(FSM_weighted_transition_index_if* p_op1,FSM_weighted_transition_index_if* p_op2);

 private:
  
};

#endif /* FSM_WEIGHTED_TRANSITION_INDEX_IF_H */
