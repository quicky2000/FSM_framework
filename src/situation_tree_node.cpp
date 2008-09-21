#include "situation_tree_node.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"

#include <assert.h>
using namespace std;

//------------------------------------------------------------------------------
situation_tree_node::situation_tree_node(
					 FSM_situation_if *p_situation):
  m_situation(p_situation)
{
  initializeUnexploredTransition();
}

//------------------------------------------------------------------------------
situation_tree_node::situation_tree_node(
					 FSM_situation_if *p_situation,
					 const string &p_predecessor_id,
					 unsigned int p_predecessor_transition):
  m_situation(p_situation)
{
  initializeUnexploredTransition();
  m_predecessor_situations.insert( map<unsigned int,string>::value_type(p_predecessor_transition,p_predecessor_id));
}

//------------------------------------------------------------------------------
const set<unsigned int> situation_tree_node::getUnexploredTransitions(void)const
{
  return m_unexplored_transitions;
}

//------------------------------------------------------------------------------
const map<unsigned int,string> situation_tree_node::getPredecessorSituations(void)const
{
  return m_predecessor_situations;
}

//------------------------------------------------------------------------------
FSM_situation_if* situation_tree_node::getSituation(void)const
{
  return m_situation;
}

//------------------------------------------------------------------------------
void situation_tree_node::setAllTransitionExplored(void)
{
  m_unexplored_transitions.clear();
}

//------------------------------------------------------------------------------
void situation_tree_node::setTransitionExplored(unsigned int p_transition_id)
{
  m_unexplored_transitions.erase(p_transition_id);
}

//------------------------------------------------------------------------------
void situation_tree_node::initializeUnexploredTransition(void)
{
  // Set all transition as unexplored
  unsigned int l_nb_transition = m_situation->getCurrentContext()->getNbTransitions();
  for(unsigned int l_transition_index = 0;l_transition_index < l_nb_transition ; l_transition_index++)
    {
      m_unexplored_transitions.insert(l_transition_index);
    }
  
}
