// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
//
// CustomUnlabeledValueArg class header
// This is the header for the CustomUnlabeledValueArg class which 
// inherits from both the TCLAP library's UnlabeledValueArg and
// the abstract base class, ArgInterface.  Implements the 
// setProperties() method.
//
// This uses the double-dispatch design pattern.

#include <string>
#include "tclap/CmdLine.h"
#include "ArgInterface.h"

#ifndef _CUSTOM_UNLABELED_VALUE_ARG_
#define _CUSTOM_UNLABELED_VALUE_ARG_

class CustomUnlabeledValueArg : public TCLAP::UnlabeledValueArg<std::string>, public ArgInterface
{
   public:
   CustomUnlabeledValueArg(const std::string name, const std::string desc, bool req, std::string value, const std::string typeDesc, TCLAP::CmdLineInterface &command, bool ignoreable, TCLAP::Visitor *visitor);
   void setProperties();
};

#endif
