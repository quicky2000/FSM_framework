#include "algorithm_wide.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include <iostream>
using namespace std;

//-----------------------------------------------------------------------------
void algorithm_wide::run(void)
{
  if(getFsm() != NULL)
    {
      getFsm()->configure();
      FSM_situation_if *l_previous_situation = NULL;
      bool l_continu = true;

      getFsm()->computeTransitions();
      m_situation_manager.getUniqueSituation(getFsm()->getCurrentSituation());

      // Initialisinng situation vector
      m_situation_vector.push_back(getFsm()->getCurrentSituation());
      vector<FSM_situation_if*>::const_iterator l_iter = m_situation_vector.begin();
 
      do
	{
	  cout << "Vector size = " << m_situation_vector.size() << endl ;
	  cout << "Map size = " << m_situation_tree.size() << endl ;
	  l_previous_situation = *l_iter;
	  cout << "Current situation : " <<endl ; 
	  getFsmUi()->displaySituation(l_previous_situation) ;


	  FSM_context_if *l_context = l_previous_situation->getCurrentContext();
	  unsigned int l_nb_transition = l_context->getNbTransitions();
	      
	  cout << "Available transitions : " << endl ;
	  for(unsigned int l_transition_index = 0;l_transition_index < l_nb_transition ; ++l_transition_index)
	    {
	      cout << l_transition_index << " : " <<  l_context->getTransition(l_transition_index)->toString() << endl ;
	      getFsm()->selectTransition(l_transition_index);
		  
	      FSM_situation_if *l_new_situation = getFsm()->getCurrentSituation();
	      if(l_new_situation->isValid())
		{
		  if(l_new_situation == m_situation_manager.getUniqueSituation(l_new_situation))
		    {
		      getFsm()->computeTransitions();
			  
		      m_situation_vector.push_back(l_new_situation);
		      m_situation_tree.insert( map<FSM_situation_if *,situation_tree_node>::value_type(l_new_situation,situation_tree_node(l_new_situation,l_previous_situation,l_transition_index)));
		    }
		}
	      else
		{
		  delete l_new_situation;
		}
	      getFsm()->setCurrentSituation(l_previous_situation);
	    }
	  m_situation_vector.erase( m_situation_vector.begin());
	  l_iter = m_situation_vector.begin();
	  l_continu = (l_iter !=  m_situation_vector.end());
	} while(l_continu);
    }
  else
    {
      cout << "FSM ERROR : no FSM in algorithm" << endl ;
    }
}

//-----------------------------------------------------------------------------
string algorithm_wide::getString(void)
{
  return "algorithm_wide";
}

//-----------------------------------------------------------------------------
void algorithm_wide::registerAlgorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
{
  registerFrameworkAlgorithm("algorithm_wide",createAlgorithmWideFirst,p_factory);
}

//-----------------------------------------------------------------------------
framework_algorithm_if* createAlgorithmWideFirst(void)
{
  return new algorithm_wide();
}

#ifdef EXTERNAL_ALGORITHM
//-----------------------------------------------------------------------------
extern "C"
{
  void registerAlgorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
  {
    registerFrameworkAlgorithm("algorithm_wide",createAlgorithmWideFirst,p_factory);
  }
}
#endif

//EOF
