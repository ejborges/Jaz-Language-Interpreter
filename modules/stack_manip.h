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

#ifndef JAZ_INTERPRETER_STACK_MANIP_H
#define JAZ_INTERPRETER_STACK_MANIP_H
#include "working_data.h"

void push();
void push_value();
void push_address();
void pop();
void set_value();
void copy();

#endif //JAZ_INTERPRETER_STACK_MANIP_H
