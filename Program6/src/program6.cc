/*
 * Program 6 - Binary File I/O Visualization
 * Author: Jimmy Nguyen
 * Email: jimmy@jimmyworks.net
 * 
 * Description:
 * Using the Curse Development Kit for visualization, a supplied
 * binary file with a defined structure is read to obtain data
 * to be outputted to the CDK matrix.  The header file that
 * comes with this project contains the classes needed to
 * extract data from the binary file.
 *
 * Program Main Controller
 */

#include <iostream>
#include <string>
#include "cdk.h"
#include "program6.h"
#include <sstream>
#include <iomanip>
using namespace std;

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

// Name of binary file in local project folder
const char *BINARYFILE = "test.bin";


/*
 * Main
 * input: void
 * return: int		return code
 * 			0 = success
 * 			1 = failure to read binary file
 */
int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;	     // CDK screen
  CDKMATRIX     *myMatrix;           // CDK matrix

  // Matrix begins at 1,1. Row and Column 0 are placeholders
  // The row and column identifiers, cell width and types 
  // can be found below
  const char    *rowTitles[] = {"", "a", "b", "c", "d", "e"};
  const char    *columnTitles[] = {"", "a", "b", "c"};
  int		boxWidths[] = { BOX_WIDTH, 
				BOX_WIDTH, 
				BOX_WIDTH, 
				BOX_WIDTH, 
				BOX_WIDTH, 
				BOX_WIDTH};
  int		boxTypes[] = {	vMIXED, 
  				vMIXED, 
				vMIXED, 
				vMIXED,  
				vMIXED,  
				vMIXED};

  // Returned result string array with values from binary file
  string *result; 

  // Read binary file and obtain values for matrix visualization
  try{
    result = readInputFile(BINARYFILE);
  }catch(std::exception ex){
    cout << "Failed to read binary file." << endl;
    cout << "Exiting..." << endl;
    return 1;
  }

  // Initialize CDK screen
  window = initscr();
  cdkscreen = initCDKScreen(window);

  // Start CDK Colors 
  initCDKColor();

  
  // Create the matrix
  // Need to manually cast (const char**) to (char **)
  myMatrix = newCDKMatrix(	cdkscreen, 
  				CENTER, 
				CENTER, 
				MATRIX_HEIGHT, 
				MATRIX_WIDTH, 
				MATRIX_HEIGHT, 
				MATRIX_WIDTH,
                          	MATRIX_NAME_STRING, 
			  	(char **) rowTitles, 
			  	(char **) columnTitles, 
			  	boxWidths,
                                boxTypes, 
				1, 1, ' ', ROW, true, true, false);

  // Verify matrix created successfully
  if (myMatrix ==NULL)
  {
    printf("Error creating Matrix\n");
    exit(1);
  }

  // Get array size and number of records from first array index
  // First three elements are: array size, magic number, and version number
  int arraySize = stoi(result[0]);
  int numRecords = arraySize - 3; // number of records
  string showNumRecords = "NumRecords: " + to_string(numRecords);

  // Get magic number
  stringstream stream;
  stream << std::uppercase << std::hex << stol(result[1]);
  string magicNumBase16 = "Magic: 0x" + stream.str();

  // Get version number
  string version = "Version: " + result[2];

  // Display the Matrix
  drawCDKMatrix(myMatrix, true);

  // Display all values in the matrix
  // Starting at row 2, column 1 is the string length and column 2 is the extracted
  // string from the binary file record.  This file only has 4 records.
  setCDKMatrixCell(myMatrix, 1, 1, magicNumBase16.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, showNumRecords.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
  setCDKMatrixCell(myMatrix, 2, 1, ("strlen: " + to_string(result[3].length())).c_str());
  setCDKMatrixCell(myMatrix, 2, 2, result[3].c_str());
  setCDKMatrixCell(myMatrix, 3, 1, ("strlen: " + to_string(result[4].length())).c_str());
  setCDKMatrixCell(myMatrix, 3, 2, result[4].c_str());
  setCDKMatrixCell(myMatrix, 4, 1, ("strlen: " + to_string(result[5].length())).c_str());
  setCDKMatrixCell(myMatrix, 4, 2, result[5].c_str());
  setCDKMatrixCell(myMatrix, 5, 1, ("strlen: " + to_string(result[6].length())).c_str());
  setCDKMatrixCell(myMatrix, 5, 2, result[6].c_str());

  // Draw the matrix
  drawCDKMatrix(myMatrix, true);

  // So we can see results, pause until a key is pressed
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}

