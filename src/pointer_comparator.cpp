#include "pointer_comparator.h"

#include "FSM_situation_if.h"

#include <iostream>
using namespace std;

namespace FSM_framework
{
  //------------------------------------------------------------------------------
  bool pointer_comparator::operator()(const FSM_interfaces::FSM_situation_if * p_op1,const FSM_interfaces::FSM_situation_if * p_op2)const
  {
    //assert(p_op1 && p_op2);
    return p_op1->less(p_op2);
  }
}

//EOF
