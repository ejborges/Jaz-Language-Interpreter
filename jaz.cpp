/* This is a language interpreter for the Jaz language
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
 *      HOW TO RUN ------------------------------------------
 *
 *          In the command line, after typing this executable's
 *          name, type the name of the .jaz file you wish to
 *          execute. This will run the code in the .jaz file
 *          and print the code's output to a .out file with the
 *          same name as the .jaz file.
 *
 *          Example of arguments: somefile.jaz
 *
 *      HOW IT WORKS ----------------------------------------
 *
 *          TODO
 *
 */

#include <iostream>
#include <fstream>
#include <algorithm> // count() in init()
#include "jaz.h"

using namespace std;

bool had_error = false;

// 1. Analyze arguments for correctness
// 2. Open .jaz file
// 3. Create or open the .out file and discard all previous contents
// 4. Get the number of lines in the file
// 5. Load .jaz file lines into file_lines vector
void init(int argc, char* argv[]){

    // Analyze arguments for correctness
    if(argc > 2){
        cout << "Too many arguments" << endl;
        cout << "Need: somefile.jaz" << endl;
        exit(1);
    }
    else if(argc < 2){
        cout << "No arguments found" << endl;
        cout << "Need: somefile.jaz" << endl;
        exit(1);
    }
    file = argv[1];
    if(file.length() < 5){
        cout << "Invalid argument '" << file << "'";
        exit(1);
    }
    else if (file[file.length() - 4] != '.' &&
             file[file.length() - 3] != 'j' &&
             file[file.length() - 2] != 'a' &&
             file[file.length() - 1] != 'z')
    {
        cout << "File is not of type .jaz";
        exit(1);
    }
    filename = file.substr(0, file.length() - 4);

    // Open the .jaz file
    ifstream in_file(file);
    if(in_file.fail()){
        cout << "Error opening file " << file;
        exit(1);
    }

    // Create or open the .out file and discard all previous contents
    out_file.open(filename + ".out", ofstream::trunc);
    if(out_file.fail()){
        cout << "Error opening file " << filename << ".out";
        exit(1);
    }

    // Get the number of lines in the file
    // http://stackoverflow.com/a/3072840
    file_lines_length = (unsigned int)count(istreambuf_iterator<char>(in_file), istreambuf_iterator<char>(), '\n');
    in_file.seekg(0, in_file.beg); // may need to return to beginning of file
    file_lines_length++; // just in case the last line didn't end with a newline '\n'
    #ifdef DEBUG_TEXT
    cout << "Number of lines in file " << file << " = " << file_lines_length << endl;
    #endif

    // Load .jaz file lines into file_lines vector
    string temp;
    for(int i = 0; i < file_lines_length; i++){
        getline(in_file, temp);
        file_lines.push_back(temp);
        if(in_file.fail() && !in_file.eof()){
            cout << "Error reading the file " << file;
            exit(1);
        }
    }

    in_file.close();

#ifdef DEBUG_TEXT
    for(int i = 0; i < file_lines_length; i++)
        cout << "file_lines[" << i << "] = " << file_lines[i] <<
        "\n\t\tinstruction = '" << get_instruction(file_lines[i]) << "'" <<
        "\n\t\t  parameter = '" << get_parameter(file_lines[i]) << "'" << endl;
#endif
}

// Given a line of Jaz code, return the instruction
string get_instruction(string code_line){
    string temp = "";
    for(int i = 0; i < code_line.length(); i++){
        if((code_line[i] == ' ' || code_line[i] == '\t') && temp.length() == 0) continue;
        if((code_line[i] == ' ' || code_line[i] == '\t' || code_line[i] == '\n') && temp.length() != 0) break;
        temp += code_line[i];
    }
    return temp;
}

// Given a line of Jaz code, return the parameter
string get_parameter(string code_line){
    string temp = "";
    bool gotInstruction = false;
    for(int i = 0; i < code_line.length(); i++){
        if(!gotInstruction)
        {
            if((code_line[i] == ' ' || code_line[i] == '\t') && temp.length() == 0) continue;
            if((code_line[i] == ' ' || code_line[i] == '\t' || code_line[i] == '\n') && temp.length() != 0) 
            {
                gotInstruction = true;    
                temp = "";
            }
            else temp += code_line[i];
        }
        else temp += code_line[i];
    }
    if (!gotInstruction)
    {
        return "";
    }
    return temp;
}

// Given a string, remove whitespace before first char and after last char
string remove_surrounding_whitespace(string s){
    int start = -1, end = 0;
    string temp = "";
    for(int i = 0; i < s.length(); ++i){
        if(s[i] == ' ' || s[i] == '\t') continue;
        else if(start == -1) start = end = i;
        else end = i;
    }
    for(int i = start; i < end+1; i++) temp += s[i];
    return temp;
}

// return true if given string contains whitespace
bool has_whitespace(std::string s){
    for(int i = 0; i < s.length(); i++){
        if(s[i] == ' ' || s[i] == '\t' || s[i] == '\n') return true;
    }
    return false;
}

// returns the variable_table index for the variable named if it exists in variable_table
// returns -1 otherwise
int search_variable_table(std::string name){
    if(variable_table.size() == 0) return -1;
    for(int i = 0; i < variable_table.size(); i++){
        if(variable_table[i].name.compare(name) == 0) return i;
    }
    return -1;
}

// returns true if the address exists in variable_table
bool exists_in_variable_table(int address){
    return (address >= 0 && address < variable_table.size());
}

// Scan through the entire .jaz file and note the name
// and line number of each label
void find_labels(){
    string label_name;
    for(unsigned int i = 0; i < file_lines_length; i++){
        if(get_instruction(file_lines[i]).compare("label") == 0) {

            label_name = remove_surrounding_whitespace(get_parameter(file_lines[i]));

            if(has_whitespace(label_name)){
                error("whitespace not allowed in label names; label '" + label_name + "'");
                return;
            }

            // check for duplicate labels
            if(!label_table.empty())
                for(int j = 0; j < label_table.size(); j++){
                    if(label_name.compare(label_table[j].label_name) == 0){
                        program_line_number = i;
                        error("duplicate label name '" + label_name + "' in " + file +
                                      " line " + to_string(label_table[j].line_number+1) + " and");
                        return;
                    }
                }

            label.label_name = label_name;
            label.line_number = i;
            label_table.push_back(label);
        }
    }
#ifdef DEBUG_TEXT
    for(int i = 0; i < label_table.size(); i++)
        cout << "label '" << label_table[i].label_name << "' on line " << label_table[i].line_number+1 << endl;
#endif
}

// Get the instruction and parameter from the current Jaz code line
void read_line(){
    if(program_line_number >= file_lines_length)
        error("program_line_number out of scope; must be between [0.." +
                      to_string(file_lines_length) + ") but is " + to_string(program_line_number) + ";");
    else {
        instruction = get_instruction(file_lines[program_line_number]);
        parameter = get_parameter(file_lines[program_line_number]);
    }
}

// Depending on the instruction, call the appropriate function
void execute_instruction(){

    // stack manipulation instructions
         if (instruction.compare("push") == 0){
             parameter = remove_surrounding_whitespace(parameter);
             push();
         }
    else if (instruction.compare("rvalue") == 0){
             parameter = remove_surrounding_whitespace(parameter);
             push_value();
         }
    else if (instruction.compare("lvalue") == 0){
             parameter = remove_surrounding_whitespace(parameter);
             push_address();
         }
    else if (instruction.compare("pop") == 0)       pop();
    else if (instruction.compare(":=") == 0)        set_value();
    else if (instruction.compare("copy") == 0)      copy();


    // control flow instructions
    else if (instruction.compare("label") == 0){
             parameter = remove_surrounding_whitespace(parameter);
             check_label();
         }
    else if (instruction.compare("goto") == 0){
             parameter = remove_surrounding_whitespace(parameter);
             goto_label();
         }
    else if (instruction.compare("gofalse") == 0){
             parameter = remove_surrounding_whitespace(parameter);
             go_false();
         }
    else if (instruction.compare("gotrue") == 0){
             parameter = remove_surrounding_whitespace(parameter);
             go_true();
         }
    else if (instruction.compare("halt") == 0)      halt();


    // arithmetic operator instructions
    else if (instruction.compare("+") == 0)         add();
    else if (instruction.compare("-") == 0)         sub();
    else if (instruction.compare("*") == 0)         mul();
    else if (instruction.compare("/") == 0)         div();
    else if (instruction.compare("div") == 0)       mod();


    // logical operator instructions
    else if (instruction.compare("&") == 0)         logic_and();
    else if (instruction.compare("!") == 0)         logic_bang();
    else if (instruction.compare("|") == 0)         logic_or();


    // relational operator instructions
    else if (instruction.compare("<>") == 0)        not_equal();
    else if (instruction.compare("<=") == 0)        less_than_or_equal();
    else if (instruction.compare(">=") == 0)        greater_than_or_equal();
    else if (instruction.compare("<") == 0)         less_than();
    else if (instruction.compare(">") == 0)         greater_than();
    else if (instruction.compare("=") == 0)         equal();


    // subprogram control instructions
    else if (instruction.compare("begin") == 0)     begin();
    else if (instruction.compare("end") == 0)       end();
    else if (instruction.compare("return") == 0)    returnFromCall();
    else if (instruction.compare("call") == 0){
             parameter = remove_surrounding_whitespace(parameter);
             call();
         }


    // output instructions
    else if (instruction.compare("print") == 0)     print();
    else if (instruction.compare("show") == 0)      show();

    else if (instruction.compare("") == 0)          ; // do nothing
    else {error("unknown instruction '" + instruction + "'"); return;}

    if(program_line_number < (file_lines_length - 1)) program_line_number++;
    else continue_main_loop = false;
}

// Print out an error message to the console and signal the main loop to quit
void error(string message){
    cout << "Error:\n\t\t" << message << " in " << file << " line " << program_line_number+1 << endl;
    continue_main_loop = false;
    had_error = true;
}

// Print out a warning message to the console
void warning(string message){
    cout << "Warning:\n\t\t" << message << " in " << file << " line " << program_line_number+1 << endl;
}

// Perform any cleanup before terminating the interpreter
void cleanup(){
    out_file.close();
    if(!had_error) cout << "\n\tJaz program ran successfully" << endl;
}