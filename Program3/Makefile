# Makefile
# Author: Jimmy Nguyen
# Email:  jimmy@jimmyworks.net

# make
all: program 

# make clean
clean: 
	rm -f program a.out *.o *~ *tar.gz

program: program.o
	g++ -std=c++11 program.cc -o $@ 

# make tarball: create tarball without extra files
tarball:
	tar cfvz program.tar.gz * --exclude=bin --exclude=libexec --exclude=gawk --exclude=share --exclude='*.o' --exclude='*~' 

%.o:%.cc
	g++ -c -std=c++11 -o $@ $<

