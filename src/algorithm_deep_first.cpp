#include "algorithm_deep_first.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include <iostream>
#include <assert.h>
using namespace std;

//-----------------------------------------------------------------------------
void algorithm_deep_first::run(void)
{
  if(getFsm() != NULL)
    {
      getFsm()->configure();
      FSM_situation_if *l_previous_situation = NULL;
      unsigned int l_previous_transition = 0;

      bool l_continu = true;
      do
	{
	  FSM_situation_if *l_current_situation = getFsm()->getCurrentSituation();
	      
	  // Check if situation was already encoutered
	  FSM_situation_if *l_unique_situation = m_situation_manager.getUniqueSituation(l_current_situation);
	  map<const FSM_situation_if *,situation_tree_node>::iterator l_node_iter = m_situation_tree.find(l_unique_situation);
	  if(l_node_iter == m_situation_tree.end())
	    {
	      cout << "Computing transitions" << endl ;
	      cout << "Current situation : \"" << l_current_situation->getStringId() << "\"" <<endl ; 
	      getFsmUi()->displaySituation(l_current_situation) ;
	      
	      getFsm()->computeTransitions();
	      
	      // Store current situation with its predecessor relation if it exists
	      if(l_previous_situation != NULL)
		{
		  l_node_iter = m_situation_tree.insert(map<FSM_situation_if *,situation_tree_node>::value_type(l_unique_situation,situation_tree_node(l_current_situation,l_previous_situation,l_previous_transition))).first;
		}
	      else
		{
		  l_node_iter = m_situation_tree.insert(map<FSM_situation_if *,situation_tree_node>::value_type(l_unique_situation,situation_tree_node(l_current_situation))).first;
		}
	      cout << "Total of situation = " <<  m_situation_tree.size() << endl;
	    }
	  else if(l_current_situation != l_unique_situation)
	    {
	      l_current_situation = l_unique_situation; 
	      getFsm()->setCurrentSituation(l_unique_situation);
	    }
	  
	  situation_tree_node & l_situation_tree_node = l_node_iter->second;
	  const set<unsigned int> &l_unexplored_transitions = l_situation_tree_node.getUnexploredTransitions();
			
	  //	  cout << "Situation valid = " << l_current_situation->isValid() << endl ;
	  //	  cout << "Non explored transitions : " << l_unexplored_transitions.size() <<endl ;
	  set<unsigned int>::const_iterator l_iter = l_unexplored_transitions.begin();
	  set<unsigned int>::const_iterator l_iter_end = l_unexplored_transitions.end();
	  while(l_iter != l_iter_end)
	    {
	      cout << *l_iter << " " ;
	      l_iter++;
	    }
	  cout << endl ;
 
	  if(!l_current_situation->isFinal())
	    {
	      // Check if it can go deeply
	      if( l_current_situation->isValid() && l_unexplored_transitions.size()>0)
		{
		  // Store current situation to record the relationship of future situation
		  l_previous_transition = *(l_unexplored_transitions.begin());
		  l_previous_situation = l_current_situation;

		  //	      cout << "Select transition number : " << l_previous_transition << endl ;

		  // Compute the next situation
		  getFsm()->selectTransition(l_previous_transition);

		  // Indicate that transition is explored
		  l_situation_tree_node.setTransitionExplored(l_previous_transition);
		}
	      // No more transition available so we go back for one step if possible
	      else
		{
	     
		  const map<unsigned int,FSM_situation_if *> &l_predecessor_situations = l_situation_tree_node.getPredecessorSituations();
		  // Check if there is a predecessor
		  if(l_predecessor_situations.size())
		    {
		      l_previous_situation = NULL;

		      // Getting predecessor situation
		      map<const FSM_situation_if *,situation_tree_node>::const_iterator l_previous_node_iter = 
			m_situation_tree.find(l_predecessor_situations.begin()->second);

		      // Predecessor situation should be in situation tree !!!!
		      assert(l_previous_node_iter != m_situation_tree.end());

		      //		  cout << "Restore previous situation " << l_previous_node_iter->second.getSituation() <<  endl ;
		      // Getting back to previous situation
		      getFsm()->setCurrentSituation(l_previous_node_iter->second.getSituation());
		    }
		  else
		    {		  
		      // We are at the original situation
		      l_continu = false ;
		    }
		}
	    }
	  else
	    {
	      cout << "Final situation found !!!" << endl ;
	      l_continu = false;
	    }
	} while(l_continu);
      cout << "End of algorithm" << endl ;
    }
  else
    {
      cout << "FSM ERROR : no FSM in algorithm" << endl ;
    }
}

//-----------------------------------------------------------------------------
string algorithm_deep_first::getString(void)
{
  return "algorithm_deep_first";
}

//-----------------------------------------------------------------------------
void algorithm_deep_first::registerAlgorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
{
  registerFrameworkAlgorithm("algorithm_deep_first",createAlgorithmDeepFirst,p_factory);
}

//-----------------------------------------------------------------------------
framework_algorithm_if* createAlgorithmDeepFirst(void)
{
  return new algorithm_deep_first();
}

#ifdef EXTERNAL_ALGORITHM
//-----------------------------------------------------------------------------
extern "C"
{
  void registerAlgorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
  {
    registerFrameworkAlgorithm("algorithm_deep_first",createAlgorithmDeepFirst,p_factory);
  }
}
#endif

//EOF
