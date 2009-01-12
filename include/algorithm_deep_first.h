#ifndef ALGORITHM_DEEP_FIRST
#define ALGORITHM_DEEP_FIRST

#include "framework_algorithm_if.h"
#include "situation_tree_node.h"
#include "situation_manager.h"

class algorithm_deep_first: public framework_algorithm_if
{
 public:
  // Methods inherited from interface
  void run(void);
  std::string getString(void);
  
  static void registerAlgorithm(std::map<std::string,FSM_framework_algorithm_creator > &p_factory);
 private:
  std::map<const FSM_situation_if*,situation_tree_node> m_situation_tree;
  situation_manager m_situation_manager;
};

framework_algorithm_if* createAlgorithmDeepFirst(void);

#endif /*ALGORITHM_DEEP_FIRST */
