#ifndef SITUATION_MANAGER_H
#define SITUATION_MANAGER_H

#include "pointer_comparator.h"

#include <set>

namespace FSM_interfaces
{
  class FSM_situation_if;
}

namespace FSM_framework
{
  class situation_manager
  {
  public:
    situation_manager(void);
    ~situation_manager(void);
    FSM_interfaces::FSM_situation_if & get_unique_situation(FSM_interfaces::FSM_situation_if & p_situation);
  private:
    std::set<FSM_interfaces::FSM_situation_if*,pointer_comparator > m_set;
  };
}

#endif // SITUATION_MANAGER_H 
//EOF

