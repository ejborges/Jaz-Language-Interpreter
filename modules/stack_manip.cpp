/* This is the stack manipulation instruction library for the Jaz language interpreter
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
 *          This library is composed of all stack manipulation instructions.
 *          It handles pushing values and addresses onto the stack, setting
 *          and popping items that are currently on the stack, duplicate what
 *          is currently on the top of the stack and push a copy of the top value.
 *
 *          push()
 *              Takes the global parameter variable as an integer value and pushes
 *              it onto the integer_stack.
 *
 *          push_value()
 *              Takes the global parameter variable as a variable name, looks up its
 *              integer value in the variable_table, and pushes the value onto the
 *              integer_stack.
 *
 *          push_address()
 *              Takes the global parameter variable as a variable name, looks up its
 *              address in the variable_table, and pushes the value onto the integer_stack.
 *
 *          pop()
 *              Removes the top value of the stack and throws it away without being
 *              used.
 *
 *          set_value()
 *              Pops the top two values from the integer_stack (the first value popped
 *              should should be an integer value and the second value popped should
 *              be an address) and, using the variable_table, places the value from the
 *              first popped into the address of the second popped.
 *
 *          copy()
 *              Copies the top of the integer_stack and pushes it resulting in the top two
 *              values of the stack being equal.
 */

#include <iostream>
#include "stack_manip.h"

 using namespace std;

// push instruction
void push()
{
    // check parameter for correctness
    // parameter must have length of 1 or more,
    // only have numerical characters and the '-' char at beginning
    // not exceed the +- value range of signed int type
    if(parameter.length() == 0){
        error("no parameter to push to integer_stack");
        return;
    }
    if(parameter.length() == 1 && (parameter[0] < '0' || parameter[0] > '9')){
        error("invalid parameter '" + parameter + "' to push to integer_stack");
        return;
    }
    for(int i = 0; i < parameter.length(); i++){
        if(i == 0 && parameter[0] != '-' && (parameter[0] < '0' || parameter[0] > '9')){
            error("invalid parameter '" + parameter + "' to push to integer_stack");
            return;
        }
        if(i != 0 && (parameter[i] < '0' || parameter[i] > '9')){
            error("invalid parameter '" + parameter + "' to push to integer_stack");
            return;
        }
    }
    int value_to_push;
    try{
        value_to_push = stoi(parameter);
    }
    catch(...){
        error("parameter value '" + parameter + "' out of integer range");
        return;
    }

    integer_stack.push(value_to_push);

//    cout << "\tpushed " << value_to_push << " to integer_stack from .jaz line" << program_line_number+1 << endl;
}

// rvalue instruction
void push_value()
{

}

// lvalue instruction
void push_address()
{
    if(variable_table.empty()){
        variable.address = ++new_variable_address_value;
    }
}

// pop instruction
void pop()
{
	if (integer_stack.empty())
	{
        error("popped empty integer_stack");
		return;
	}
	integer_stack.pop();
}

// := instruction
void set_value()
{
    if (integer_stack.size() < 2)
    {
        error("not enough elements in the stack to execute instruction");
        return;
    }

    int value = integer_stack.top();
    integer_stack.pop();
    int address = integer_stack.top();
    integer_stack.pop();
    if (!exists_in_variable_table(address))
    {
        error("address " + to_string(address) + " does not exist");
        return;
    }

    if (!((variable_table[address].scope + 1) == current_scope_level || variable_table[address].scope == current_scope_level))
    {
        error("variable " + variable.name + " out of scope");
        return;
    }
    variable_table[address].value = value;
}

// copy instruction
void copy()
{
	if (integer_stack.empty())
    {
        error("nothing in the stack to copy");
        return;
    }
    integer_stack.push(integer_stack.top());
}