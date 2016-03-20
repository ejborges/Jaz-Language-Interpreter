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

string filename;
string* file_lines;

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
    filename = argv[1];
    if(filename.length() < 5){
        cout << "Invalid argument '" << filename << "'";
        exit(1);
    }
    else if (filename[filename.length() - 4] != '.' &&
             filename[filename.length() - 3] != 'j' &&
             filename[filename.length() - 2] != 'a' &&
             filename[filename.length() - 1] != 'z')
    {
        cout << "File is not of type .jaz";
        exit(1);
    }

    // Open the .jaz file
    ifstream in_file(filename);
    if(in_file.fail()){
        cout << "Error opening file " << filename;
        exit(1);
    }

    // Get the number of lines in the file
    // http://stackoverflow.com/a/3072840
    int number_of_lines;
    number_of_lines = (int)count(istreambuf_iterator<char>(in_file), istreambuf_iterator<char>(), '\n');
    in_file.seekg(0, in_file.beg); // may need to return to beginning of file
    number_of_lines++; // just in case the last line didn't end with a newline '\n'
#ifdef DEBUG_TEXT
    cout << "Number of lines in file " << filename << " = " << number_of_lines << endl;
#endif

    // Initialize array
    file_lines = new string[number_of_lines];
    for(int i = 0; i < number_of_lines; i++) file_lines[i] = "";

    // Load .jaz file lines into array
    for(int i = 0; i < number_of_lines; i++){
        getline(in_file, file_lines[i]);
        if(in_file.fail() && !in_file.eof()){
            cout << "Error reading the file " << filename;
            exit(1);
        }
#ifdef DEBUG_TEXT
        cout << "file_lines[" << i << "] = " << file_lines[i] << endl;
#endif
    }

    in_file.close();
}