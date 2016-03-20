/*
	Authors:	Emilio Borges
			    Marcus Schmitz
	Date:       March 2016
	Project:    Jaz Interpreter
	Class:      EECS 3550 Software Engineering
*/

//#include <iostream>
#include "jaz.h"

using namespace std;


int main(int argc, char* argv[]) {

    // Initialization
    analyze_args(argc, argv);
    read_file();

    bool next_line = true;
    while(next_line){
        next_line = false;
    }

    delete [] file_lines;

    return 0;
}