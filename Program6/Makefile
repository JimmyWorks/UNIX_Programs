#   Program 6 Binary File I/O Visualization
#   Author: Jimmy Nguyen
#   Email: Jimmy@JimmyWorks.net
#
#   Description:
#   Makefile for Program 6: Binary File I/O Visualization
#   Commands:
#   make		Make all executables.
#   make clean		Clean all intermediate files
#   make backup 	Make a backup of the current project

# Project name for make backup
PROJECTNAME = Program6

#
# ATTENTION!!
# The two variables below must be changed to your library
# and header directories for CDK
#
CDK_LIB = /usr/lib
CDK_HEAD = /usr/include

# Filenames
 # Source
SRC = program6.cc \
       binaryIO.cc
 # Directories
SRC_DIR = ./src/
INC_DIR = ./include/

 # Source with path
SRCS=$(SRC:%=$(SRC_DIR)%)

# Executables
EXE = program6

# Compilers and Flags

CXX = g++
CXXFLAGS = -Wall -g -std=c++11 
CPPFLAGS = -Wall -I$(INC_DIR) -I$(CDK_HEAD) -std=c++11
LDFLAGS = -L$(CDK_LIB)
LDLIBS = -lcdk -lcurses

# Make Targets
OBJS=$(SRCS:cc=o)

 # make
all: $(EXE) 

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS) 

 # make clean
clean: 
	rm -f $(SRC_DIR)*.o $(EXE) $(SRC_DIR)*.d

Makefile: $(SRCS:.c=.d)

 # Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

 # make backup (Backup Target)
backup: clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


 # Include the dependency files
-include $(SRCS:.cc=.d)


