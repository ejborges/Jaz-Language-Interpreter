#ifndef JAZ_INTERPRETER_SUBPROGRAM_CTRL_H
#define JAZ_INTERPRETER_SUBPROGRAM_CTRL_H

class subprogram_ctrl{
public:
void begin();
void end();
void returnFromCall();
void call(string label);

private:

};

#endif //JAZ_INTERPRETER_SUBPROGRAM_CTRL_H
