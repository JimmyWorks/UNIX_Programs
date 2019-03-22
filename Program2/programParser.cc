//  Program Parser
//
//  This portion of the CLI handles all the parsing and sets up the map
//  OPTIONS_MAP for accessing values passed in.
//
//  Behavior:
//
//   ./program  [-o <output filename>] [-l] [-u] [--] [--version] [-h]
//                  <input filename>
//
//  -u --upper          Uppercase all letters in document
//  -l --lower          Lowercase all letters in document
//  -o <output file>    Specify ouput file (default: output.txt)
//  -- -ignore_rest     Ignore rest of cmd
//  -h --help           Display usage
//  --version           Display version
//  <input file>        Input file is required and cannot be ignored
//                      by ignore_rest
//
//  For more information, see program.cc
//
//  Author: Jimmy H Nguyen
//  Email:  jimmy@jimmyworks.net

#include <iostream>
#include "tclap/CmdLine.h"
#include "program.h"
using namespace std;

// Initialization of INDEX_MAP which is used below in parseCommandLine(...).
// If arguments are added to this CLI, the respective lookup must be
// added below to be added to the OPTIONS_MAP.  If access is required via
// enum, the lookup must be added to enum MapIndex in the program2.h header.
// Using the name of the TCLAP::ARG, this maps the string to the respective
// enum that will be used to access that property.
std::map<std::string, int> INDEX_MAP = 
  {
     {"upper", UPPER},
     {"lower", LOWER},
     {"infile", INFILE},
     {"outfile", OUTFILE},
     {"help", HELP},
     {"ignore_rest", IGNORE_REST},
     {"version", VERSION},
     {"infile_name", INFILE_NAME},
     {"outfile_name", OUTFILE_NAME}
  };

// Parse Command Line
// This method takes the command line input and parses the line.  A valid input
// is then stored to a map, OPTIONS_MAP, which can be accessed using corresponding
// enum keys to get the string value.
// (input) int argc	argument count
// (input) char* argv	array of arguments
// (output) int		return code
// return 0		success
// return 1		mutual exclusion error
// return 2		input file unset (internal error)
int parseCommandLine(int argc, char** argv)
{
  // Command Line Object
  TCLAP::CmdLine command("CLI Program \n   Jimmy Nguyen <Jimmy@JimmyWorks.net>", ' ', "1.0", true);

  // Argument Objects 
  TCLAP::SwitchArg upper("u", "upper", "Convert all text to uppercase.", command, false);
  TCLAP::SwitchArg lower("l", "lower", "Convert all text to lowercase.", command, false);
  TCLAP::UnlabeledValueArg<std::string> infile("infile", "The name of the input file.", true, "infile.txt", "input filename", command, false);
  TCLAP::ValueArg<std::string> outfile("o", "outfile", "The name of the output file.", false, "output.txt", "output filename", command);

  // Parsing the command
  command.parse(argc, argv);

  // Checking for mutual exclusion
  if(upper.isSet() && lower.isSet())
  {
     cerr << "Error: Cannot set both -u and -l flags" << endl;
     cerr << "Flags are mutually exclusive" << endl;
     command.getOutput()->usage(command);
     return 1;
  }

  // Get the argument object list
  std::list<TCLAP::Arg*> argList = command.getArgList();

  // Cycle through list assigning to the OPTIONS_MAP
  for( std::list<TCLAP::Arg*>::iterator iter = argList.begin(); iter != argList.end(); iter++)
  {
     TCLAP::Arg* argPtr = (*iter);
     std::string name = argPtr -> getName();
     int index = INDEX_MAP[name];

     if(argPtr -> isSet())
     {
         OPTIONS_MAP[index] = "true";   
     }
     else
     {
        OPTIONS_MAP[index] = "false";
     }
  }

  // Default input and output filenames if undefined
  // Because input file is required by UnlabeledValueArg infile,
  // input filename should never be undefined.
  OPTIONS_MAP[INFILE_NAME] = "input.txt";
  OPTIONS_MAP[OUTFILE_NAME] = "output.txt";

  // Verify that input file argument is set and set the input filename
  if(infile.isSet())
  {
     OPTIONS_MAP[INFILE_NAME] = infile.getValue();
  }
  else
  {
     cerr << "Internal error: input file arg not set";
     return 2;
  }

  // Check if the output file is set.  If so, set the output filename
  if(outfile.isSet())
  {
     OPTIONS_MAP[OUTFILE_NAME] = outfile.getValue();
  }

  // Success
  return 0;
}

