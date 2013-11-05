#ifndef ALGORITHM_DEEP
#define ALGORITHM_DEEP

#include "framework_algorithm_if.h"
#include "situation_tree_node.h"
#include "situation_stack.h"
#include "situation_manager.h"

namespace FSM_framework
{
  class algorithm_deep: public framework_algorithm_if
  {
  public:
    // Methods inherited from interface
    void run(void);
    const std::string & get_string(void)const;
  
    static void register_algorithm(std::map<std::string,FSM_framework_algorithm_creator_t > &p_factory);
  private:
    std::map<FSM_interfaces::FSM_situation_if *,situation_tree_node> m_situation_tree;
    situation_manager m_situation_manager;
    FSM_framework::situation_stack m_situation_stack;
    static const std::string m_class_name;
  };

  framework_algorithm_if & create_algorithm_deep(void);
}
#endif // ALGORITHM_DEEP 
//EOF
