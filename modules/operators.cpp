/* This is the operators instruction library for the Jaz language interpreter
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
 *          This library is in charge of defining what each of the
 *          arithmetic, logical, and relational operators do within
 *          the Jaz language.
 *
 *          Arithmetic Operators
 *
 *              add()
 *                  Pops the top two integers from the integer_stack,
 *                  adds them, and pushes the result to the integer_stack.
 *
 *              sub()
 *                  Pops the top two integers from the integer_stack,
 *                  subtracts the first int popped from the second int popped,
 *                  and pushes the result to the integer_stack.
 *                  stack_top = second_popped - first_popped
 *
 *              mul()
 *                  Pops the top two integers from the integer_stack,
 *                  multiplies them, and pushes the result to the integer_stack.
 *
 *              div()
 *                  Pops the top two integers from the integer_stack,
 *                  divides the second int popped by the first int popped,
 *                  and pushes the quotient to the integer_stack.
 *                  stack_top = second_popped / first_popped
 *
 *              mod()
 *                  Pops the top two integers from the integer_stack,
 *                  divides the second int popped by the first int popped,
 *                  and pushes the remainder to the integer_stack.
 *                  stack_top = second_popped % first_popped
 *
 *          Logical Operators
 *
 *              logic_and()
 *                  Pops the top two integers from the integer_stack,
 *                  logical AND them, and pushes the result to the integer_stack.
 *                  pushes 1 for true, 0 for false
 *
 *              logic_bang()
 *                  Pops the top integer from the integer_stack,
 *                  logical NOT it, and pushes the result to the integer_stack.
 *                  pushes 1 for true, 0 for false
 *
 *              logic_or()
 *                  Pops the top two integers from the integer_stack,
 *                  logical OR them, and pushes the result to the integer_stack.
 *                  pushes 1 for true, 0 for false
 *
 *          Relational Operators
 *
 *              not_equal()
 *                  Pops the top two integers from the integer_stack and pushes
 *                  a 1 to the integer_stack if the values are not equal or
 *                  pushes a 0 to the integer_stack if the values are equal.
 *
 *              less_than_or_equal()
 *                  Pops the top two integers from the integer_stack and pushes
 *                  a 1 to the integer_stack if the second int popped is less
 *                  than or equal to the first int popped, pushes a 0 otherwise.
 *
 *              greater_than_or_equal()
 *                  Pops the top two integers from the integer_stack and pushes
 *                  a 1 to the integer_stack if the second int popped is greater
 *                  than or equal to the first int popped, pushes a 0 otherwise.
 *
 *              less_than()
 *                  Pops the top two integers from the integer_stack and pushes
 *                  a 1 to the integer_stack if the second int popped is less
 *                  than to the first int popped, pushes a 0 otherwise.
 *
 *              greater_than()
 *                  Pops the top two integers from the integer_stack and pushes
 *                  a 1 to the integer_stack if the second int popped is greater
 *                  than to the first int popped, pushes a 0 otherwise.
 *
 *              equal()
 *                  Pops the top two integers from the integer_stack and pushes
 *                  a 1 to the integer_stack if the values are equal or pushes
 *                  a 0 to the integer_stack if the values are not equal.
 */

#include "operators.h"

int first_popped, second_popped;

void add()
{
	prepare_operators();

	integer_stack.push(second_popped + first_popped);
}
void sub()
{
	prepare_operators();

	integer_stack.push(second_popped - first_popped);
}
void mul()
{
	prepare_operators();

	integer_stack.push(second_popped * first_popped);
}
void div()
{
	prepare_operators();

	integer_stack.push(second_popped / first_popped);
}
void mod()
{
	prepare_operators();

	integer_stack.push(second_popped % first_popped);
}
void logic_and()
{
	prepare_operators();

	integer_stack.push((second_popped != 0 && first_popped != 0) ? 1 : 0);
}
void logic_bang()
{
	if (integer_stack.size() < 1)
	{
		error("not enough items on the integer_stack");
		return;
	}
	int popped_value = integer_stack.top();
	integer_stack.pop();

	integer_stack.push((popped_value == 0) ? 1 : 0);
}
void logic_or()
{
	prepare_operators();

	integer_stack.push((second_popped != 0 || first_popped != 0) ? 1 : 0);
}
void not_equal()
{
	prepare_operators();

	integer_stack.push((second_popped != first_popped) ? 1 : 0);
}
void less_than_or_equal()
{
	prepare_operators();

	integer_stack.push((second_popped <= first_popped) ? 1 : 0);
}
void greater_than_or_equal()
{
	prepare_operators();

	integer_stack.push((second_popped >= first_popped) ? 1 : 0);	
}
void less_than()
{
	prepare_operators();

	integer_stack.push((second_popped < first_popped) ? 1 : 0);
}
void greater_than()
{
	prepare_operators();

	integer_stack.push((second_popped > first_popped) ? 1 : 0);	
}
void equal()
{
	prepare_operators();

	integer_stack.push((second_popped == first_popped) ? 1 : 0);	
}

void prepare_operators()
{
	if (integer_stack.size() < 2)
	{
		error("not enough items on the integer_stack");
		return;
	}
	first_popped = integer_stack.top();
	integer_stack.pop();
	second_popped = integer_stack.top();
	integer_stack.pop();
}