/*
 * Program 6 - Binary File I/O Visualization
 * Author: Jimmy Nguyen
 * Email: jimmy@jimmyworks.net
 * 
 * Binary File Reader Implementation
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string>
#include <stdexcept>
#include "program6.h"
using namespace std;

/*
 * Read Input File
 * Reads the specific binary file for this project.
 * Structure: 
 *  1    - BinaryFileHeader object
 *  Many - BinaryFileRecord objects
 *
 *  input: const char *infilename	local filename of binary file
 *  return: string *array		string array of data
 *  					array[0] = array size
 *  					array[1] = magic number
 *  					array[2] = version number
 *  					array[3+] = string in records
*/
string* readInputFile(const char *infilename)
{
  // Create class instances to hold data
  BinaryFileHeader *fileHeader = new BinaryFileHeader();
  BinaryFileRecord *fileRecord = new BinaryFileRecord();

  // Open the input file in binary mode
  ifstream binInfile (infilename, ios::in | ios::binary);
 
  // String array to return
  string *array;

  // Process the file if successfully opened
  if(binInfile.is_open())
  {
    // First read the header
    binInfile.read((char *) fileHeader, sizeof(BinaryFileHeader));
   
    // Store values from the header into temp variables
    string magicNumber = to_string(fileHeader->magicNumber);
    string version = to_string(fileHeader->versionNumber);
    int arraySize = (fileHeader->numRecords)+3;

    // Allocate space for the array
    array = new string[arraySize];

    // Assign values to the array
    array[0] = to_string(arraySize);
    array[1] = magicNumber;
    array[2] = version;

    // For remaining records, read the record and store to array
    for(int i=3; i < arraySize; i++)
    {
      binInfile.read((char *) fileRecord, sizeof(BinaryFileRecord)); 
      string record(fileRecord->stringBuffer);
      array[i] = record;
    } 

    // Close the binary file when done
    binInfile.close();
  }
  // If the file failed to open, throw an exception
  else
  {
    throw std::runtime_error("");
  }

  // return the values extracted
  return array;
}

