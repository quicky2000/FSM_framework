#ifndef ALGORITHM_DEEP_FIRST
#define ALGORITHM_DEEP_FIRST

#include "framework_algorithm_if.h"
#include "situation_tree_node.h"

class algorithm_deep_first: public framework_algorithm_if
{
 public:
  // Methods inherited from interface
  void run(void);
  string getString(void);
  
  static void registerAlgorithm(map<string,FSM_framework_algorithm_creator > &p_factory);
 private:
  map<string,situation_tree_node> m_situation_tree;
};

framework_algorithm_if* createAlgorithmDeepFirst(void);
//TO DELETEvoid registerFrameworkAlgorithm(string p_algorithm_name,FSM_framework_algorithm_creator p_creator,map<string,FSM_framework_algorithm_creator> &p_factory);

#endif
