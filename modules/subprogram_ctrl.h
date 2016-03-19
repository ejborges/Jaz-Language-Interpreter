#ifndef JAZ_INTERPRETER_SUBPROGRAM_CTRL_H
#define JAZ_INTERPRETER_SUBPROGRAM_CTRL_H
#include <string>

void begin();
void end();
void returnFromCall();
void call(std::string label);

#endif //JAZ_INTERPRETER_SUBPROGRAM_CTRL_H
