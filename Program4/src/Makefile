#   Program 4
#   Author: Jimmy Nguyen
#   Email: Jimmy@JimmyWorks.net
#
#   Description:
#   Makefile for Program 4: Postal Address Scan/Parse to XML
#   Commands:
#   make		    Make all executables.
#   make clean		Clean all intermediate files, executables, and output files.
#   make test		Make all and run unit test outputting everything to stdout.
#   make delivery	Make all and run all.  Exports results to respective output files.
#   make backup 	Make a backup of the current project

# Project name for make backup
PROJECTNAME = Program4

# Filenames
 # Source
LEX = tokens.c
YACC = grammar.tab.c
MAIN = program4.c
 # Executables
SCANNER = scanner
PARSER = parser
EXE = program4
 # Input and Output
INPUTFILE = input.txt
SCAN_OUTFILE = scanner_output.txt
PARSER_OUTFILE = parser_stdout.txt
PARSER_ERRFILE = parser_stderr.txt

# Directories 
INPUTDIR = ../input/
OUTPUTDIR = ../output/

# Compilers and Flags
 # C
CC = gcc
CCFLAGS =
 # Bison
YC = bison
YCFLAGS = -d
 # Flex
LC = flex
LCFLAGS = 

# Combined Options
INPUT = $(INPUTDIR)$(INPUTFILE)
OBJS = $(YACC) $(LEX) $(MAIN)
SCAN_OUTPATH = $(OUTPUTDIR)$(SCAN_OUTFILE)
PARSE_OUTPATH = $(OUTPUTDIR)$(PARSER_OUTFILE)
PARSE_ERRPATH = $(OUTPUTDIR)$(PARSER_ERRFILE)

# Make Targets

 # make
all: $(EXE) $(SCANNER) $(PARSER)

$(EXE): $(OBJS)
	$(CC) $(CCFLAGS) $^ -o $@

$(YACC) $(YACC:.c=.h): $(YACC:.tab.c=.y)
	$(YC) $(YCFLAGS) $^

$(LEX): $(LEX:.c=.l) $(YACC:.c=.h)
	$(LC) $(LCFLAGS) -o $@ $(LEX:.c=.l)

$(SCANNER): $(EXE)
	ln -s $^ $@

$(PARSER): $(EXE)
	ln -s $^ $@

 # make clean
clean: 
	rm -f *.o $(EXE) $(SCANNER) $(PARSER) $(OUTPUTDIR)* $(LEX) $(YACC) $(YACC:.c=.h)

 # make test
test: all unit_tests

 # make delivery
delivery: all
	./$(SCANNER) < $(INPUT) > $(SCAN_OUTPATH) 
	./$(PARSER) < $(INPUT) >$(PARSE_OUTPATH) 2>$(PARSE_ERRPATH)

 # Routine for unit tests
unit_tests:  
	#	
	# RUNNING UNIT TESTS
	#
	# 1. TESTING SCANNER...
	#
	./$(SCANNER) < $(INPUT) 
	#
	# FINISHED SCANNER TEST
	#
	# 2. TESTING PARSER...
	#
	./$(PARSER) < $(INPUT)
	#
	# FINISHED PARSER TEST
	#
	# ALL TESTS COMPLETED

 # Pattern for .d files.
%.d:%.c
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CC) -MM $(CCFLAGS) $< > $@.$$$$; \
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
-include $(SRCS:.c=.d)
