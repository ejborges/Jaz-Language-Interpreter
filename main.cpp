/*
	Authors:	Emilio Borges
			    Marcus Schmitz
	Date:       March 2016
	Project:    Jaz Interpreter
	Class:      EECS 3550 Software Engineering

	Project Description: TODO

	My Description: TODO
*/

#include <iostream>
#include <fstream>
#include <string>
//#include <algorithm> // count()

#define cout cout<<"\t"
#define DEBUG_TEXT

using namespace std;

int main(int argc, char* argv[]) {

    // Analyze arguments for correctness
    if(argc > 2){
        cout << "Too many arguments" << endl;
        cout << "Need: somefile.jaz" << endl;
        return 1;
    }
    else if(argc < 2){
        cout << "No arguments found" << endl;
        cout << "Need: somefile.jaz" << endl;
        return 1;
    }
    string filename = argv[1];
    if(filename.length() < 5){
        cout << "Invalid argument '" << filename << "'";
        return 1;
    }
    else if (filename[filename.length() - 4] != '.' &&
            filename[filename.length() - 3] != 'j' &&
            filename[filename.length() - 2] != 'a' &&
            filename[filename.length() - 1] != 'z')
    {
        cout << "File is not of type .jaz";
        return 1;
    }

    // Open the .jaz file
    ifstream in_file(filename);
    if(in_file.fail()){
        cout << "Error opening file " << filename;
        return 1;
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
    string *file_lines = new string[number_of_lines];
    for(int i = 0; i < number_of_lines; i++) file_lines[i] = "";

    // Load .jaz file lines into array
    for(int i = 0; i < number_of_lines; i++){
        getline(in_file, file_lines[i]);
        if(in_file.fail() && !in_file.eof()){
            cout << "Error reading the file " << filename;
            return 1;
        }
    #ifdef DEBUG_TEXT
      cout << "file_lines[" << i << "] = " << file_lines[i] << endl;
    #endif
    }



    delete [] file_lines;

    return 0;
}