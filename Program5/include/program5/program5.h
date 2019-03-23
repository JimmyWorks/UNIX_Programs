// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
//
// Program 5 Primary Header file
// This header file must be included in all source files
// to have access to primary functions, global constants, and
// shared global variables in the enumerated map object: globalMap.

#include <map>
#include <list>
#include "tclap/CmdLine.h"
#include "ArgInterface.h"

#ifndef _PROGRAM_5_H_
#define _PROGRAM_5_H_

// CLI parse function
int parseCLI(int argc, char *argv[]);

// Config parse function
int parseConfig();

// Directory monitoring routine
int monitor();

// Update config function
extern int updateConfig();

// Enumerated keys to the map
enum MapKey
{
   ROOT,
   PIDFILE,
   CONFIG,
   DAEMON,
   VERBOSE,
   LOGFILE,
   LOGFULLPATH,
   PASSWORD,
   NUMVERSIONS,
   WATCHDIR,
   MAPKEY_COUNT
};

//// The remaining lists and maps are stored in
//// program5globals.cc

// Argument to Key map
extern std::map<std::string, int> ArgToKey;

// Global map values accessed with map key
extern std::map<int, std::string> globalMap;

// List of args used in CLI parser
extern std::list<ArgInterface*> args; 

#endif
