//  Requirements:  Build a Command-Line Interface (CLI)
//  Behavior:
//
//   ./program  [-o <output filename>] [-l] [-u] [--] [--version] [-h]
//                  <input filename>
//
//  -u --upper		Uppercase all letters in document
//  -l --lower		Lowercase all letters in document
//  -o <output file>	Specify ouput file (default: output.txt)
//  -- -ignore_rest	Ignore rest of cmd
//  -h --help		Display usage
//  --version		Display version
//  <input file>	Input file is required and cannot be ignored
//  			by ignore_rest
//
//  This project abstracts the command-line parsing aspect of the
//  program, storing it in a std::map object.  Using maps and enums,
//  any argument name can be used with the OPTIONS_MAP to access the
//  value as a string, checking if the value is set and what the 
//  property is set to.  The --upper and --lower arguments are
//  mutually exclusive but neither is required to run the program.
//
//  Example:
//      >> OPTIONS_MAP[OUTFILE]
//      true
//  	>> OPTIONS_MAP[OUTFILE_NAME] 
//      output.txt
//
//  Author: Jimmy H Nguyen
//  Email:  jimmy@jimmyworks.net

#include <iostream>
#include <fstream>
#include <stdexcept>
#include "program.h"
using namespace std;

// Instance of global map, OPTIONS_MAP, which is populated
// during parsing and accessed using enum MapIndex keys to
// return string values.
std::map<int, std::string> OPTIONS_MAP;

// Function prototypes contained within this source file
void mutateDocument(ifstream*, ofstream*, int);
int processCommand();
bool strToBool(std::string);


// Main
// Simply runs parseCommandLine(...) and processCommand()
// handling upper level return codes.
// (input) int argc		argument count
// (input) char* argv[]		argument array
// (output) int			return code
// return 0			success
// return 1			parsing failure
// return 2			processing failure
int main(int argc, char** argv)
{
   if(!parseCommandLine(argc, argv)) //Parse the command line
   {
      if(!processCommand()) //Process commands
      {
         cout << "Done" << endl;
         return 0;
      }
      else
      {
         return 2;
      }
   }
   else
   {
      std::cout << "Failed to parse command!" << endl;
      return 1;
   }
}

// Mutate Document
// Function responsibile for taking references to an input and
// output file and, depending on the mode passed in, alters the
// document accordingly.
// (input) ifstream* ifile	reference open input file
// (input) ofstream* ofile	reference to open output file
// (input) int mode		operation (use enum MapIndex)
// (output)			none
void mutateDocument(ifstream* ifile, ofstream* ofile, int mode)
{
      // Create buffer to hold the lines from the input file
      // and function pointer, mutateChar, for the char operation
      std::string buffer;
      int (*mutateChar)(int);      

      // Check the mode and assign the corresponding pointer
      // to the function 
      if(mode == UPPER)
      {
         mutateChar = &toupper; //Use std::toupper(int)
      }
      else if(mode == LOWER)
      {
         mutateChar = &tolower; //Use std::tolower(int)
      }
      else
      {
         cerr << "Invalid mode received";
	 return;
      }

      // Loop through the document and modify characters 
      // along the way writing to the output file
      while(std::getline((*ifile), buffer))
      {
         char c;
	 int i = 0;
	 // For each index of the C string
	 while((buffer.c_str())[i])
	 {
	    c = buffer.c_str()[i];
            // Use the char in function assigned
	    *ofile << (char)mutateChar(c); // write to outfile
	    i++;
	 }
	 *ofile << endl; // After each line, enter a newline
      }
}

// Process Command
// Function responsible for executing all processing requirements
// for this program. TODO: Move portions of this code to other files
// and functions for readability and maintainability.
// (input) 		none
// (output) int		return code
// return 0		success
// return 1		failed to open input file
// return 2 		failed to open output file
// return 3		failed to mutate document
int processCommand()
{
   int status = 0; // return code
   ifstream infile;
   ofstream outfile;
   

   // Process input file
   if(strToBool(OPTIONS_MAP[INFILE]))
   {
      cout << "Opening input file: " << OPTIONS_MAP[INFILE_NAME] << endl;
      
      // Check if input file successfully opened
      infile.open(OPTIONS_MAP[INFILE_NAME].c_str());
      if(!infile)
      {
         cerr << "ERROR: Cannot find or open input file!!!" << endl;
	 return 1;
      }
      cout << "Successfully opened!" << endl;
   }
   else
   {
      throw logic_error("Internal error: Input file not specified.");
   }

   // Process output file
   cout << "Opening output file: " << OPTIONS_MAP[OUTFILE_NAME] << endl;
   outfile.open(OPTIONS_MAP[OUTFILE_NAME].c_str());
   // Check if output file successfully opened
   if(!outfile)
   {
      cerr << "ERROR: Cannot open output file!!!" << endl;
      return 2; 
   }

   cout << "Successfully opened!" << endl;
   
   // Document mutation block
   // Check if --upper or --lower arguments set and process accordingly
   try
   {
      if(strToBool(OPTIONS_MAP[UPPER])) // If --upper set...
      {
         cout << "Uppercasing entire document..." << endl;
        mutateDocument(&infile, &outfile, UPPER);
      }
      else if(strToBool(OPTIONS_MAP[LOWER])) // If --lower set...
      {
         cout << "Lowercasing entire document..." << endl;
         mutateDocument(&infile, &outfile, LOWER);
      }
      else // Else, do nothing
      {
         cout << "No changes to file made..." << endl;
      }
   }
   catch( std::exception ex){ // Notify if exceptions encountered
      cerr << "An exception was encountered in text mutation block." << endl;
      status = 3;
   }
 
   // Close all files and return the function status
   infile.close();
   outfile.close();
   return status;
}

// String to Boolean
// Converts strings to boolean values.  Throws invalid_argument
// exception for invalid strings.
// (input) string str	input string
// (output) bool	boolean interpreted
bool strToBool(std::string str)
{
   if(str.compare("true") == 0)
   {
      return true;
   }
   else if(str.compare("false") == 0)
   {
      return false;
   }
   else
   {
      throw std::invalid_argument( "Cannot cast string to boolean if string is not \"true\" or \"false\".");
   }
}

