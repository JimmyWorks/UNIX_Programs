// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
//
// CustomUnlabeledValueArg implementation
// These are the functions for the CustomUnlabeledValueArg class which
// inherits from both the TCLAP library's UnlabeledValueArg and
// the abstract base class, ArgInterface.  Implements the
// setProperties() method.
//
// This uses the double-dispatch design pattern.


#include <map>
#include <string>
#include "tclap/CmdLine.h"
#include "program5/CustomUnlabeledValueArg.h"

   extern std::map<int, std::string> globalMap;
   extern std::map<std::string, int> ArgToKey;

   // Constructor passes parameters to TCLAP parent class constructor
   CustomUnlabeledValueArg::CustomUnlabeledValueArg(const std::string name, const std::string desc, bool req, std::string value, const std::string typeDesc, TCLAP::CmdLineInterface &command, bool ignoreable, TCLAP::Visitor *visitor) : TCLAP::UnlabeledValueArg<std::string>(name, desc, req, value, typeDesc, command, ignoreable, visitor){}

   // Must implement setProperties() enforced by ArgInterface parent
   void CustomUnlabeledValueArg::setProperties()
   {
      globalMap[ArgToKey[this->TCLAP::UnlabeledValueArg<std::string>::getName()]] = this->TCLAP::UnlabeledValueArg<std::string>::getValue();
   }

