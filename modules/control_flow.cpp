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
 *          check_label(string label)
 *              Takes in a string parameter as the label name and checks it
 *              and the current line number the execution cursor is at
 *              against what is already saved in the label_table.
 *
 *          goto_label(string target)
 *              Takes in a string parameter as the target label to jump to and
 *              moves the execution cursor to the line in the file where the
 *              label_table says the target label exists.
 *
 *          go_false(string target)
 *              Takes in a string parameter as the target label to jump to
 *              and moves the execution cursor to the line in the file where
 *              the label_table says the target label exists if the previous
 *              relational value returned false (aka the top value on the
 *              integer_stack is an integer with value zero).
 *
 *          go_true(string target)
 *              Takes in a string parameter as the target label to jump to
 *              and moves the execution cursor to the line in the file where
 *              the label_table says the target label exists if the previous
 *              relational value returned true(aka the top value on the
 *              integer_stack is an integer with value one).
 *
 *          halt(void)
 *              Defines the end of the Jaz program. It can be placed anywhere
 *              in the Jaz code and once executed will make the Jaz interpreter
 *              terminate as a result.
 */

#include "control_flow.h"

void check_label(std::string label)
{

}
void goto_label(std::string target)
{

}
void go_false(std::string target)
{

}
void go_true(std::string target)
{

}
void halt()
{

}