/* This is the output instruction library for the Jaz language interpreter
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

#include <fstream>
#include <iostream>
#include "output.h"

using namespace std;

ofstream out_file;

void print(){
	if (parameter.empty())
	{
		if (integer_stack.empty())
		{
			error("nothing to print, empty integer_stack");
			return;
		}
		out_file << integer_stack.top() << endl;
	}
	else if (search_variable_table(parameter) == -1)
	{
		out_file << "0" << endl;
	}
	else
	{
		out_file << variable_table[search_variable_table(parameter)].value << endl;
	}
}

void show(){
    out_file << parameter << endl;
}