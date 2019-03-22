// C++ Controller Code
// Author: Jimmy Nguyen
// Email:  jimmy@jimmyworks.net
//
// Program Description:
// Demonstrate the use of C++ program to call an external process
// and process the console output.  This program calls an installed
// older version of gawk to process code in "gawk.code" file using 
// input from "numbers.txt".  The result is printed to the screen
// and to a file.  A Makefile was also create to demonstrate how
// Makefiles can be used to efficiently build the project.

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

// Size of character array buffer for processing subprocess call
#define BUFFER_SIZE 256

// Global string constants
// As per requirements, the fullpath to the gawk program 
// was hardcoded into the program.  
//TODO: Please change 'GAWK' below to match the location of executable: gawk ver 1.3.8. 
const std::string GAWK = "/usr/bin/gawk ";
const std::string VERSION = "--version ";
const std::string FILEOPT = "-f ";
const std::string GAWKCODE = "gawk.code ";
const std::string INFILE = "numbers.txt ";
const char* OUTFILE_HEADER = 
"Program Output\n\ 
Author: Jimmy Nguyen\n\ 
Email:  jimmy@jimmyworks.net\n";

// Function prototypes
// Reads output to console and output file
// If no output file defined, simply outputs to console
// If checkSum not defined, function simply prints without processing.
void readOutput(FILE*, FILE* outfile=NULL, bool checkSum=false);

// Main
// Calls a gawk subprocess to run the following commands:
//    gawk --version
//    gawk -f gawk.code numbers.txt
// Output from both calls are printed to the screen and
// saved to output file: output.txt.
// (input) int argc	main argument count
// (input) char* argv[]	main argument array
// (output) int		return code
// return code 0	success
// return code 1	failed first subprocess call
// return code 2	failed second subprocess call
int main(int argc, char* argv[])
{
   // Create output file and string for subprocess call
   std::string cmd = GAWK + " " +  VERSION;
   FILE* outfile;
   outfile = fopen("output.txt", "w"); // output file
   
   // Print Header to output file
   fprintf(outfile, OUTFILE_HEADER);

   // Execute subprocess call and store output to file
   FILE* buffer = popen(cmd.c_str(), "r");
   // Check if output exists; exit program if it does not exist
   if(!buffer)
   {
      cerr << "Failed to run command: " << cmd << endl;
      return 1;
   }

   cout << endl << "The first call to gawk returned: " << endl << endl;
   fprintf(outfile, "\nThe first call to gawk returned:\n\n");

   // Read the output and write it to the output file.  Then, close the process.
   readOutput(buffer, outfile);
   pclose(buffer);

   // Create next subprocess call and execute the call
   cmd = GAWK + " " + FILEOPT + " " + GAWKCODE + " " + INFILE; 
   buffer = popen(cmd.c_str(), "r");
   // Check if output exists; exit program if it does not exist
   if(!buffer)
   {
      cerr << "Failed to run command: " << cmd << endl;
      return 2;
   }

   cout << endl << "The second call to gawk returned: " << endl << endl;
   fprintf(outfile, "\nThe second call to gawk returned:\n\n");

   // Read the output and write it to the output file.
   readOutput(buffer, outfile, true);

   // Close all process and data streams
   pclose(buffer);
   fclose(outfile);

   // Success
   return 0;
}

// Read Output
// Takes a temporary buffer file into the output file and prints
// the result to the console. If in sum mode, will take two
// output values and sum them together.
// (input) FILE* output		temporary buffer file
// (input) FILE* outfile	output file
// (input) bool checkSum	run in sum mode
void readOutput(FILE* output, FILE* outfile, bool checkSum)
{
   char line[BUFFER_SIZE];

   // Check if in sum mode
   // If not, print output to console and file.
   if(!checkSum)
   {
      while (fgets(line, BUFFER_SIZE, output)) 		// if not end of file
      {
         printf(line); 		// print it to the console
         if(outfile) 		// if outfile defined
            fprintf(outfile, line); 	// save it to the outfile
        	// get next character
      }
   }
   else // If in sum mode, print values of columns and sum.
   {
      // Initial values
      int total1 = 0; // Column 1 total
      int total4 = 0; // Column 2 total
      stringstream str; // build string stream for output

      try
      {
         // Get column 1 total
         fgets(line, BUFFER_SIZE, output); // get line
         total1 = atoi(line); // convert char* to int
	 str << "The sum of column 1 is: " << total1 << endl;

         // Get column 2 total
	 fgets(line, BUFFER_SIZE, output); // get line
	 total4 = atoi(line); // convert char* to int
	 str << "The sum of column 4 is: " << total4 << endl;

         // Sum them together
         str << "The sum of both is: " << total1 + total4 << endl << endl;
      }
      catch(...)
      {
         cout << "An error occurred when parsing gawk values" << endl;
         exit(EXIT_FAILURE);
      } 
      fprintf(outfile, str.str().c_str()); // print output string to file
      cout << str.str(); // print output string to console
   }
}
