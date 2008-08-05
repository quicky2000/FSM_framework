#ifndef _FRAMEWORK_ALGORITHM_UI_IF_H_
#define _FRAMEWORK_ALGORITHM_UI_IF_H_

#include <string>
#include <map>
using namespace std;

class framework_algorithm_UI_if
{
	public:
		virtual string getType(void)=0;
};

typedef framework_algorithm_UI_if *(*FSM_framework_algorithm_UI_creator)(void);

void registerFrameworkAlgorithmUI(string p_algorithm_name,FSM_framework_algorithm_UI_creator p_creator,map<string,FSM_framework_algorithm_UI_creator> &p_factory);

#endif
