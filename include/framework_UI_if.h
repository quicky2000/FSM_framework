#ifndef FRAMEWORK_UI_IF
#define FRAMEWORK_UI_IF

#include <vector>
#include <string>

namespace FSM_framework
{
  class framework_UI_if
  {
  public:
    virtual void display_loaded_fsm(const std::vector<std::string> & p_FSM_list)=0;
    virtual void display_loaded_fsm_ui(const std::vector<std::string> & p_FSM_UI_list)=0;
    virtual void display_loaded_algorithm(const std::vector<std::string> & p_algorithm_list)=0;
    virtual void display_warning_message(const std::string & p_message)=0;
    virtual void display_error_message(const std::string & p_message)=0;

    virtual ~framework_UI_if(void);
  };
}
#endif // FRAMEWORK_UI_IF 
//EOF
