// Program Main
// Author: Jimmy H. Nguyen
// Email: Jimmy@JimmyWorks.net

// Includes
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include "program.h"
using namespace std;

// Main routine
// @param argc -- number of arguments passed
// @param argv -- array of strings passed into function
// @return an integer return code
int main(int argc, char* argv[])
{
   // Identifier to show program main is caller
   const char* PREFIX = "MAIN: ";
   char string[50]; // String buffer

   // Show the caller program name and number of arguments passed
   sprintf(string, "Program: %s", argv[0]);
   MyStdOut(string, PREFIX);
   sprintf(string, "Arguments Passed (argc): %d", argc);
   MyStdOut(string, PREFIX);

   // Print each of the arguments passed in
   for(int i = 0; i < argc; i++)
   {
      sprintf(string, "Argument %d: %s", (i+1), argv[i]);
      MyStdOut(string, PREFIX);
   }
   
   // Call the function from the supporting C++ File
   try
   {
      int stat = CallCC2();
      
      if(stat == 0)
         MyStdOut("Sub-program executed properly.", PREFIX);
      else
         MyStdOut("Sub-program had an issue.", PREFIX);

   }
   catch(...)
   {
      MyStdErr("Failed to call subprocess in second program");
      return 1;
   }

   MyStdOut("Done!", PREFIX);

   // Success
   return 0;
}

