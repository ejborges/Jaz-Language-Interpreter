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

#include "working_data.h"

using namespace std;

string file;
string filename;
string *file_lines;
unsigned int file_lines_length;

string instruction;
string parameter;
unsigned int program_line_number;
unsigned int scope_level;
stack<unsigned int> program_line_number_stack;
stack<int> integer_stack;

variable_struct variable;
label_struct label;

vector<variable_struct> variable_table;
vector<label_struct> label_table;