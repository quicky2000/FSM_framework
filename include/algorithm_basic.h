#ifndef _ALGORITHM_BASIC_
#define _ALGORITHM_BASIC_

#include "framework_algorithm_if.h"

class algorithm_basic: public framework_algorithm_if
{
	public:
		// Methods inherited from interface
		void run(void);
		string getString(void);
	
		static void registerAlgorithm(map<string,FSM_framework_algorithm_creator > &p_factory);
};

framework_algorithm_if* createAlgorithmBasic(void);

#endif
