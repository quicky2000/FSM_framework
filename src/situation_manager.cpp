#include "situation_manager.h"
#include "FSM_situation_if.h"

#include <iostream>
using namespace std;

situation_manager::situation_manager(void)
{
}

FSM_situation_if* situation_manager::getUniqueSituation(FSM_situation_if *p_situation)
{
  FSM_situation_if *l_result = p_situation;
  set<FSM_situation_if*,pointer_comparator>::const_iterator l_iter = m_set.find(p_situation);
  if(l_iter != m_set.end())
    {
      l_result = *l_iter;
      delete p_situation;
    }
  else
    {
      m_set.insert(p_situation);
    }
  return l_result;
}
