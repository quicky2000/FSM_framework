#ifndef SITUATION_MANAGER_H
#define SITUATION_MANAGER_H

#include "pointer_comparator.h"

#include <set>

class FSM_situation_if;

class situation_manager
{
 public:
  situation_manager(void);
  FSM_situation_if* getUniqueSituation(FSM_situation_if *p_situation);
 private:
  std::set<FSM_situation_if*,pointer_comparator > m_set;
};

#endif /* SITUATION_MANAGER_H */

//EOF

