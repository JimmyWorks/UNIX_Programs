// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
// 
// Program Globals
// This source file is the location where program globals are
// declared and maintained.

#include <map>
#include <string>
#include "program5/ArgInterface.h"
#include "program5/program5.h"

std::map<int, std::string> globalMap;

std::list<ArgInterface*> args; 

std::map<std::string, int> ArgToKey =
{
   {"daemon", DAEMON},
   {"config", CONFIG},
   {"Verbose", VERBOSE},
   {"LogFile", LOGFILE},
   {"Password", PASSWORD},
   {"NumVersions", NUMVERSIONS},
   {"WatchDir", WATCHDIR}
};


