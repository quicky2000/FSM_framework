#include "framework_controler.h"
#include "framework_base.h"
#include "framework_UI_if.h"
#include "quicky_exception.h"

#include <iostream>
using namespace std;

namespace FSM_framework
{
  //-----------------------------------------------------------------------------
  framework_controler::framework_controler(framework_UI_if *p_framework_ui)
  {
    m_framework_ui= p_framework_ui;
    m_framework = new framework_base(this);
  }

  //-----------------------------------------------------------------------------
  framework_controler::~framework_controler(void)
  {
    delete m_framework;
  }

  //-----------------------------------------------------------------------------
  void framework_controler::load_library(const std::string & p_name)
  {
    try
      {
        m_framework->loadLibrary(p_name);
        m_framework_ui->display_loaded_fsm(m_framework->get_fsm_list());
        m_framework_ui->display_loaded_fsm_ui(m_framework->get_fsm_ui_list());
        m_framework_ui->display_loaded_algorithm(m_framework->get_algorithm_list());
      }
    catch(std::exception & e)
      {
        display_error_message(e.what());
      }
  }

  //-----------------------------------------------------------------------------
  void framework_controler::select_fsm(const std::string & p_name)
  {
    m_framework->select_fsm(p_name);
  }

  //-----------------------------------------------------------------------------
  void framework_controler::select_fsm_ui(const std::string & p_name)
  {
    m_framework->select_fsm_ui(p_name);
  }

  //-----------------------------------------------------------------------------
  void framework_controler::select_algorithm(const std::string & p_name)
  {
    m_framework->select_algorithm(p_name);
  }

  //-----------------------------------------------------------------------------
  void framework_controler::run(void)
  {
    m_framework->run();
  }

  //-----------------------------------------------------------------------------
  void framework_controler::display_warning_message(const std::string & p_message)
  {
    m_framework_ui->display_warning_message(p_message);
  }

  //-----------------------------------------------------------------------------
  void framework_controler::display_error_message(const std::string & p_message)
  {
    m_framework_ui->display_error_message(p_message);
  }
}
//EOF
