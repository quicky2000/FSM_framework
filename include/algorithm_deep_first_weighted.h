#ifndef ALGORITHM_DEEP_FIRST_WEIGHTED
#define ALGORITHM_DEEP_FIRST_WEIGHTED

#include "framework_algorithm_if.h"
#include "situation_tree_node.h"
#include "situation_manager.h"

#include <vector>

class FSM_weighted_transition_index_if;

class algorithm_deep_first_weighted: public framework_algorithm_if
{
 public:
  // Methods inherited from interface
  void run(void);
  std::string getString(void);
  
  static void registerAlgorithm(std::map<std::string,FSM_framework_algorithm_creator > &p_factory);
 private:
  std::map<std::string,situation_tree_node> m_situation_tree;
  std::map<std::string,std::vector<FSM_weighted_transition_index_if*> > m_situation_weighted_transition_index;
  situation_manager m_situation_manager;
};

framework_algorithm_if* createAlgorithmDeepFirstWeighted(void);

#endif /* ALGORITHM_DEEP_FIRST_WEIGHTED */
