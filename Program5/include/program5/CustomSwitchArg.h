// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
//
// CustomSwitchArg class header
// This is the header for the CustomSwitchArg class which
// inherits from both the TCLAP library's UnlabeledValueArg and
// the abstract base class, ArgInterface.  Implements the
// setProperties() method.
//
// This uses the double-dispatch design pattern.

#include <string>
#include "tclap/CmdLine.h"
#include "ArgInterface.h"

#ifndef _CUSTOM_SWITCHARG_
#define _CUSTOM_SWITCHARG_

class CustomSwitchArg : public TCLAP::SwitchArg, public ArgInterface
{
   public:
   CustomSwitchArg(const std::string flag, const std::string name, const std::string desc, TCLAP::CmdLineInterface &command, bool def, TCLAP::Visitor *visitor);
   void setProperties();
};

#endif
