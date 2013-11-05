#ifndef POINTER_COMPARATOR_H
#define POINTER_COMPARATOR_H

namespace FSM_interfaces
{
  class FSM_situation_if;
}

namespace FSM_framework
{
  class pointer_comparator// :public std::binary_function<T*,T*,bool>
  {
  
  public:
    bool operator()(const FSM_interfaces::FSM_situation_if *p_op1,
                    const FSM_interfaces::FSM_situation_if *p_op2)const;

  private:
  
  };
}
#endif // POINTER_COMPARATOR_H 
//EOF
