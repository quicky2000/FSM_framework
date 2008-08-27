#ifndef ALGORITHM_BASIC
#define ALGORITHM_BASIC

#include "framework_algorithm_if.h"

class algorithm_basic: public framework_algorithm_if
{
 public:
  // Methods inherited from interface
  void run(void);
  std::string getString(void);
	
  static void registerAlgorithm(std::map<std::string,FSM_framework_algorithm_creator > &p_factory);
};

framework_algorithm_if* createAlgorithmBasic(void);

#endif /* ALGORITHM_BASIC */
