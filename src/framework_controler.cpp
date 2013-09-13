#include "framework_controler.h"
#include "framework_base.h"
#include "framework_UI_if.h"
#include "quicky_exception.h"

#include <iostream>
using namespace std;

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
void framework_controler::loadLibrary(string p_name)
{
  try
    {
      m_framework->loadLibrary(p_name);
      vector<string> l_list = m_framework->getFsmList();
      m_framework_ui->displayLoadedFsm(&l_list);
      l_list = m_framework->getFsmUiList();
      m_framework_ui->displayLoadedFsmUi(&l_list);
      l_list = m_framework->getAlgorithmList();
      m_framework_ui->displayLoadedAlgorithm(&l_list);
    }
  catch(std::exception & e)
    {
      displayErrorMessage(e.what());
    }
}

//-----------------------------------------------------------------------------
void framework_controler::selectFsm(string p_name)
{
  m_framework->selectFsm(p_name);
}

//-----------------------------------------------------------------------------
void framework_controler::selectFsmUi(string p_name)
{
  m_framework->selectFsmUi(p_name);
}

//-----------------------------------------------------------------------------
void framework_controler::selectAlgorithm(string p_name)
{
  m_framework->selectAlgorithm(p_name);
}

//-----------------------------------------------------------------------------
void framework_controler::run(void)
{
  m_framework->run();
}

//-----------------------------------------------------------------------------
void framework_controler::displayWarningMessage(string p_message)
{
  m_framework_ui->displayWarningMessage(p_message);
}

//-----------------------------------------------------------------------------
void framework_controler::displayErrorMessage(string p_message)
{
  m_framework_ui->displayErrorMessage(p_message);
}
