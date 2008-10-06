#include "algorithm_deep_first_weighted.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include "FSM_weighted_transition_index_if.h"
#include "FSM_weighted_transition_index_comparator.h"

#include <iostream>
#include <assert.h>
using namespace std;

//-----------------------------------------------------------------------------
void algorithm_deep_first_weighted::run(void)
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
	  string l_unique_id = l_current_situation->getUniqueId();

	      
	  // Check if situation was already encoutered
	  map<string,situation_tree_node>::iterator l_node_iter = m_situation_tree.find(l_unique_id);
	  map<string,vector<FSM_weighted_transition_index_if*> >::iterator l_weight_iter = m_situation_weighted_transition_index.find(l_unique_id);
	  if(l_node_iter == m_situation_tree.end() || l_weight_iter ==  m_situation_weighted_transition_index.end())
	    {
	      cout << "Computing transitions" << endl ;
	      cout << "Current situation : " << l_current_situation << " \"" << l_unique_id << "\"" <<endl ; 
	      getFsmUi()->displaySituation(l_current_situation) ;

	      getFsm()->computeTransitions();

	      // Store current situation with its predecessor relation if it exists
	      if(l_previous_situation != NULL)
		{
		  l_node_iter = m_situation_tree.insert(map<string,situation_tree_node>::value_type(l_unique_id,situation_tree_node(l_current_situation,l_previous_situation->getUniqueId(),l_previous_transition))).first;
		}
	      else
		{
		  l_node_iter = m_situation_tree.insert(map<string,situation_tree_node>::value_type(l_unique_id,situation_tree_node(l_current_situation))).first;
		}

	      // Weighted code
	      l_weight_iter = m_situation_weighted_transition_index.insert(map<string,vector<FSM_weighted_transition_index_if*> >::value_type(l_unique_id,vector<FSM_weighted_transition_index_if*>())).first;
	      getFsm()->computeTransitionWeights(l_weight_iter->second);

	      sort(l_weight_iter->second.begin(),l_weight_iter->second.end(),FSM_weighted_transition_index_comparator());

	      vector<FSM_weighted_transition_index_if*>::const_iterator l_iter = l_weight_iter->second.begin();
	      vector<FSM_weighted_transition_index_if*>::const_iterator l_iter_end = l_weight_iter->second.end();

	      while(l_iter != l_iter_end)
		{
		  cout << (*l_iter)->getString() << "\t transition is " << l_current_situation->getCurrentContext()->getTransition((*l_iter)->getTransitionIndex())->toString() << endl ;
		  l_iter++;
		}

	      cout << "Total of situation = " <<  m_situation_tree.size() << endl;
	    }
	  else if(l_current_situation != l_node_iter->second.getSituation())
	    {
	      delete l_current_situation;
	      l_current_situation = l_node_iter->second.getSituation();
	      getFsm()->setCurrentSituation(l_current_situation);
	    }
	  
	  situation_tree_node & l_situation_tree_node = l_node_iter->second;
	  const set<unsigned int> &l_unexplored_transitions = l_situation_tree_node.getUnexploredTransitions();
	  vector<FSM_weighted_transition_index_if*> &l_weighted_transitions = l_weight_iter->second;
		
	  cout << "Situation valid = " << l_current_situation->isValid() << endl ;
	  cout << "Non explored transitions : " << l_unexplored_transitions.size() <<endl ;
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
		  l_previous_transition = (*l_weighted_transitions.begin())->getTransitionIndex();
		  l_previous_situation = l_current_situation;

		  cout << "Select transition number : " << l_previous_transition << endl ;

		  // Compute the next situation
		  getFsm()->selectTransition(l_previous_transition);

		  // Indicate that transition is explored
		  if((*l_weighted_transitions.begin())->getWeight())
		    {
		      l_situation_tree_node.setTransitionExplored(l_previous_transition);
		      l_weighted_transitions.erase(l_weighted_transitions.begin());
		    }
		  else
		    {
		      l_situation_tree_node.setAllTransitionExplored();
		      l_weighted_transitions.clear();
		    }
		}
	      // No more transition available so we go back for one step if possible
	      else
		{
	     
		  const map<unsigned int,string> &l_predecessor_situations = l_situation_tree_node.getPredecessorSituations();
		  // Check if there is a predecessor
		  if(l_predecessor_situations.size())
		    {
		      l_previous_situation = NULL;

		      // Getting predecessor situation
		      map<string,situation_tree_node>::const_iterator l_previous_node_iter =  m_situation_tree.find(l_predecessor_situations.begin()->second);

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
string algorithm_deep_first_weighted::getString(void)
{
  return "algorithm_deep_first_weighted";
}

//-----------------------------------------------------------------------------
void algorithm_deep_first_weighted::registerAlgorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
{
  registerFrameworkAlgorithm("algorithm_deep_first_weighted",createAlgorithmDeepFirstWeighted,p_factory);
}

//-----------------------------------------------------------------------------
framework_algorithm_if* createAlgorithmDeepFirstWeighted(void)
{
  return new algorithm_deep_first_weighted();
}

#ifdef EXTERNAL_ALGORITHM
//-----------------------------------------------------------------------------
extern "C"
{
  void registerAlgorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
  {
    registerFrameworkAlgorithm("algorithm_deep_first_weighted",createAlgorithmDeepFirst,p_factory);
  }
}
#endif

//EOF
