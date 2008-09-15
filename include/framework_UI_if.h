#ifndef FRAMEWORK_UI_IF
#define FRAMEWORK_UI_IF

#include <vector>
#include <string>

class framework_UI_if
{
 public:
  virtual void displayLoadedFsm(std::vector<std::string> *p_FSM_list)=0;
  virtual void displayLoadedFsmUi(std::vector<std::string> *p_FSM_UI_list)=0;
  virtual void displayLoadedAlgorithm(std::vector<std::string> *p_algorithm_list)=0;
  virtual void displayWarningMessage(std::string p_message)=0;
  virtual void displayErrorMessage(std::string p_message)=0;

  virtual ~framework_UI_if(void);
};
#endif /* FRAMEWORK_UI_IF */
