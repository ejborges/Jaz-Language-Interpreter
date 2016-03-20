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
#include <algorithm> // count()
#include "jaz.h"

using namespace std;

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

    // Get the number of lines in the file
    // http://stackoverflow.com/a/3072840
    file_lines_length = (int)count(istreambuf_iterator<char>(in_file), istreambuf_iterator<char>(), '\n');
    in_file.seekg(0, in_file.beg); // may need to return to beginning of file
    file_lines_length++; // just in case the last line didn't end with a newline '\n'
#ifdef DEBUG_TEXT
    cout << "Number of lines in file " << file << " = " << file_lines_length << endl;
#endif

    // Initialize array
    file_lines = new string[file_lines_length];
    for(int i = 0; i < file_lines_length; i++) file_lines[i] = "";

    // Load .jaz file lines into array
    for(int i = 0; i < file_lines_length; i++){
        getline(in_file, file_lines[i]);
        if(in_file.fail() && !in_file.eof()){
            cout << "Error reading the file " << file;
            exit(1);
        }
#ifdef DEBUG_TEXT
        cout << "file_lines[" << i << "] = " << file_lines[i] << endl;
#endif
    }

    in_file.close();
}

string get_instruction(string code_line){
    string temp = "";
    for(int i = 0; i < code_line.length(); i++){
        if((code_line[i] == ' ' || code_line[i] == '\t') && temp.length() == 0) continue;
        if((code_line[i] == ' ' || code_line[i] == '\t' || code_line[i] == '\n') && temp.length() != 0) break;
        temp += code_line[i];
    }
    return temp;
}

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

void find_labels(){
    for(unsigned int i = 0; i < file_lines_length; i++){
        if(get_instruction(file_lines[i]).compare("label") == 0) {
            label.label_name = get_parameter(file_lines[i]);
            label.line_number = i;
            label_table.push_back(label);
        }
    }
#ifdef DEBUG_TEXT
    for(int i = 0; i < label_table.size(); i++)
        cout << "label '" << label_table[i].label_name << "' on line " << label_table[i].line_number << endl;
#endif
}

void read_line(){

}

void execute_instruction(){

}