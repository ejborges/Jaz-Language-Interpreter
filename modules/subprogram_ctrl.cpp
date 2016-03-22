/* This is the subprogram control instruction library for the Jaz language interpreter
 *
 * ----------------------------------------------------------
 *
 *      Authors: Emilio Borges, Marcus Schmitz
 *      Developed: March 2016
 *
 *      The University of Toledo
 *      EECS 3550: Software Engineering
 *
 *      Project files can be found at:
 *      https://drive.google.com/open?id=0B4CF__kbczDjaEdoRkxqdkg5cXc
 *
 *      Project documentation can be found at:
 *      https://drive.google.com/open?id=0B4CF__kbczDjdWplcVJKTjYwbVczQVVFTkxhMDNzWUVpbGE0
 *
 *      Jaz language instructions can be found at:
 *      https://drive.google.com/open?id=0B4CF__kbczDjdjZ2aTFJTEJ6eUE
 *
 *      Textual Design Notation (TDN) document can be found at:
 *      https://drive.google.com/open?id=1Kn2HFw5_qydebZM2q2Mb6eNdbSVzJNHYhT4-36sdS2E
 *
 *
 *      HOW TO USE ------------------------------------------
 *
 *          Include this library's .h file in the interpreter's .h file.
 *          Then, call any of these functions within the interpreter's
 *          .cpp file while also passing it the appropriate parameters.
 *
 *      HOW IT WORKS ----------------------------------------
 *
 *
 */


#include "subprogram_ctrl.h"

using namespace std;

//Any variable declared in here will need a scope level
// 1 higher than the current scope level.
void begin()
{
    if(parameter.length() != 0) {
        warning("instruction begin does not take a parameter");
        return;
    }
	current_scope_level++;
#ifdef TRACE_CODE
    cout << "line " << program_line_number << ": begin; increased scope_level from "
    << current_scope_level-1 << " to " << current_scope_level << "\n";
#endif
}

//This will signal the end of a subroutine call.
void end()
{
    if(parameter.length() != 0) {
        warning("instruction end does not take a parameter");
        return;
    }
	if (current_scope_level > 0)
	{
		for (int i = 0; i < variable_table.size(); ++i)
		{
			if (variable_table[i].scope == current_scope_level)
			{
#ifdef TRACE_CODE
                cout << "line " << program_line_number << ": end; cleared variable "
                << variable_table[i].name << " at address " << i << " with value "
                << variable_table[i].value << " and scope " << variable_table[i].scope << "\n";
#endif
				variable_table[i].name.clear();
				variable_table[i].address = -1;
				variable_table[i].value = 0;
				variable_table[i].scope = -1;
                variable_table[i].coppied_from_address = -1;
			}
		}
		current_scope_level--;
#ifdef TRACE_CODE
        cout << "line " << program_line_number << ": end; decreased scope_level from "
        << current_scope_level+1 << " to " << current_scope_level << "\n";
#endif
	} 
	else error("can't end, too low of scope, current scope value = " + to_string(current_scope_level));
}

//This will decrement the current scope level so the program
// knows what variables it has access to.
void returnFromCall()
{
    if(parameter.length() != 0) {
        warning("instruction return does not take a parameter");
        return;
    }
	if (program_line_number_stack.empty())
	{
		error("empty program_line_number_stack; no clue where to return to");
		return;
	}

    // copy this
    for(int i = 0; i < variable_table.size(); i++){
        if((variable_table[i].coppied_from_address != -1) &&
                (variable_table[variable_table[i].coppied_from_address].scope == current_scope_level-1)){
#ifdef TRACE_CODE
            cout << "line " << program_line_number << ": return; copied variable "
            << variable_table[i].name << " with value " << variable_table[i].value << " and address "
            << variable_table[i].address << " and scope " << variable_table[i].scope << " to variable "
            << variable_table[variable_table[i].coppied_from_address].name << " with value "
            << variable_table[variable_table[i].coppied_from_address].value << " and address "
            << variable_table[variable_table[i].coppied_from_address].address << " and scope "
            << variable_table[variable_table[i].coppied_from_address].scope << "\n";
#endif
            variable_table[variable_table[i].coppied_from_address].value = variable_table[i].value;
//            variable_table[i].value = variable_table[variable_table[i].coppied_from_address].value;
#ifdef TRACE_CODE
//            cout << "HERE line " << program_line_number << ": return; copied variable ("
//            << variable_table[i].name << ", " << variable_table[i].value << ") to "
//            << "(" << variable_table[variable_table[i].coppied_from_address].name
//            << ", " << variable_table[variable_table[i].coppied_from_address].value
//            << ")" << "\n";
#endif
        }
    }

    // "delete" variables going out of scope
	for (int i = 0; i < variable_table.size(); ++i)
	{
		if (variable_table[i].scope == current_scope_level)
		{
#ifdef TRACE_CODE
            cout << "line " << program_line_number << ": return; cleared variable "
            << variable_table[i].name << " at address " << i << " with value "
            << variable_table[i].value << " and scope " << variable_table[i].scope << "\n";
#endif
			variable_table[i].name.clear();
			variable_table[i].address = -1;
			variable_table[i].value = 0;
			variable_table[i].scope = -1;
            variable_table[i].coppied_from_address = -1;
		}
	}
	if (current_scope_level > 0){
        current_scope_level--;
#ifdef TRACE_CODE
        cout << "line " << program_line_number << ": return; decreased scope_level from "
        << current_scope_level+1 << " to " << current_scope_level << "\n";
#endif
    }
	else error("can't returnFromCall, too low of scope, value = " + to_string(current_scope_level));

#ifdef TRACE_CODE
    cout << "line " << program_line_number
    << ": return; popped program_line_number_stack and set program_line_number to "
    << program_line_number_stack.top() << " from " << program_line_number << "\n";
#endif
    program_line_number = program_line_number_stack.top();
    program_line_number_stack.pop();

}

//We use the input label to jump to the subroutine specified
// by the label parameter and increment the current scope level.
void call()
{
    // copy this scope's vars into new scope with new address
    for(int i = 0; i < variable_table.size(); i++){
        if(variable_table[i].scope == current_scope_level){
            variable.name = variable_table[i].name;
            variable.address = new_variable_address_value++;
            variable.value = variable_table[i].value;
            variable.scope =  variable_table[i].scope+1;
            variable.coppied_from_address = i;
            variable_table.push_back(variable);
        }
    }

	current_scope_level++;
	program_line_number_stack.push(program_line_number);
#ifdef TRACE_CODE
    cout << "line " << program_line_number << ": call; increased scope_level from "
    << current_scope_level-1 << " to " << current_scope_level << " and pushed line number "
    << program_line_number << " to the program_line_number_stack\n";
#endif
	goto_label();
}