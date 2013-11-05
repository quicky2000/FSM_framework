#include "framework_algorithm_if.h"
#include <assert.h>

using namespace std;

namespace FSM_framework
{
  //-----------------------------------------------------------------------------
  framework_algorithm_if::framework_algorithm_if(void):
    m_fsm(NULL),
    m_fsm_ui(NULL)
  {
  }

  //-----------------------------------------------------------------------------
  framework_algorithm_if::~framework_algorithm_if(void)
  {
    // Removing destructors
    // We assume that they will be destructed by framework
    //	if(m_fsm != NULL)
    //	{
    //		delete m_fsm;
    m_fsm = NULL;
    //	}
    //	if(m_fsm_ui != NULL)
    //	{
    //		delete m_fsm_ui;
    m_fsm_ui = NULL;
    //	}
  }

  //-----------------------------------------------------------------------------
  void framework_algorithm_if::set_fsm
  (
   FSM_interfaces::FSM_if *p_fsm
   )
  {
    assert(p_fsm);
    m_fsm = p_fsm;
  }

  //-----------------------------------------------------------------------------
  void framework_algorithm_if::set_fsm_ui
  (
   FSM_interfaces::FSM_UI_if *p_fsm_ui
   )
  {
    assert(p_fsm_ui);
    m_fsm_ui = p_fsm_ui;
  }

  //-----------------------------------------------------------------------------
  FSM_interfaces::FSM_if* framework_algorithm_if::get_fsm(void)
  {
    assert(m_fsm);
    return m_fsm;
  }

  //-----------------------------------------------------------------------------
  FSM_interfaces::FSM_UI_if* framework_algorithm_if::get_fsm_ui(void)
  {
    assert(m_fsm_ui);
    return m_fsm_ui;
  }

  //-----------------------------------------------------------------------------
  void register_framework_algorithm(const string & p_algorithm_name,
                                    FSM_framework_algorithm_creator_t p_creator,
                                    map<string,FSM_framework_algorithm_creator_t> & p_factory)
  {
    p_factory.insert(map<string,FSM_framework_algorithm_creator_t>::value_type(p_algorithm_name,p_creator));
  }
}
//EOF
