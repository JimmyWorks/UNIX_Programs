// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
//
// Configuration file parsing implementation
// This source file contains all the functions for parsing the
// configuration file to the enumerated global map and updating
// values on the global map.  Update routine does not parse
// password nor watch directory.

#include <cstdlib>
#include "program5/program5.h"
#include <string>
#include <rude/config.h>
using namespace std;

const int PARAM_LEN = 5;
const std::string parameters[PARAM_LEN] = 
{	
   "Password",
   "WatchDir",
   "Verbose",
   "LogFile",
   "NumVersions" 
};

int parseConfig();
int updateConfig();
int parse(int start_index);

int parseConfig()
{
   try{
      parse(0);
   }catch(exception ex){        
        std::string exMsg = ex.what();
        std::string str = "Failed to parse config file\n" + exMsg;
        cerr << str << endl;
	return 1;
   }
   return 0;
}

int updateConfig()
{
   try{
      parse(2);
   }catch(exception ex){        
        std::string exMsg = ex.what();
        std::string str = "Failed to parse config file\n" + exMsg;
        cerr << str << endl;
	return 1;
   }
   return 0;
}

int parse(int start_index)
{
   rude::Config config;
   std::string conf = globalMap[ROOT] + "/" + globalMap[CONFIG];
   if(!config.load(conf.c_str()))
   {
      throw std::logic_error("Could not load config file");
   }

   config.setSection("Parameters");
   for(int i = start_index; i < PARAM_LEN; i++)
   {
      if(!config.exists(parameters[i].c_str()))
      {
          std::string error = "Missing parameter: " + parameters[i];
          cout << error << endl;
          throw std::logic_error(error);
      }
   }
   for(int i = start_index; i < PARAM_LEN; i++)
   {
      globalMap[ArgToKey[parameters[i]]] = config.getStringValue(parameters[i].c_str());
   }
   
   const std::string log_filename = globalMap[ROOT] + "/" + globalMap[LOGFILE];
   
   FILE *logger = fopen(log_filename.c_str(), "a");
   fclose(logger);

   globalMap[LOGFULLPATH] = log_filename;


   return 0;
}
