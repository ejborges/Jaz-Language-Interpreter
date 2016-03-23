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
#include <iostream>

#define cout cout<<"\t"
//#define DEBUG_TEXT
//#define TRACE_CODE

extern std::string file;
extern std::string filename;
extern std::vector<std::string> file_lines;
extern unsigned int file_lines_length;

extern bool continue_main_loop;
extern bool inside_begin_block;
extern std::string instruction;
extern std::string parameter;
extern unsigned int program_line_number;
extern unsigned int current_scope_level;
extern unsigned int new_variable_address_value;
extern std::stack<unsigned int> program_line_number_stack;
extern std::stack<int> integer_stack;

struct variable_struct {
    std::string name;
    int address;
    int value;
    int scope;
    int original_scope;
    bool dont_delete;
} extern variable;

struct label_struct {
    std::string label_name;
    unsigned int line_number;
} extern label;

extern std::vector<variable_struct> variable_table;
extern std::vector<label_struct> label_table;

extern void error(std::string message);
extern void warning(std::string message);
extern bool has_whitespace(std::string s);
extern int search_variable_table(std::string var_name);
extern bool exists_in_variable_table(int address);

#endif //JAZ_INTERPRETER_WORKING_DATA_H
