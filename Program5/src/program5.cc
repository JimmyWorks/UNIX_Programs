// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
//
// Program Description:
// This program watches a directory and monitors for any file
// changes.  Upon a file modification, the old file is backed up
// to a hidden, .versions, directory within the watched directory.
// Files are backed up with the filename and the current timestamp
// appended.
//
// The program can be run in the terminal or in daemon-mode in the
// background.  The program has CLI-support which allows for the
// program to determine with configuration file to use and whether 
// or not to run in daemon-mode.
//
// The configuration file specifies which directory to monitor,
// the log filename, the max number of version files, and other
// settings.
//
// The program also accepts the following signals: SIGINT, SIGTERM,
// and SIGHUP.  SIGINT and SIGTERM will terminate the program with
// all files properly closed and the pid file, which is created when
// running in deamon-mode, to be deleted.  SIGHUP will reload the
// configuration file except for password and monitored directory.
// Note that SIGHUP can potentially change which log file the output
// will be written to mid-execution.
//
// Program Main Controller
// This source file contains the program main which calls the CLI
// parse methods, Config parse methods, and Monitoring routines.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <math.h>
#include <libgen.h>
#include <cstdlib>
#include <algorithm>
#include "program5/program5.h"
#include <rude/config.h>
using namespace std;

enum main_enums
{
   MATCH,
   CLI_FAILURE, 
   CONFIG_FAILURE, 
   LOG_FILE_FAILURE,
   FORK_FAILURE,
   DAEMON_RUN_ERROR
};

const char* pid_filename = "dirmond.pid";

void getExecPath(std::string &root_dir)
{
   char buffer[1024];
   size_t len = sizeof(buffer);
   char pathname[32];
   sprintf(pathname, "/proc/%d/exe", getpid());
   int bytes = std::min<size_t>(readlink(pathname, buffer, len), len - 1);
   if(bytes >= 0)
       buffer[bytes] = '\0';
   std::string str(dirname(dirname(buffer)));
   root_dir = str + "/";
}

bool existingFile(const char *path)
{
   if(FILE *file = fopen(path, "r"))
   {
      fclose(file);
      return true;
   }
   else
   {
      return false;
   }
}

int main(int argc, char* argv[])
{
   std::string root_dir;
   
   getExecPath(root_dir);
   cout << "Root is :" << root_dir << endl;
   globalMap[ROOT] = root_dir;
   try{
      parseCLI(argc, argv);
   }catch(exception &ex){
      cerr << "Error: Failed to parse command line." << endl;
      cerr << ex.what() << endl;
      return CLI_FAILURE;
   }

   cout << "daemon maps to: " << globalMap[DAEMON] << endl;
   cout << "config maps to: " << globalMap[CONFIG] << endl;

   try{
      parseConfig();
   }catch(exception &ex){
      cerr << "Error: Failed to parse config file." << endl;
      cerr << ex.what() << endl;
      return CONFIG_FAILURE;
   }

   cout << "verbose: " << globalMap[VERBOSE] << endl;
   cout << "logfile: " << globalMap[LOGFILE] << endl;
   cout << "password: " << globalMap[PASSWORD] << endl;
   cout << "numversions " << globalMap[NUMVERSIONS] << endl;
   cout << "watchdir: " << globalMap[WATCHDIR] << endl;

   int pid = -1;
   cout << "Current parent pid is: " << getpid() << endl;
   if(globalMap[DAEMON].compare("true") == MATCH)
   {
      pid = fork();
      
      if(pid == -1)
      {
         cerr << "Failed to fork" << endl;
	 return FORK_FAILURE;
      }
      else if(pid == 0)
      {
         //child
         cout << "I am born!  My pid is: " << getpid() << endl;
      }
      else
      {
         //parent
	 cout << "Child is " << pid << endl;
	 return 0;
      }
   }

   // Only main process or forked daemon exists at this point
   FILE *logger = fopen(globalMap[LOGFULLPATH].c_str(), "a");
   cout << "Log path: " << globalMap[LOGFULLPATH] << endl;
   fputs("Log file started...\n", logger);

   if(!logger)
   { 
      cerr << "Error: Failed to open log file." << endl;
      return LOG_FILE_FAILURE;
   }

   globalMap[PIDFILE] = "NULL";

   if(pid == 0)
   {
      std::string pid_fullpath = root_dir + "/" + pid_filename;
      globalMap[PIDFILE] = pid_fullpath;
      FILE *pidFile = NULL;
      if(!existingFile(pid_fullpath.c_str()))
      {
         
         pidFile = fopen(pid_fullpath.c_str(), "w");
         fprintf(pidFile, "%d\n", getpid());
         fclose(pidFile);
      }
      else
      {
	 fputs("Error encountered: pid file exists!  Daemon terminating...\n", logger);
	 fclose(logger);
	 return DAEMON_RUN_ERROR;
      }
      
   }
   
   // If daemon, log and pidFile exists
   // Else, if main process, log file exists and pidFile is NULL pointer
   fclose(logger);
   monitor(); 
   return 0;
}

