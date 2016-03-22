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
	current_scope_level++;
}

//This will signal the end of a subroutine call.
void end()
{
	if (current_scope_level > 0)
	{
		for (int i = 0; i < variable_table.size(); ++i)
		{
			if (variable_table[i].scope == current_scope_level)
			{
				variable_table[i].name = "";
				variable_table[i].address = -1;
				variable_table[i].value = 0;
				variable_table[i].scope = -1;
			}
		}
		current_scope_level--;
	} 
	else error("can't end, too low of scope, value = " + to_string(current_scope_level));
}

//This will decrement the current scope level so the program
// knows what variables it has access to.
void returnFromCall()
{
	if (program_line_number_stack.empty())
	{
		error("empty program_line_number_stack, so no clue where to return to");
	}
	program_line_number = program_line_number_stack.top();
	program_line_number_stack.pop();

	for (int i = 0; i < variable_table.size(); ++i)
	{
		if (variable_table[i].scope == current_scope_level)
		{
			variable_table[i].name = "";
			variable_table[i].address = -1;
			variable_table[i].value = 0;
			variable_table[i].scope = -1;
		}
	}
	if (current_scope_level > 0) current_scope_level--;
	else error("can't returnFromCall, too low of scope, value = " + to_string(current_scope_level));

}

//We use the input label to jump to the subroutine specified
// by the label parameter and increment the current scope level.
void call()
{
	current_scope_level++;
	program_line_number_stack.push(program_line_number);
	goto_label();
}