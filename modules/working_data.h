/* This is the data types library for the Jaz language interpreter
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
 *          Then, call any of these data types within the interpreter's
 *          .cpp file while also passing it the appropriate parameters.
 *
 *      HOW IT WORKS ----------------------------------------
 *
 *
 */

#ifndef JAZ_INTERPRETER_WORKING_DATA_H
#define JAZ_INTERPRETER_WORKING_DATA_H

#include <string>
#include <stack>
#include <vector>

extern std::string file;
extern std::string filename;
extern std::string *file_lines;
extern unsigned int file_lines_length;

extern std::string instruction;
extern std::string parameter;
extern unsigned int program_line_number;
extern unsigned int scope_level;
extern std::stack<int> program_line_number_stack;
extern std::stack<int> integer_stack;

struct variable_struct {
    std::string name;
    unsigned int address;
    int value;
    int scope_value;
};

struct label_struct {
    std::string label_name;
    unsigned int line_number;
};

extern std::vector<variable_struct> variable_table;
extern std::vector<label_struct> label_table;

#endif //JAZ_INTERPRETER_WORKING_DATA_H
