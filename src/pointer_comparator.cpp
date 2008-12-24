#include "pointer_comparator.h"

#include "FSM_situation_if.h"

#include <iostream>
using namespace std;

//------------------------------------------------------------------------------
bool pointer_comparator::operator()(const FSM_situation_if* p_op1,const FSM_situation_if* p_op2)const
{
  //assert(p_op1 && p_op2);
  return p_op1->less(p_op2);
}

//EOF
