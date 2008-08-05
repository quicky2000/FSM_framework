#ifndef _FRAMEWORK_CONTROLER_H_
#define _FRAMEWORK_CONTROLER_H_

#include <string>
using namespace std;

class framework_UI_if;
class framework_base;

class framework_controler
{
	public:
		framework_controler(framework_UI_if *p_framework_UI);
		void loadLibrary(string p_name);
		void selectFsm(string p_name);
		void selectFsmUi(string p_name);
		void selectAlgorithm(string p_name);
		void run(void);
		void displayWarningMessage(string p_message);
		void displayErrorMessage(string p_message);
		framework_base* getFramework(void);

	private:
		framework_UI_if *m_framework_ui;
		framework_base *m_framework;
};
#endif
