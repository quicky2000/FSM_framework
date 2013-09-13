#ifndef FRAMEWORK_BASE_H
#define FRAMEWORK_BASE_H

#include "framework_algorithm_if.h"
#include "framework_algorithm_UI_if.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "quicky_exception.h"

#include <vector>
#include <string>

// Define for dynamic libraries management
#ifdef _WIN32
#include <windows.h>
#define dlopen LoadLibrary
#define dlerror GetLastError
#define dlclose FreeLibrary
#define dlsym GetProcAddress
#else
#include <dlfcn.h>
#endif

class framework_controler;

class framework_base
{
 public:
  // Constructors/Destructors
  framework_base(framework_controler *p_framework_controler);
  ~framework_base(void);

  /***********/
  /* Methods */
  /***********/
  void run(void);
  void loadLibrary(string p_library_name) throw (quicky_exception::quicky_logic_exception);

  vector<string> getFsmList(void);
  vector<string> getFsmUiList(void);
  vector<string> getAlgorithmList(void);

  void selectFsm(string p_FSM_name);
  void selectFsmUi(string p_FSM_UI_name);
  void selectAlgorithm(string p_algorithm_name);

 protected:
  /***********/
  /* Methods */
  /***********/
  bool isFsmLoaded(string p_fsm_name);
  bool isFsmUiLoaded(string p_FSM_UI_name);
  bool isAlgorithmLoaded(string p_algorithm_name);

  FSM_creator getFsmCreator(string p_fsm_name);
  FSM_UI_creator getFsmUiCreator(string p_FSM_UI_name);
  FSM_framework_algorithm_creator getAlgorithmCreator(string p_algorithm_name);
	
  map<string,FSM_framework_algorithm_creator>& getAlgorithmFactory(void);
  map<string,FSM_framework_algorithm_UI_creator>& getAlgorithmUiFactory(void);

  FSM_if* getFsm(void);
  framework_algorithm_if* getAlgorithm(void);

  void setFsm(FSM_if *p_fsm);
  void setFsmUi(FSM_UI_if *p_fsm_ui);
  void setAlgorithm(framework_algorithm_if *p_algorithm);

  void registerAlgorithmUiCreator(string p_name,FSM_framework_algorithm_UI_creator p_creator);

 private:
  /***********/
  /* Methods */
  /***********/
  void closeLibrary(string p_library_name);
  void closeAllLibrary(void);

  /***********/
  /* Members */
  /***********/
  framework_controler *m_framework_controler;

#ifndef _WIN32
  map<string,void*> m_library_handles;
#else
  map<string,HMODULE> m_library_handles;
#endif
  
  // FSM triplet instance
  FSM_if *m_fsm;
  FSM_UI_if *m_fsm_ui;
  framework_algorithm_if *m_algorithm;

  //Factories
  map<string,FSM_creator> m_fsm_factory;
  map<string,FSM_UI_creator > m_fsm_ui_factory;
  map<string,FSM_framework_algorithm_creator > m_algorithm_factory;
  map<string,FSM_framework_algorithm_UI_creator > m_algorithm_ui_factory;

  static string m_register_function_name;
};

#endif /* FRAMEWORK_BASE_H */
