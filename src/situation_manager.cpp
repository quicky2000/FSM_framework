#include "situation_manager.h"
#include "FSM_situation_if.h"

#include <iostream>
using namespace std;

namespace FSM_framework
{
  //----------------------------------------------------------------------------
  situation_manager::situation_manager(void)
  {
  }

  //----------------------------------------------------------------------------
  situation_manager::~situation_manager(void)
  {
    for(set<FSM_interfaces::FSM_situation_if*,pointer_comparator>::const_iterator l_iter = m_set.begin();
        m_set.end() != l_iter;
        ++l_iter)
      {
        delete *l_iter;
      }
  }

  //----------------------------------------------------------------------------
  FSM_interfaces::FSM_situation_if & situation_manager::get_unique_situation(FSM_interfaces::FSM_situation_if & p_situation)
  {
    FSM_interfaces::FSM_situation_if * l_result = & p_situation;
    set<FSM_interfaces::FSM_situation_if*,pointer_comparator>::const_iterator l_iter = m_set.find(&p_situation);
    if(l_iter != m_set.end())
      {
        if(*l_iter != & p_situation)
          {
            l_result = *l_iter;
            delete & p_situation;
          }
      }
    else
      {
        m_set.insert(&p_situation);
      }
    return *l_result;
  }
}
//EOF
