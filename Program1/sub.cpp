// Program Main
// Author: Jimmy H. Nguyen
// Email: Jimmy@JimmyWorks.net

// Includes
#include <iostream>
#include "program.h"
using namespace std;

// Global Constants
char const* SUP_PREFIX = "SUPPORT: ";

// Custom Standard Out Routine
void MyStdOut(char const* string, char const* prefix)
{
   cout << prefix << string << "\n";
}

// Custom Standard Error Routine
void MyStdErr(char const* string, char const* prefix)
{
   cerr << prefix << string << "\n";
}

// Demonstrating Call from C++ File Outside Main File
int CallCC2()
{
   try
   {
      MyStdErr("Hi!  I am called from C++ file #2!!! :)", SUP_PREFIX);
      return 0;
   }
   catch(...)
   {
      return 1;
   }
}

