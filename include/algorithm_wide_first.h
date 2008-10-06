#ifndef ALGORITHM_WIDE_FIRST
#define ALGORITHM_WIDE_FIRST

#include "framework_algorithm_if.h"
#include "situation_tree_node.h"

#include <vector>

class algorithm_wide_first: public framework_algorithm_if
{
 public:
  // Methods inherited from interface
  void run(void);
  std::string getString(void);
	
  static void registerAlgorithm(std::map<std::string,FSM_framework_algorithm_creator > &p_factory);

 private:
  std::map<std::string,situation_tree_node> m_situation_tree;
  std::vector<FSM_situation_if*> m_situation_vector;
  
};

framework_algorithm_if* createAlgorithmWideFirst(void);

#endif /* ALGORITHM_WIDE_FIRST */
