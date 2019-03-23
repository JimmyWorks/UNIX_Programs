// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
//
// CustomSwitchArg implementation
// These are the functions for the CustomSwitchArg class which
// inherits from both the TCLAP library's UnlabeledValueArg and
// the abstract base class, ArgInterface.  Implements the
// setProperties() method.
//
// This uses the double-dispatch design pattern.

#include "program5/CustomSwitchArg.h"
#include "tclap/CmdLine.h"
#include <map> 

   extern std::map<int, std::string> globalMap;
   extern std::map<std::string, int> ArgToKey;

   // Constructor passes parameters to TCLAP parent class constructor
   CustomSwitchArg::CustomSwitchArg(const std::string flag, const std::string name, const std::string desc, TCLAP::CmdLineInterface &command, bool def, TCLAP::Visitor *visitor) : TCLAP::SwitchArg(flag, name, desc, command, def, visitor){}

   // Must implement setProperties() enforced by ArgInterface parent
   void CustomSwitchArg::setProperties()
   {
         globalMap[ArgToKey[this->TCLAP::SwitchArg::getName()]] = this->TCLAP::SwitchArg::isSet() ? "true" : "false";
   }

