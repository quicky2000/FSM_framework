#ifndef _SITUATION_STACK_H_
#define _SITUATION_STACK_H_

#include <set>
#include <stack>
#include <cassert>

class FSM_situation_if;

namespace FSM_framework
{
  class situation_stack
  {
  public:
    inline void push(FSM_situation_if * p_situation);
    inline bool contains(FSM_situation_if * const p_situation)const;
    inline FSM_situation_if * pop(void);
    inline unsigned int size(void)const;
  private:
    std::set<FSM_situation_if*> m_sorted;
    std::stack<FSM_situation_if*> m_in_order;
  };

  //----------------------------------------------------------------------------
  unsigned int situation_stack::size(void)const
  {
    return m_in_order.size();
  }
  //----------------------------------------------------------------------------
  void situation_stack::push(FSM_situation_if * p_situation)
  {
    assert(m_sorted.end() == m_sorted.find(p_situation));
    m_in_order.push(p_situation);
    m_sorted.insert(p_situation);
  }

  //----------------------------------------------------------------------------
  bool situation_stack::contains(FSM_situation_if * p_situation)const
  {
    return m_sorted.end() != m_sorted.find(p_situation);
  }

  //----------------------------------------------------------------------------
  FSM_situation_if * situation_stack::pop(void)
  {
    assert(m_in_order.size());
    FSM_situation_if * l_popped = m_in_order.top();
    assert(m_sorted.end() != m_sorted.find(l_popped));
    m_sorted.erase(l_popped);
    m_in_order.pop();
    return l_popped;
  }
}

#endif // _SITUATION_STACK_H_
//EOF
