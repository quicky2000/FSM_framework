#ifndef SITUATION_TREE_NODE_H
#define SITUATION_TREE_NODE_H

#include "FSM_types.h"
#include <string>
#include <map>
#include <set>

namespace FSM_interfaces
{
  class FSM_situation_if;
}

namespace FSM_framework
{
  class situation_tree_node
  {
  public:

    /**
       Constructor without predecessor information 
       @param p_situation : situation of node
    */
    situation_tree_node(FSM_interfaces::FSM_situation_if & p_situation);

    /**
       Constructor with predecessor information 
       @param p_situation : situation of node
       @param p_predecessor_id : id of predecessor situation
       @param p_predecessor_transtion : index of transition used to come from predecessor
    */
    situation_tree_node(FSM_interfaces::FSM_situation_if  & p_situation,
                        FSM_interfaces::FSM_situation_if & p_predecessor_id,
                        const FSM_interfaces::FSM_types::transition_index_t & p_predecessor_transition);

    /**
       Method to access to situation contained in the node
    */
    FSM_interfaces::FSM_situation_if & get_situation(void)const;

    /**
       Method to get the list of unexplored transitions
       @return list of unexplored transitions
    */
    const std::set<FSM_interfaces::FSM_types::transition_index_t> & get_unexplored_transitions(void)const;

    /**
       Method to indicate that a transition is explored
       @param p_transition index of transition to mark explored
    */
    void set_transition_explored(const FSM_interfaces::FSM_types::transition_index_t & p_transition_id);

    /**
       Method to indicate that all transition are explored
    */
    void set_all_transition_explored(void);

    /**
       Method to get the list of predecessors
    */
    const std::map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> & get_predecessor_situations(void)const;

  private:
    /**
       Method to initalize unexplored transition list
    */
    void initialize_unexplored_transition(void);

    FSM_interfaces::FSM_situation_if & m_situation;
    std::set<FSM_interfaces::FSM_types::transition_index_t> m_unexplored_transitions;
    std::map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> m_successor_situations;
    std::map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> m_predecessor_situations;

  };
}
#endif // SITUATION_TREE_NODE_H 
//EOF
