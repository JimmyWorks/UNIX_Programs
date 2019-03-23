#   Program 5
#   Author: Jimmy Nguyen
#   Email: Jimmy@JimmyWorks.net
#
#   Description:
#   Makefile for Program 5: Make UNIX Deamon
#   Commands:
#   make		Make all executables.
#   make clean		Clean all intermediate files
#   make clean_files	Clean logs and lingering pid files
#   make test		Test the program in command terminal
#   make test_daemon	Test the program in daemon mode
#   make backup 	Make a backup of the current project

# Project name for make backup
PROJECTNAME = Program5

#
# ATTENTION!!
# The two variables below must be changed to your library directory
# and header directory for TCLAP and rudeconfig
#
LIB_DIR = /home/lib/
OSS_HD_DIR = /home/include

# Filenames
 # Source
SRCS = program5globals.cc \
       CustomSwitchArg.cc \
       CustomUnlabeledValueArg.cc \
       program5cli.cc \
       program5rude.cc \
       program5monitor.cc \
       program5.cc
 # Executables
EXE = program5
 # Input and Output
INPUTFILE = input.txt

# Directories 
INPUTDIR = ../input/
OUTPUTDIR = ../output/
BIN_DIR = ../bin/

# Compilers and Flags

CXX = g++
CXXFLAGS = -Wall -static -std=c++11 
CPPFLAGS = -Wall -I../include/ -I$(OSS_HD_DIR) -std=c++11
LDFLAGS = -L$(LIB_DIR)
LDLIBS = -lrudeconfig

# Make Targets
OBJS=$(SRCS:cc=o)

 # make
all: $(EXE) 

$(EXE): $(OBJS)
	$(SET_ENV_LD_LIB_PATH) $(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $(BIN_DIR)$@ $(LDLIBS) 

 # make clean
clean: 
	rm -f *.o $(OUTPUTDIR)* *.d*

 # make test
test: clean_files
	# TESTING WITHOUT DAEMON...
	#
	$(SET_ENV_LD_LIB_PATH) $(BIN_DIR)$(EXE)

test_daemon: clean_files
	# TESTING WITH DAEMON...
	#
	$(SET_ENV_LD_LIB_PATH) $(BIN_DIR)$(EXE) -d

Makefile: $(SRCS:.c=.d)

clean_files:
	rm -f ../dirmond.log
	rm -f ../dirmond.pid

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

