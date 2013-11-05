#ifndef FSM_WEIGHTED_TRANSITION_INDEX_COMPARATOR_H
#define FSM_WEIGHTED_TRANSITION_INDEX_COMPARATOR_H

#include <functional>

namespace FSM_interfaces
{
  class FSM_weighted_transition_index_if;
}

namespace FSM_framework
{
  class FSM_weighted_transition_index_comparator:
  public std::binary_function<FSM_interfaces::FSM_weighted_transition_index_if*,FSM_interfaces::FSM_weighted_transition_index_if*,bool>
    {
      
    public:
      bool operator()(FSM_interfaces::FSM_weighted_transition_index_if* p_op1,FSM_interfaces::FSM_weighted_transition_index_if* p_op2);
      
    private:
      
    };
}

#endif // FSM_WEIGHTED_TRANSITION_INDEX_IF_H
//EOF
