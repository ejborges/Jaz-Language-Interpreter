#ifndef JAZ_INTERPRETER_CONTROL_FLOW_H
#define JAZ_INTERPRETER_CONTROL_FLOW_H

class control_flow{
public:
void check_label(string label);
void goto_label(string target);
void go_false(string target);
void go_true(string target);
void halt();

private:

};

#endif //JAZ_INTERPRETER_CONTROL_FLOW_H
