/*
	Authors:	Emilio Borges
			    Marcus Schmitz
	Date:       March 2016
	Project:    Jaz Interpreter
	Class:      EECS 3550 Software Engineering
*/

#ifndef JAZ_INTERPRETER_JAZ_H
#define JAZ_INTERPRETER_JAZ_H

#define cout cout<<"\t"
#define DEBUG_TEXT

#include <string>
#include "modules/control_flow.h"
#include "modules/operators.h"
#include "modules/stack_manip.h"
#include "modules/subprogram_ctrl.h"

extern std::string filename;
extern std::string *file_lines;

void analyze_args(int argc, char* argv[]);
void read_file();

#endif //JAZ_INTERPRETER_JAZ_H
