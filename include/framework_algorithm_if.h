#ifndef FRAMEWORK_ALGORITHM_IF_H
#define FRAMEWORK_ALGORITHM_IF_H

#include <string>
#include <map>

class FSM_if;
class FSM_UI_if;

class framework_algorithm_if
{
 public:
  // Constructor and destructor
  framework_algorithm_if(void);
  virtual ~framework_algorithm_if(void);

  // Methods to implement
  virtual void run(void)=0;
  virtual std::string getString(void)=0;

  // Accessors
  void setFsm(FSM_if *p_FSM);
  void setFsmUi(FSM_UI_if *p_FSM_UI);
  FSM_if* getFsm(void);
  FSM_UI_if* getFsmUi(void);

 private:
  FSM_if *m_fsm;
  FSM_UI_if *m_fsm_ui;
}
;

typedef framework_algorithm_if *(*FSM_framework_algorithm_creator)(void);

void registerFrameworkAlgorithm(std::string p_algorithm_name,FSM_framework_algorithm_creator p_creator,std::map<std::string,FSM_framework_algorithm_creator> &p_factory);

#endif /* FRAMEWORK_ALGORITHM_IF_H */
