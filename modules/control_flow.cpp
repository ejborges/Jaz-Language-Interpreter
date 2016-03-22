/* This is the control flow instruction library for the Jaz language interpreter
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
 *          This library handles labeling certain sections of Jaz code and
 *          jumping to those labels. It also handles the termination or
 *          halting of the Jaz program. These functions perform basic
 *          control flow instructions that affect the Jaz code's order of
 *          execution.
 *
 *          check_label()
 *              Takes the global parameter variable as the label name and
 *              checks it and the current line number the execution cursor
 *              is at against what is already saved in the label_table.
 *
 *          goto_label()
 *              Takes the global parameter variable as the target label to
 *              jump to and moves the execution cursor to the line in the
 *              file where the label_table says the target label exists.
 *
 *          go_false()
 *              Takes the global parameter variable as the target label to
 *              jump to and moves the execution cursor to the line in the
 *              file where the label_table says the target label exists if
 *              the previous relational value returned false (aka the top
 *              value on the integer_stack is an integer with value zero).
 *
 *          go_true()
 *              Takes the global parameter variable as the target label to
 *              jump to and moves the execution cursor to the line in the
 *              file where the label_table says the target label exists if
 *              the previous relational value returned true(aka the top
 *              value on the integer_stack is an integer with value one).
 *
 *          halt()
 *              Defines the end of the Jaz program. It can be placed anywhere
 *              in the Jaz code and once executed will make the Jaz interpreter
 *              terminate as a result.
 */

#include "control_flow.h"

using namespace std;

void check_label()
{
	//do nothing
}

void goto_label()
{
    if(parameter.length() == 0) {
        error("no parameter specified; expected label name");
        return;
    }
	if (label_table.size() == 0)
	{
		error("no labels exist");
		return;	
	}
	
	for (int i = 0; i < label_table.size(); ++i)
	{
		if (parameter.compare(label_table[i].label_name) == 0) 
		{
#ifdef TRACE_CODE
            cout << "line " << program_line_number << ": goto " <<
                    parameter << " in line " << label_table[i].line_number << "\n";
#endif
			program_line_number = label_table[i].line_number;
			return;
		}
	}

    error("label " + parameter + " does not exist");
}

void go_false()
{
	if (integer_stack.size() == 0)
	{
		error("integer_stack is empty; no value to check");
		return;
	}
	if (integer_stack.top() == 0)
	{
		goto_label();
	}
    else{
#ifdef TRACE_CODE
        cout << "line " << program_line_number << ": gofalse did not jump; stack was "
        << integer_stack.top() << "\n";
#endif
    }
	integer_stack.pop();
}

void go_true()
{
	if (integer_stack.size() == 0)
	{
		error("no value on integer_stack to check");
		return;
	}
	if (integer_stack.top() == 1)
	{
		goto_label();
	}
    else{
#ifdef TRACE_CODE
        cout << "line " << program_line_number << ": gotrue did not jump; stack was "
        << integer_stack.top() << "; popped stack\n";
#endif
    }
	integer_stack.pop();
}

void halt()
{
    if(parameter.length() != 0) {
        error("instruction halt does not take a parameter");
        return;
    }
	continue_main_loop = false;
#ifdef TRACE_CODE
    cout << "line " << program_line_number << ": halt" << "\n";
#endif
}