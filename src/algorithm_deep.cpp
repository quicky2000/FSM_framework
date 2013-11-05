#include "algorithm_deep.h"
#include "FSM_if.h"
#include "FSM_UI_if.h"
#include "FSM_situation_if.h"
#include "FSM_context_if.h"
#include "FSM_transition_if.h"

#include <iostream>
#include <assert.h>
using namespace std;

namespace FSM_framework
{

  //-----------------------------------------------------------------------------
  void algorithm_deep::run(void)
  {
    if(get_fsm() != NULL)
      {
	get_fsm()->configure();
	FSM_interfaces::FSM_situation_if *l_previous_situation = NULL;
	FSM_interfaces::FSM_types::transition_index_t l_previous_transition = 0;

	bool l_continu = true;
	do
	  {
	    FSM_interfaces::FSM_situation_if * l_current_situation = & get_fsm()->get_current_situation();
	    std::cout << "Current situation :" << std::endl ;
	    get_fsm_ui()->display_situation(*l_current_situation) ;
	    std::cout << "-----" << std::endl ;
	      
	    // Check if situation was already encoutered
	    FSM_interfaces::FSM_situation_if * l_unique_situation = & m_situation_manager.get_unique_situation(*l_current_situation);
	    map<FSM_interfaces::FSM_situation_if *,situation_tree_node>::iterator l_node_iter = m_situation_tree.find(l_unique_situation);
	    if(l_node_iter == m_situation_tree.end())
	      {
		std::cout << "New situation ! (never encountered)" << std::endl ;
		cout << "Current situation : \"" << l_current_situation->get_string_id() << "\"" <<endl ; 

		if(l_current_situation->is_valid() && !l_current_situation->is_final())
		  {
		    cout << "Computing transitions" << endl ;
		    get_fsm()->compute_transitions();
		  }
	      
		// Store current situation with its predecessor relation if it exists
		if(l_previous_situation != NULL)
		  {
		    l_node_iter = m_situation_tree.insert(map<FSM_interfaces::FSM_situation_if *,situation_tree_node>::value_type(l_unique_situation,situation_tree_node(*l_current_situation,*l_previous_situation,l_previous_transition))).first;
		  }
		else
		  {
		    l_node_iter = m_situation_tree.insert(map<FSM_interfaces::FSM_situation_if *,situation_tree_node>::value_type(l_unique_situation,situation_tree_node(*l_current_situation))).first;
		  }
		cout << "Total of situation = " <<  m_situation_tree.size() << endl;
	      }
	    else if( l_current_situation != l_unique_situation)
	      {
		l_current_situation = l_unique_situation; 
		get_fsm()->set_current_situation(*l_unique_situation);
	      }
	 
	  
 
	    situation_tree_node & l_situation_tree_node = l_node_iter->second;
	    const set<FSM_interfaces::FSM_types::transition_index_t> & l_unexplored_transitions = l_situation_tree_node.get_unexplored_transitions();
			
	    cout << "Situation valid = " << l_current_situation->is_valid() << endl ;
	    cout << "Non explored transitions : " << l_unexplored_transitions.size() <<endl ;
	    set<FSM_interfaces::FSM_types::transition_index_t>::const_iterator l_iter = l_unexplored_transitions.begin();
	    set<FSM_interfaces::FSM_types::transition_index_t>::const_iterator l_iter_end = l_unexplored_transitions.end();
	    while(l_iter != l_iter_end)
	      {
		cout << *l_iter << " " ;
		++l_iter;
	      }
	    cout << endl ;
 
	    // Check if it can go deeply
	    if(l_unexplored_transitions.size() > 0 && !m_situation_stack.contains(*l_current_situation))
	      {
		// Store in stack
		m_situation_stack.push(*l_current_situation);

		// Store current situation to record the relationship of future situation
		l_previous_transition = *(l_unexplored_transitions.begin());
		l_previous_situation = l_current_situation;

		cout << "Select transition number : " << l_previous_transition << endl ;

		// Compute the next situation
		get_fsm()->select_transition(l_previous_transition);

		// Indicate that transition is explored
		l_situation_tree_node.set_transition_explored(l_previous_transition);
	      }
	    // No more transition available so we go back for one step if possible
	    else
	      {
		if(m_situation_stack.size())
		  {
		    FSM_interfaces::FSM_situation_if * l_previous_situation = & (m_situation_stack.pop());
		    std::cout << "restore previous situation" << std::endl ;

		    // Getting back to previous situation
		    assert(l_previous_situation);
		    get_fsm()->set_current_situation(*l_previous_situation);
		  }
		else
		  {
		    // We are at the original situation
		    l_continu = false ;
		  }
#if 0
		const map<FSM_interfaces::FSM_types::transition_index_t,FSM_interfaces::FSM_situation_if &> &l_predecessor_situations = l_situation_tree_node.get_predecessor_situations();
		// Check if there is a predecessor
		if(l_predecessor_situations.size())
		  {
		    l_previous_situation = NULL;

		    // Getting predecessor situation
		    map<const FSM_interfaces::FSM_situation_if *,situation_tree_node>::const_iterator l_previous_node_iter = 
		      m_situation_tree.find(&(l_predecessor_situations.begin()->second));

		    // Predecessor situation should be in situation tree !!!!
		    assert(l_previous_node_iter != m_situation_tree.end());

		    cout << "Restore previous situation " << l_previous_node_iter->second.get_situation() <<  endl ;
		    // Getting back to previous situation
		    get_fsm()->set_current_situation(l_previous_node_iter->second.get_situation());
		  }
		else
		  {		  
		    // We are at the original situation
		    l_continu = false ;
		  }
#endif
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
  const std::string & algorithm_deep::get_string(void)const
  {
    return m_class_name;
  }

  //-----------------------------------------------------------------------------
  void algorithm_deep::register_algorithm(map<string,FSM_framework_algorithm_creator_t> &p_factory)
  {
    register_framework_algorithm("algorithm_deep",create_algorithm_deep,p_factory);
  }

  //-----------------------------------------------------------------------------
  framework_algorithm_if & create_algorithm_deep(void)
  {
    return *(new algorithm_deep());
  }

#ifdef EXTERNAL_ALGORITHM
  //-----------------------------------------------------------------------------
  extern "C"
  {
    void register_algorithm(map<string,FSM_framework_algorithm_creator> &p_factory)
    {
      register_framework_algorithm("algorithm_deep",create_algorithm_deep,p_factory);
    }
  }
#endif

  const std::string algorithm_deep::m_class_name = "algorithm_deep";
}
//EOF
