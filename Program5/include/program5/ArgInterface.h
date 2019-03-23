// Program 5 - Directory Monitoring Automatic File Backup
// Author: Jimmy Nguyen
// Email: jimmy@jimmyworks.net
//
// ArgInterface class header
// This is the header for the ArgInterface class which is the
// abstract base class for the derived concrete classes:
// CustomUnlabeledValueArg and CustomSwitchArg.  This class
// enforces a pure virtual method, setProperties(), which
// must be implemented by derived classes.
//
// This uses the double-dispatch design pattern.

#ifndef _ARG_INTERFACE_
#define _ARG_INTERFACE_
class ArgInterface
{
   public:
   ArgInterface(){};
   virtual ~ArgInterface(){};
   virtual void setProperties()=0;
};
#endif
