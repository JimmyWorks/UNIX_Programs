// Program 5: Program CLI Parser
// Author: Jimmy Nguyen
// Email: Jimmy@JimmyWorks.net
//
// Program CLI parse implementation
// This source file uses TCLAP libraries to implement program CLI.
// Custom classes were created to use the double-dispatch design
// pattern for a cleaner implementation of assigning options to 
// the enumerated global map.  Multiple inheritance is used with 
// custom classes inheriting from both the abstract base class
// created and TCLAP's classes provided.

#include <iostream>
#include "tclap/CmdLine.h"
#include <map>
#include <list>
#include "program5/program5.h"
#include "program5/ArgInterface.h"
#include "program5/CustomSwitchArg.h"
#include "program5/CustomUnlabeledValueArg.h"
using namespace std;

int parseCLI(int argc, char** argv)
{
  // Command Line Object
  TCLAP::CmdLine command("CS3377.502 Program 5\n   Jimmy Nguyen <Jimmy@JimmyWorks.net>", ' ', "1.0", true);

  // Argument Objects 
  CustomSwitchArg daemon("d", "daemon", "Run in daemon mode (forks to run as a daemon).", command, false, NULL);
  CustomUnlabeledValueArg config("config", "The name of the configuration file. Default is dirmond.conf", false, "dirmond.conf", "config filename", command, false, NULL);

  args.push_back(&daemon);
  args.push_back(&config);

  // Parsing the command
  command.parse(argc, argv);

  // Cycle through list assigning to the OPTIONS_MAP
  for( std::list<ArgInterface*>::iterator iter = args.begin(); iter != args.end(); iter++)
  {
     (*iter)->setProperties();
  }

  // Success
  return 0;
}

