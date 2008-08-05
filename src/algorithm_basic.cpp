#include "algorithm_basic.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include <iostream>
using namespace std;

//-----------------------------------------------------------------------------
void algorithm_basic::run(void)
{
	if(getFsm() != NULL)
	{
		getFsm()->configure();
	    FSM_situation_if *l_previous_situation = NULL;
		bool l_continu = true;
		do
		{

			l_previous_situation = getFsm()->getCurrentSituation();
			getFsmUi()->displaySituation(l_previous_situation) ;
			getFsm()->computeTransitions();

			FSM_context_if *l_context = l_previous_situation->getCurrentContext();
			unsigned int l_nb_transition = l_context->getNbTransitions();
			
			cout << "Available transitions : " << endl ;
			for(unsigned int l_transition_index = 0;l_transition_index < l_nb_transition ; l_transition_index++)
			{
				cout << l_transition_index << " : " <<  l_context->getTransition(l_transition_index)->toString() << endl ;
			}
			unsigned int l_choosen_transition;
			cin >> l_choosen_transition;

			getFsm()->selectTransition(l_choosen_transition);
		} while(l_continu);
	}
	else
	{
		cout << "FSM ERROR : no FSM in algorithm" << endl ;
	}
}

//-----------------------------------------------------------------------------
string algorithm_basic::getString(void)
{
	return "algorithm_basic";
}

//-----------------------------------------------------------------------------
void algorithm_basic::registerAlgorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
{
	registerFrameworkAlgorithm("algorithm_basic",createAlgorithmBasic,p_factory);
}

//-----------------------------------------------------------------------------
framework_algorithm_if* createAlgorithmBasic(void)
{
  return new algorithm_basic();
}

//-----------------------------------------------------------------------------
extern "C"
{
	void registerAlgorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
	{
		registerFrameworkAlgorithm("algorithm_basic",createAlgorithmBasic,p_factory);
	}
}

//-----------------------------------------------------------------------------
void registerFrameworkAlgorithm(string p_algorithm_name,FSM_framework_algorithm_creator p_creator,map<string,FSM_framework_algorithm_creator> &p_factory)
{
	p_factory.insert(map<string,FSM_framework_algorithm_creator>::value_type(p_algorithm_name,p_creator));
}
