#ifndef JAZ_INTERPRETER_CONTROL_FLOW_H
#define JAZ_INTERPRETER_CONTROL_FLOW_H
#include <string>
void check_label(std::string label);
void goto_label(std::string target);
void go_false(std::string target);
void go_true(std::string target);
void halt();

#endif //JAZ_INTERPRETER_CONTROL_FLOW_H
