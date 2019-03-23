/*
 * Program 6 - Binary File I/O Visualization
 * Author: Jimmy Nguyen
 * Email: jimmy@jimmyworks.net
 *
 * Program Header
 */

#include <string.h>
using namespace std;

#ifndef _PROGRAM_6_H_
#define _PROGRAM_6_H_

// Max length of char buffer in BinaryFileRecord
const int maxLen = 25;

// Binary File Header found in binary file
class BinaryFileHeader
{
  public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

// Binary File Record found in binary file
class BinaryFileRecord
{
  public:
  uint8_t strLength;
  char stringBuffer[maxLen];
};

// Function implemented in binaryIO.cc
string* readInputFile(const char *infilename);

#endif
