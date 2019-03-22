#!/bin/bash
# Bash script for running test cases
# Author: Jimmy H. Nguyen
# Email: Jimmy@JimmyWorks.net

clear

echo "Starting Bash script to test \"executable\""

# Create headers for log files
echo "Creating header for output files: \"output.log\" and \"error.log\""
echo "Standard Output Log" >output.log
echo "Standard Error Log" >error.log
echo "Author: Jimmy H. Nguyen" | tee -a output.log error.log >/dev/null
echo "Email: Jimmy@JimmyWorks.net" | tee -a output.log error.log >/dev/null

# Run all test cases

echo "Running \"program\" with 0 arguments."
./program >>output.log 2>>error.log
echo "   stdout saved to \"output.log\""
echo "   stderr saved to \"error.log\""

echo "Running \"program\" with 1 argument."
./program >>output.log 2>>error.log hello
echo "   stdout appended to \"output.log\""
echo "   stderr appended to \"error.log\""

echo "Running \"program\" with 5 arguments."
./program >>output.log 2>>error.log My name is Inigo Montoya.
echo "   stdout appended to \"output.log\""
echo "   stderr appended to \"error.log\""

echo "Done!"
echo ""
