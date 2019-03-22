#!/bin/bash
# Bash script for compiling source files
# Author: Jimmy H. Nguyen
# Email: Jimmy@JimmyWorks.net

clear

echo "Running \"compile.sh\" to compile program files"
echo "Compiling source file \"main.cpp\" into object file \"main.o\""
g++ -c main.cpp
echo "Compiling source file \"sub.cpp\" into object file \"sub.o\""
g++ -c sub.cpp
echo "Linking files to create executable \"executable\""
g++ -o program main.o sub.o

echo "Done"
