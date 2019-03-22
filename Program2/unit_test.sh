#!/bin/bash
# Unit Testing Script
#
# This is the unit tester for the Program CLI
# This script checks if any editing/modifications to
# this project has broken past features.
#
# Author: Jimmy Nguyen
# Email:  jimmy@jimmyworks.net

echo
echo "[UNIT TEST 1] Running program without file specified..."
echo "[UNIT TEST 1] Command: ./program"
echo "[UNIT TEST 1] Press enter to continue..."
read x

./program

echo
echo "[UNIT TEST 1] Error and usage should be displayed above"

echo
echo "[UNIT TEST 2] Running program with -u and -l flags..."
echo "[UNIT TEST 2] Command: ./program sample_input.txt -u -l"
echo "[UNIT TEST 2] Press enter to continue..."
read x

./program sample_input.txt -u -l

echo
echo "[UNIT TEST 2] Error for mutually exclusive options show be displayed above"

echo
echo "[UNIT TEST 3] Running program with -h flag..."
echo "[UNIT TEST 3] Command: ./program sample_input.txt -h"
echo "[UNIT TEST 3] Press enter to continue..."
read x

./program sample_input.txt -h

echo
echo "[UNIT TEST 3] Usage should be displayed above"

echo
echo "[UNIT TEST 4] Running program with -- flag and testing -l flag..."
echo "[UNIT TEST 4] Command: ./program sample_input.txt -l -- -u"
echo "[UNIT TEST 4] Press enter to continue..."
read x

./program sample_input.txt -l -- -u

echo
echo "[UNIT TEST 4] Output should be saved to default file: output.txt"

echo
echo "[UNIT TEST 5] Running program with -u flag and specific output file..."
echo "[UNIT TEST 5] Command: ./program sample_input.txt -u -o upper_output.txt"
echo "[UNIT TEST 5] Press enter to continue..."
read x

./program sample_input.txt -u -o upper_output.txt

echo
echo "[UNIT TEST 5] Output should be save to upper_output.txt"

echo
echo "[UNIT TEST 6] Running program with invalid input file..."
echo "[UNIT TEST 6] Command: ./program I_dont_exist -u"
echo "[UNIT TEST 6] Press enter to continue..."
read x

./program I_dont_exist

echo
echo "[UNIT TEST 6] Program should terminate with error message above"
echo
echo "Completed all unit tests."
