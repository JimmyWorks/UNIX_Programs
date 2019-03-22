//  Program Header
//  Author: Jimmy Nguyen
//  Email:  jimmy@jimmyworks.net

#ifndef _PROGRAM_H_
#define _PROGRAM_H_

#include <map>
#include <string>

// enum MapIndex
// Enum used as keys to aide in referencing the map 
// std::map <int, std::string> OPTIONS_MAP object.
// Names correspond to various properties set after
// collecting program arguments and map to strings
// of "true" or "false" except INFILE_NAME and 
// OUTFILE_NAME which map to filenames.
enum MapIndex
{
   INFILE, 
   INFILE_NAME, 
   OUTFILE, 
   OUTFILE_NAME, 
   UPPER, 
   LOWER, 
   HELP,
   VERSION,
   IGNORE_REST
};

// Global Map Declarations
// The following maps are used across source files.

// INDEX_MAP: Used to map TCLAP::ARG names (string) 
// to the corresponding enum key used for referencing
// the OPTIONS_MAP.  This allows for expandability
// in future argument additions to the set.
extern std::map<std::string, int> INDEX_MAP;

// OPTIONS_MAP: Used to map enum keys describing
// the property to be accessed to the value as
// parsed from the command line.  Keys are integer
// values as shown in enum MapIndex and are mapped
// to strings of "true" or "false" depending on if
// that argument was set.  Other values can be return
// in the string such as filenames.
extern std::map<int, std::string> OPTIONS_MAP;

// Function Prototypes
// The following functions are used across source files.

// parseCommandLine: Used by main() stored in program2.cc
// to call function stored in program2Parser.cc.  This
// function utilizes TCLAP to parse the command line
// and set up the OPTIONS_MAP.
int parseCommandLine(int, char**);

#endif
