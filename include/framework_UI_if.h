#ifndef _FRAMEWORK_UI_IF_
#define _FRAMEWORK_UI_IF_

#include <vector>
using namespace std;

class framework_UI_if
{
	public:
		virtual void displayLoadedFsm(vector<string> *p_FSM_list)=0;
		virtual void displayLoadedFsmUi(vector<string> *p_FSM_UI_list)=0;
		virtual void displayLoadedAlgorithm(vector<string> *p_algorithm_list)=0;
		virtual void displayWarningMessage(string p_message)=0;
		virtual void displayErrorMessage(string p_message)=0;
};
#endif
