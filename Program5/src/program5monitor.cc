// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
//
// Program Directory Monitoring Functions
// This source file contains the functions which support monitoring
// the watch directory, making file backups, and termination.
 

#include "program5/program5.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <sys/inotify.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/unistd.h>
#include <chrono>
#include <ctime>
#include <signal.h>

using namespace std;

const std::string version_folder = ".versions";
const size_t SIZE = sizeof(struct inotify_event) + PATH_MAX + 1;
int process;
FILE *logger;

enum monitor_enums
{
   MATCH,
   MAIN,
   FORK
};

void debug(const char *message)
{
   if(process == MAIN)
   {
      cout << message << endl;
   }
   else
   {
      logger = fopen(globalMap[LOGFULLPATH].c_str(), "a");
      fprintf(logger, "%s\n", message);
      fclose(logger);
   }
}

void cleanup()
{
  if(process == FORK)
  {
     try{
        FILE* pidfile = fopen(globalMap[PIDFILE].c_str(), "r");
        fclose(pidfile);
        std::remove(globalMap[PIDFILE].c_str());
     }catch(exception ex){
        std::string exMsg = ex.what();
        std::string str = "Failed to remove pid file\n" + exMsg;
        debug(str.c_str());
     }
  }
  debug("Ending process...");
}

void signalHandler(int signum)
{
   switch(signum){
      case SIGINT:  debug("Got SIGINT"); 
      case SIGTERM: debug("Got SIGTERM");
                    cleanup();
		    exit(0);
                    break;
      case SIGHUP:  debug("Got SIGHUP");
                    debug("Updating configurations\n Log file may change...");
		    if(!updateConfig())
		    {
		       debug("Updated the config file!");
		       std::string changes = 
		          "Number of versions: " + globalMap[NUMVERSIONS] +
		          "\nVerbose: " + globalMap[VERBOSE] +
		          "\nLogfile: " + globalMap[LOGFILE];
		       debug(changes.c_str());

		    }
		    else
		    {
		       debug("Failed to update config file...");
		    }
      default:      break;
   }
}

int monitor()
{
  struct stat info;
  process = MAIN;

  signal(SIGHUP, signalHandler);
  signal(SIGTERM, signalHandler);
  signal(SIGINT, signalHandler);


  if(globalMap[PIDFILE].compare("NULL") == MATCH)
  {
     cout << "Main running..." << endl;
  }
  else
  {
     cout << globalMap[PIDFILE] << endl;
     process = FORK;
     debug("Daemon running!");
  }

  std::string watch_dir = globalMap[WATCHDIR];
  std::string version_path = watch_dir + "/" + version_folder;

  // Check if .versions folder exists in watch directory.  If not, create it.
  if(stat(version_path.c_str(), &info) != -1 && info.st_mode && S_IFDIR)
     debug("directory exists");
  else
  {
     debug("directory does not exist");
     if(mkdir(version_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH))
        debug("Failed creating directory");
     else
        debug("Created it!");

  }


  int fileDesc = inotify_init();
  if( fileDesc < 0)
  {
     debug("Error while creating inotify\n");
  }

  std::string check = "version path: " + version_path + "file description num: " + to_string(fileDesc);
  debug(check.c_str());
  // Watch the directory
  int watchID = inotify_add_watch(fileDesc, watch_dir.c_str(), IN_MODIFY | IN_ATTRIB );

  if(watchID == -1)
  {
     debug("Failed to watch the directory in inotify_add_watch call");
     
  }
  char buff[SIZE];
  char strbuff[64];
  while(1)
  {
     int len = read(fileDesc, buff, SIZE);


     if(len < 0)
     {
        debug("error in event reading");
	break;
     }

    int i = 0;
    while(i < len)
    {
     struct inotify_event *event = (struct inotify_event*) &buff[i];
     sprintf(strbuff, "pid %d observed a change to watched directory", getpid());
     debug(strbuff);

     if(event->mask & IN_MODIFY)
     {
     sprintf(strbuff, "pid %d observed a modification to %s", getpid(), event->name);
     debug(strbuff);

     auto now = std::chrono::system_clock::now();
     time_t tt = std::chrono::system_clock::to_time_t(now);
     tm local_tm = *localtime(&tt);
     std::string year = to_string(local_tm.tm_year + 1900);
     std::string month = to_string(local_tm.tm_mon + 1);
     std::string day = to_string(local_tm.tm_mday);
     std::string hour = to_string(local_tm.tm_hour);
     std::string min = to_string(local_tm.tm_min);
     std::string sec = to_string(local_tm.tm_sec);
     std::string timestamp = year + "." + month + "." + day + "-" + hour + ":" + min + ":" + sec;
     std::string src_filename = watch_dir + "/" + event->name; 
     std::string dst_filename = version_path + "/" + event->name + timestamp; 
     std::ifstream src(src_filename, std::ios::binary);
     std::ofstream dst(dst_filename, std::ios::binary);
     dst << src.rdbuf();
        
     }
     if(event->mask & IN_ATTRIB)
     {
     sprintf(strbuff, "pid %d observed an attribute change", getpid());
     debug(strbuff);
       
     }
     i += SIZE+event->len;
    }
  }

  return 0;
}
