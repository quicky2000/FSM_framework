#ifndef ALGORITHM_BASIC
#define ALGORITHM_BASIC

#include "framework_algorithm_if.h"

namespace FSM_framework
{
  class algorithm_basic: public framework_algorithm_if
  {
  public:
    // Methods inherited from interface
    void run(void);
    const std::string & get_string(void)const;
	
    static void register_algorithm(std::map<std::string,FSM_framework_algorithm_creator_t > & p_factory);
    static const std::string m_class_name;
  };

  framework_algorithm_if & create_algorithm_basic(void);
}
#endif // ALGORITHM_BASIC 
//EOF
