/*
  Program 4
  Author: Jimmy Nguyen
  Email: Jimmy@JimmyWorks.net
  
  Program 4 Controller
  This source file serves as the controller for this program with the
  main() function below.  This program is expected to be called by
  a symbolic link, locally, where the symlink is either named
  "parser" or "scanner".  Depending on the caller, the program
  will either process the input stream as a scanner or a parser, using
  the tokens as defined in tokens.l and the grammar defined in grammar.y.
*/

#include <stdio.h>
#include <string.h>
#include "grammar.tab.h"
#define PARSER "./parser"
#define SCANNER "./scanner"

// External functions
extern int yylex();
extern int yyparse();
extern char* yytext;

// Main
// input: int argc         Argument count
// input: char *argv[]	   Arguments passed in
// return: int		   Return code
int main(int argc, char* argv[])
{
   printf("%s\n", argv[0]); 

   // Check the name of caller to determine run mode
   if(strcmp(argv[0],PARSER)==0)  		// Parser mode
   {
      printf("\nOperating in parse mode\n\n");
      yyparse(); // Call yyparse to handle parsing execution
      printf("\n\nParse Successful!\n");
   }
   else if(strcmp(argv[0],SCANNER)==0) 		// Scanner mode
   {
      printf("\nOperating in scan mode\n\n");

      int ntoken; // Current token
      do
      {
         ntoken = yylex(); // Get token from yylex
         switch(ntoken) // Handle token by printing what was found
	 {
            case 0: // Reached end of file
	    	printf("yylex has reached END OF FILE\n");
		break;
	    case SPACE:
	    	printf("yylex returned SPACE token \n");
		break;
	    case EOL:
	    	printf("yylex returned EOL token \n");
		break;
	    case NAME_INITIAL:
	    	printf("yylex returned NAME_INITIAL token (%s)\n", yytext);
		break;
	    case SR:
	    	printf("yylex returned SR token (%s)\n", yytext);
		break;
	    case JR:
	    	printf("yylex returned JR token (%s)\n", yytext);
		break;
	    case ROMAN_NUM:
	    	printf("yylex returned ROMAN_NUM token (%s)\n", yytext);
		break;
	    case NAME:
	    	printf("yylex returned NAME token (%s)\n", yytext);
		break;
	    case INT:
	    	printf("yylex returned INT token (%s)\n", yytext);
		break;
	    case IDENTIFIER:
	    	printf("yylex returned IDENTIFIER token (%s)\n", yytext);
		break;
	    case COMMA:
	    	printf("yylex returned COMMA token (%s)\n", yytext);
		break;
	    case DASH:
	    	printf("yylex returned DASH token (%s)\n", yytext);
		break;
	    case HASH:
	    	printf("yylex returned HASH token (%s)\n", yytext);
		break;
	    default:
	        printf("ERROR: Missing token case in program main\n"
		       "Token value: %d\n"
		       "YYTEXT: %s\n", ntoken, yytext);
	 }
      }while(ntoken); // While not at end of file, keep going...

      printf("\n\nScan Successful!\n");
   }
   else		// Else, print USAGE
   {
      printf("Must use symlink while in local directory.\n"
             "Usage:\n"
	     "./scanner < FILE"
             "./parser  < FILE");
      
      return(1); // Failed to execute scanner or parser
   }

   return 0; // Exit success!
}
