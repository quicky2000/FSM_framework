#ifndef SITUATION_TREE_NODE_H
#define SITUATION_TREE_NODE_H

#include <string>
#include <map>
#include <set>

class FSM_situation_if;

class situation_tree_node
{
 public:

  /**
     Constructor without predecessor information 
     @param p_situation : situation of node
  */
  situation_tree_node(FSM_situation_if *p_situation);

  /**
     Constructor with predecessor information 
     @param p_situation : situation of node
     @param p_predecessor_id : id of predecessor situation
     @param p_predecessor_transtion : index of transition used to come from predecessor
  */
  situation_tree_node(FSM_situation_if *p_situation,const std::string &p_predecessor_id,unsigned int p_predecessor_transition);

  /**
     Method to access to situation contained in the node
  */
  FSM_situation_if* getSituation(void)const;

  /**
     Method to get the list of unexplored transitions
     @return list of unexplored transitions
  */
  const std::set<unsigned int> getUnexploredTransitions(void)const;

  /**
     Method to indicate that a transition is explored
     @param p_transition index of transition to mark explroed
  */
  void setTransitionExplored(unsigned int p_transition_id);

  /**
     Method to get the list of predecessors
  */
  const std::map<unsigned int,std::string> getPredecessorSituations(void)const;

 private:
  /**
     Method to initalize unexplored transition list
  */
  void initializeUnexploredTransition(void);

  FSM_situation_if *m_situation;
  std::set<unsigned int> m_unexplored_transitions;
  std::map<unsigned int,std::string> m_successor_situations;
  std::map<unsigned int,std::string> m_predecessor_situations;

};
#endif /* SITUATION_TREE_NODE_H */
