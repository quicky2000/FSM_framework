#ifndef FRAMEWORK_CONTROLER_H
#define FRAMEWORK_CONTROLER_H

#include <string>

namespace FSM_framework
{
  class framework_UI_if;
  class framework_base;

  class framework_controler
  {
  public:
    framework_controler(framework_UI_if *p_framework_UI);
    ~framework_controler(void);
    void load_library(const std::string & p_name);
    void select_fsm(const std::string & p_name);
    void select_fsm_ui(const std::string & p_name);
    void select_algorithm(const std::string & p_name);
    void run(void);
    void display_warning_message(const std::string & p_message);
    void display_error_message(const std::string & p_message);
    framework_base* get_framework(void);

  private:
    framework_UI_if *m_framework_ui;
    framework_base *m_framework;
  };
}
#endif /* FRAMEWORK_CONTROLER_H */
