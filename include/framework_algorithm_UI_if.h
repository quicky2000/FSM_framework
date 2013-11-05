#ifndef FRAMEWORK_ALGORITHM_UI_IF_H
#define FRAMEWORK_ALGORITHM_UI_IF_H

#include <string>
#include <map>

namespace FSM_framework
{
  class framework_algorithm_UI_if
  {
  public:
    virtual const std::string & get_type(void)const=0;
    
    inline virtual ~framework_algorithm_UI_if(void){}
  };

  typedef framework_algorithm_UI_if *(*FSM_framework_algorithm_UI_creator_t)(void);

  void register_framework_algorithm_ui(const std::string & p_algorithm_name,
                                       FSM_framework_algorithm_UI_creator_t p_creator,
                                       std::map<std::string,FSM_framework_algorithm_UI_creator_t> &p_factory);
}
#endif // FRAMEWORK_ALGORITHM_UI_IF_H 
//EOF
