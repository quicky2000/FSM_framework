#ifndef ALGORITHM_WIDE
#define ALGORITHM_WIDE

#include "framework_algorithm_if.h"
#include "situation_tree_node.h"
#include "situation_manager.h"

#include <vector>

namespace FSM_framework
{
  class algorithm_wide: public framework_algorithm_if
  {
  public:
    // Methods inherited from interface
    void run(void);
    const std::string & get_string(void)const;
	
    static void register_algorithm(std::map<std::string,FSM_framework_algorithm_creator_t > &p_factory);

  private:
    std::map<FSM_interfaces::FSM_situation_if *,situation_tree_node> m_situation_tree;
    std::vector<FSM_interfaces::FSM_situation_if *> m_situation_vector;
    situation_manager m_situation_manager;
    static const std::string m_class_name;
  };

  framework_algorithm_if & create_algorithm_wide(void);
}
#endif // ALGORITHM_WIDE
//EOF
