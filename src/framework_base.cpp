#include "framework_controler.h"
#include "framework_base.h"
#include "algorithm_basic.h"
#include "algorithm_deep_first.h"

#include <assert.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
using namespace std;

//---------------------------------------------------------------------------
framework_base::framework_base
	(
		framework_controler *p_framework_controler
	):
	m_framework_controler(p_framework_controler),
	m_fsm(NULL),
	m_fsm_ui(NULL),
	m_algorithm(NULL)
{
	cout << "Framework_base 1.0" << endl ;

	assert(m_framework_controler);
	m_register_function_name = "registerFsm" ;

	// Registering algorithms
	algorithm_basic::registerAlgorithm(getAlgorithmFactory());
	algorithm_deep_first::registerAlgorithm(getAlgorithmFactory());
}

//---------------------------------------------------------------------------
framework_base::~framework_base(void)
{
	if(m_framework_controler != NULL)
	{
		m_framework_controler = NULL;
	}
	if(m_fsm != NULL)
	{
		m_fsm = NULL;
	}
	if(m_fsm_ui != NULL)
	{
		m_fsm_ui = NULL;
	}
	if(m_algorithm != NULL)
	{
		m_algorithm = NULL;
	}
//	closeAllLibrary();
}

//---------------------------------------------------------------------------
void framework_base::run(void)
{
	assert(m_algorithm != NULL);
	m_algorithm->setFsm(m_fsm);
	m_algorithm->setFsmUi(m_fsm_ui);
	m_algorithm->run();
}

//---------------------------------------------------------------------------
void framework_base::loadLibrary(string p_library_name)
{
	// Check that library is not already open
	if(!m_library_handles.count(p_library_name))
    {
		// Opening shared library
#ifndef _WIN32
		void* l_library_handle = dlopen (p_library_name.c_str(), RTLD_LAZY);
#else

#ifndef UNICODE
		HMODULE l_library_handle = dlopen (p_library_name.c_str());
#else
		unsigned int l_size = MultiByteToWideChar(CP_ACP, 0, p_library_name.c_str(), -1, NULL, 0);
		WCHAR *l_buf = new WCHAR[l_size];
		MultiByteToWideChar(CP_ACP, 0,p_library_name.c_str(), -1, l_buf, l_size);
		HMODULE l_library_handle = dlopen (l_buf);
#endif
#endif

		if (l_library_handle == NULL)
		{
			stringstream l_stream;
			l_stream << dlerror();
			m_framework_controler->displayErrorMessage("Problem when opening library \""+p_library_name+"\": "+l_stream.str());
			exit(1);
		}

#ifndef _WIN32
		m_library_handles.insert(map<string,void*>::value_type(p_library_name,l_library_handle));
#else
		m_library_handles.insert(map<string,HMODULE>::value_type(p_library_name,l_library_handle));
#endif

		// Searching FSM_creator creator function
		void (*l_func)(map<string, FSM_creator>*);
	
		l_func = (void (*)(map<string, FSM_creator>*)) dlsym(l_library_handle, m_register_function_name.c_str());
		if (l_func == NULL)
		{
			stringstream l_stream;
			l_stream << dlerror();
			m_framework_controler->displayErrorMessage("Unable to find symbol \""+m_register_function_name+"\" "+l_stream.str()); 
			dlclose(l_library_handle);
			exit(-1);
		}
	
		// Exécution de la fonction "func"
		l_func(&m_fsm_factory);
	  
		// Searchign FSM_UI_creator creator function
		void (*l_func_ui)(map<string, FSM_UI_creator>*);
	
		l_func_ui = (void (*)(map<string, FSM_UI_creator>*)) dlsym(l_library_handle, "registerFsmUi");
		if (l_func_ui == NULL)
		{
			stringstream l_stream;
			l_stream << dlerror();
			m_framework_controler->displayErrorMessage("Unable to find symbol \"registerFsmUi\" "+l_stream.str()); 
			dlclose(l_library_handle);
			exit(-1);
		}
	
		// Exécution de la fonction "func"
		l_func_ui(&m_fsm_ui_factory);
	}
	else
    {
		m_framework_controler->displayWarningMessage("library \"" + p_library_name + "\" was already loaded");
    }
}

//---------------------------------------------------------------------------
vector<string> framework_base::getFsmList(void)
{
	vector<string> l_result;
	map<string,FSM_creator>::iterator l_iter = m_fsm_factory.begin();
	map<string,FSM_creator>::iterator l_iter_end = m_fsm_factory.end();

	while(l_iter != l_iter_end)
    {
		l_result.push_back(l_iter->first);
		l_iter++;
    }
	return l_result;
}

//---------------------------------------------------------------------------
vector<string> framework_base::getFsmUiList(void)
{
	vector<string> l_result;
	map<string,FSM_UI_creator>::iterator l_iter = m_fsm_ui_factory.begin();
	map<string,FSM_UI_creator>::iterator l_iter_end = m_fsm_ui_factory.end();

	while(l_iter != l_iter_end)
    {
		l_result.push_back(l_iter->first);
		l_iter++;
    }
	return l_result;
}

//---------------------------------------------------------------------------
vector<string> framework_base::getAlgorithmList(void)
{
	vector<string> l_result;
	map<string,FSM_framework_algorithm_creator>::iterator l_iter = m_algorithm_factory.begin();
	map<string,FSM_framework_algorithm_creator>::iterator l_iter_end = m_algorithm_factory.end();

	while(l_iter != l_iter_end)
    {
		l_result.push_back(l_iter->first);
		l_iter++;
    }
	return l_result;
}

//---------------------------------------------------------------------------
void framework_base::selectFsm(string p_fsm_name)
{
	if(isFsmLoaded(p_fsm_name))
    {
		this->setFsm(getFsmCreator(p_fsm_name)());
    }
	else
    {
		m_framework_controler->displayWarningMessage("WARNING : FSM \"" + p_fsm_name + "\" is not available");
    }
}

//---------------------------------------------------------------------------
void framework_base::selectFsmUi(string p_fsm_ui_name)
{
	if(isFsmUiLoaded(p_fsm_ui_name))
    {
		this->setFsmUi(getFsmUiCreator(p_fsm_ui_name)());
    }
  else
    {
		m_framework_controler->displayWarningMessage("WARNING : FSM_UI \"" + p_fsm_ui_name+ "\" is not available");
    }
}

//---------------------------------------------------------------------------
void framework_base::selectAlgorithm(string p_algorithm_name)
{
	if(isAlgorithmLoaded(p_algorithm_name))
    {
		this->setAlgorithm(getAlgorithmCreator(p_algorithm_name)());
    }
	else
    {
		m_framework_controler->displayWarningMessage("WARNING : FSM \"" + p_algorithm_name + "\" is not available");
    }
}

//---------------------------------------------------------------------------
bool framework_base::isFsmLoaded(string p_fsm_name)
{
	return m_fsm_factory.count(p_fsm_name);
}

//---------------------------------------------------------------------------
bool framework_base::isFsmUiLoaded(string p_fsm_ui_name)
{
	return m_fsm_ui_factory.count(p_fsm_ui_name);
}

//---------------------------------------------------------------------------
bool framework_base::isAlgorithmLoaded(string p_algorithm_name)
{
	return m_algorithm_factory.count(p_algorithm_name);
}

//---------------------------------------------------------------------------
FSM_creator framework_base::getFsmCreator(string p_fsm_name)
{
	if(m_fsm_factory.count(p_fsm_name) == 0)
	{
		m_framework_controler->displayErrorMessage("Framework ERROR : no fsm creator for fsm of type \"" + p_fsm_name + "\"");
		exit(-1);
	}
	return m_fsm_factory[p_fsm_name];
}

//---------------------------------------------------------------------------
FSM_UI_creator framework_base::getFsmUiCreator(string p_fsm_name)
{
	if(m_fsm_ui_factory.count(p_fsm_name) == 0)
	{
		m_framework_controler->displayErrorMessage("Framework ERROR : no fsm_ui creator for fsm of type \""+ p_fsm_name + "\"");
		exit(-1);
	}
	return m_fsm_ui_factory[p_fsm_name];
}

//---------------------------------------------------------------------------
FSM_framework_algorithm_creator framework_base::getAlgorithmCreator(string p_algorithm_name)
{
	if(m_algorithm_factory.count(p_algorithm_name) == 0)
	{
		m_framework_controler->displayErrorMessage("Framework ERROR : no algorithm creator for algorithm of type \"" + p_algorithm_name + "\"" );
		exit(-1);
	}
	return m_algorithm_factory[p_algorithm_name];
}

//---------------------------------------------------------------------------
map<string,FSM_framework_algorithm_creator >& framework_base::getAlgorithmFactory(void)
{
	return m_algorithm_factory;
}

//---------------------------------------------------------------------------
map<string,FSM_framework_algorithm_UI_creator >& framework_base::getAlgorithmUiFactory(void)
{
	return m_algorithm_ui_factory;
}

//---------------------------------------------------------------------------
FSM_if* framework_base::getFsm(void)
{
	return m_fsm;
}

//---------------------------------------------------------------------------
framework_algorithm_if* framework_base::getAlgorithm(void)
{
	return m_algorithm;
}

//---------------------------------------------------------------------------
void framework_base::setFsm(FSM_if *p_fsm)
{
	assert(p_fsm);
	m_fsm = p_fsm;
}

//---------------------------------------------------------------------------
void framework_base::setFsmUi(FSM_UI_if *p_fsm_ui)
{
	assert(p_fsm_ui);
	m_fsm_ui = p_fsm_ui;
}

//---------------------------------------------------------------------------
void framework_base::setAlgorithm(framework_algorithm_if *p_algorithm)
{
	assert(p_algorithm);
	m_algorithm = p_algorithm;
}

//---------------------------------------------------------------------------
void framework_base::registerAlgorithmUiCreator(string p_name, FSM_framework_algorithm_UI_creator p_creator)
{
	if(m_algorithm_ui_factory.count(p_name) == 0)
	{
		m_algorithm_ui_factory.insert(map<string,FSM_framework_algorithm_UI_creator >::value_type(p_name,p_creator));
	}
	else
	{
		m_framework_controler->displayWarningMessage("WARNING : algorithm UI creator \""+p_name+"\" is already registered");
	}
}

//---------------------------------------------------------------------------
void framework_base::closeLibrary(string p_library_name)
{
	if(m_library_handles.count(p_library_name))
    {
		dlclose(m_library_handles[p_library_name]);
    }
  else
    {
		m_framework_controler->displayWarningMessage("library \"" + p_library_name + "\" was not loaded");
    }
}

//---------------------------------------------------------------------------
void framework_base::closeAllLibrary(void)
{
#ifndef _WIN32
	map<string,void*>::iterator l_iter = m_library_handles.begin();
	map<string,void*>::iterator l_iter_end = m_library_handles.end();
#else
	map<string,HMODULE>::iterator l_iter = m_library_handles.begin();
	map<string,HMODULE>::iterator l_iter_end = m_library_handles.end();
#endif

	while(l_iter != l_iter_end)
    {
		dlclose(l_iter->second);      
		l_iter++;
    }
}

string framework_base::m_register_function_name = "Undefined";
