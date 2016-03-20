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

//#include <iostream>
#include "jaz.h"

using namespace std;


int main(int argc, char* argv[]) {

    // Initialization
    init(argc, argv);

    bool next_line = true;
    while(next_line){
        next_line = false;
    }

    delete [] file_lines;

    return 0;
}