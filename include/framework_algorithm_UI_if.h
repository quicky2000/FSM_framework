#ifndef FRAMEWORK_ALGORITHM_UI_IF_H
#define FRAMEWORK_ALGORITHM_UI_IF_H

#include <string>
#include <map>

class framework_algorithm_UI_if
{
 public:
  virtual std::string getType(void)=0;
};

typedef framework_algorithm_UI_if *(*FSM_framework_algorithm_UI_creator)(void);

void registerFrameworkAlgorithmUI(std::string p_algorithm_name,FSM_framework_algorithm_UI_creator p_creator,std::map<std::string,FSM_framework_algorithm_UI_creator> &p_factory);

#endif /* FRAMEWORK_ALGORITHM_UI_IF_H */
