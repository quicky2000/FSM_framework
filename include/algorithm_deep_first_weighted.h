#ifndef ALGORITHM_DEEP_FIRST_WEIGHTED
#define ALGORITHM_DEEP_FIRST_WEIGHTED

#include "framework_algorithm_if.h"
#include "situation_tree_node.h"
#include "situation_manager.h"

#include <vector>

namespace FSM_interfaces
{
  class FSM_weighted_transition_index_if;
}

namespace FSM_framework
{

  class algorithm_deep_first_weighted: public framework_algorithm_if
  {
  public:
    // Methods inherited from interface
    void run(void);
    const std::string & get_string(void)const;
    
    static void register_algorithm(std::map<std::string,FSM_framework_algorithm_creator_t > &p_factory);
  private:
    std::map<FSM_interfaces::FSM_situation_if*,situation_tree_node> m_situation_tree;
    std::map<FSM_interfaces::FSM_situation_if*,std::vector<FSM_interfaces::FSM_weighted_transition_index_if*> > m_situation_weighted_transition_index;
    situation_manager m_situation_manager;
    static const std::string m_class_name;
  };

framework_algorithm_if & create_algorithm_deep_first_weighted(void);
}
#endif // ALGORITHM_DEEP_FIRST_WEIGHTED 
//EOF
