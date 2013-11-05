#include "situation_tree_node.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"

#include <assert.h>
using namespace std;

namespace FSM_framework
{
  //------------------------------------------------------------------------------
  situation_tree_node::situation_tree_node(
                                           FSM_interfaces::FSM_situation_if & p_situation):
    m_situation(p_situation)
  {
    initialize_unexplored_transition();
  }

  //------------------------------------------------------------------------------
  situation_tree_node::situation_tree_node(
                                           FSM_interfaces::FSM_situation_if & p_situation,
                                           FSM_interfaces::FSM_situation_if & p_predecessor_id,
                                           const FSM_interfaces::FSM_types::transition_index_t & p_predecessor_transition):
    m_situation(p_situation)
  {
    initialize_unexplored_transition();
    m_predecessor_situations.insert( map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &>::value_type(p_predecessor_transition,p_predecessor_id));
  }

  //------------------------------------------------------------------------------
  const set<FSM_interfaces::FSM_types::transition_index_t> & situation_tree_node::get_unexplored_transitions(void)const
  {
    return m_unexplored_transitions;
  }

  //------------------------------------------------------------------------------
  const map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> & situation_tree_node::get_predecessor_situations(void)const
  {
    return m_predecessor_situations;
  }

  //------------------------------------------------------------------------------
  FSM_interfaces::FSM_situation_if & situation_tree_node::get_situation(void)const
  {
    return m_situation;
  }

  //------------------------------------------------------------------------------
  void situation_tree_node::set_all_transition_explored(void)
  {
    m_unexplored_transitions.clear();
  }

  //------------------------------------------------------------------------------
  void situation_tree_node::set_transition_explored(const FSM_interfaces::FSM_types::transition_index_t & p_transition_id)
  {
    m_unexplored_transitions.erase(p_transition_id);
  }

  //------------------------------------------------------------------------------
  void situation_tree_node::initialize_unexplored_transition(void)
  {
    // Set all transition as unexplored
    if( m_situation.get_current_context()->transitions_computed())
      {
        FSM_interfaces::FSM_types::transition_index_t l_nb_transition = m_situation.get_current_context()->get_nb_transitions();
        for(FSM_interfaces::FSM_types::transition_index_t l_transition_index = 0;
            l_transition_index < l_nb_transition ; 
            ++l_transition_index)
          {
            m_unexplored_transitions.insert(l_transition_index);
          }
      }
  
  }
}
//EOF
