#ifndef FRAMEWORK_CONTROLER_H
#define FRAMEWORK_CONTROLER_H

#include <string>

class framework_UI_if;
class framework_base;

class framework_controler
{
 public:
  framework_controler(framework_UI_if *p_framework_UI);
  ~framework_controler(void);
  void loadLibrary(std::string p_name);
  void selectFsm(std::string p_name);
  void selectFsmUi(std::string p_name);
  void selectAlgorithm(std::string p_name);
  void run(void);
  void displayWarningMessage(std::string p_message);
  void displayErrorMessage(std::string p_message);
  framework_base* getFramework(void);

 private:
  framework_UI_if *m_framework_ui;
  framework_base *m_framework;
};
#endif /* FRAMEWORK_CONTROLER_H */
