#!/bin/bash
# Compile Bash Script
# Author: Jimmy Nguyen
# Email: jimmy@jimmyworks.net

# Compile program.cc using C++11 and include directory for headers
echo "Compiling program.cc..."
g++ -c -std=c++11 program.cc -I include/

# Compile programParser.cc using C++11 and include directory for headers
echo "Compiling programParser.cc..."
g++ -c -std=c++11 programParser.cc -I include/

# Compile program executable using output files from above
echo "Linking object files to create executable..."
g++ program.o programParser.o -o program
echo "Done."
