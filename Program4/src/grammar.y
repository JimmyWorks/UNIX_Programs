        /*
        Program 4
        Author: Jimmy Nguyen
        Email: Jimmy@JimmyWorks.net

	Description:
        Yacc File for parsing postal addresses and converting to XML.
	Stdout reports all messages and errors found while the XML
	statements are printed to Stderr.
        */

%{
#include <stdio.h>
#include <stdlib.h>

// Function signatures used in middle section
extern int yylex();
void yyerror(char const*); // Suppressed stderr messages from Bison
void myerror(char const*); // Custom error messages
void handle(const char*, char*); // Handle identified strings to their tags

// XML Tags
const char *fname = "FirstName";
const char *lname = "LastName";
const char *suffix = "Suffix";
const char *housenum = "HouseNumber";
const char *street = "StreetName";
const char *apt = "AptNum";
const char *citystr = "City";
const char *statestr = "State";
const char *zip5str = "Zip5";
const char *zip4str = "Zip4";

// Error Messages
const char *nameErrorMsg = "Bad name part... Skipping to newline";
const char *streetAddrErrorMsg = "Bad street address part... Skipping to newline";
const char *locationErrorMsg = "Bad location part... Skipping to newline";

/*
  The following segment of the top block defines all the tokens used by
  both main() and the lex file through the tab.h header.  Tokens are also
  associated with their corresponding types through union.  The parser
  starts at "program" in the grammar section.
*/
%}

%union {char* name}

%token NAME_INITIAL SR JR ROMAN_NUM 
%token NAME INT IDENTIFIER EOL COMMA 
%token DASH HASH SPACE 
%type <name> NAME_INITIAL SR JR ROMAN_NUM NAME IDENTIFIER INT

%type <name> personal_part last_name suffix_part
%type <name> street_number street_name apt_number 
%type <name> city state zip5 zip4

%start program
%{ 
/*
   In the following section, the grammar is defined for processing a list
   of postal addresses.  Starting at "program", the program processes postal
   addresses, which can be one or multiple address blocks.  Each address block
   is composed of three parts: name_part, street_address, and location_part.
   Each part is defined and the terminals pertaining to that part is located
   directly below it.  Terminals are passed back up to one of the three main
   parts for processing where the handle function is called to handle the 
   string found and the tag associated with it.  In cases were tokens passed
   do not match a grammar rule, the error is caught and handled with the 
   myerror function, moving on to EOL to continue parsing.
*/
%}
%%

program		: postal_addresses	{ /* program start */ }

postal_addresses: address_block
		| address_block postal_addresses

address_block	: name_part street_address location_part { fprintf(stderr, "\n");} 

name_part	: personal_part SPACE last_name SPACE suffix_part EOL
			{ handle(fname, $1); 
			  handle(lname, $3); 
			  handle(suffix, $5); }
		| personal_part SPACE last_name EOL
			{ handle(fname, $1); 
			  handle(lname, $3);  }
		| error EOL { myerror(nameErrorMsg);}

personal_part	: NAME		{$$ = $1;}
		| NAME_INITIAL  {$$ = $1;}
last_name	: NAME		{$$ = $1;}
suffix_part	: SR 		{$$ = $1;}
		| JR		{$$ = $1;}
		| ROMAN_NUM	{$$ = $1;}

street_address	: street_number SPACE street_name SPACE apt_number EOL
			{ handle(housenum, $1);
			  handle(street, $3);
			  handle(apt, $5);     }
		| street_number SPACE street_name EOL
			{ handle(housenum, $1);
			  handle(street, $3);  }
		| error EOL { myerror(streetAddrErrorMsg);}

street_number	: INT 		{$$ = $1;}
		| IDENTIFIER	{$$ = $1;}
street_name	: NAME		{$$ = $1;}
apt_number	: HASH INT	{$$ = $2;}
		| INT		{$$ = $1;}

location_part	: city COMMA SPACE state SPACE zip5 DASH zip4 EOL
			{ handle(citystr, $1);
			  handle(statestr, $4);
			  handle(zip5str, $6);
			  handle(zip4str, $8);  }
		| city COMMA SPACE state SPACE zip5 EOL
			{ handle(citystr, $1);
			  handle(statestr, $4);
			  handle(zip5str, $6);  }
		| error EOL { myerror(locationErrorMsg);}

city		: NAME		{$$ = $1;}
state		: NAME		{$$ = $1;}
zip5		: INT		{$$ = $1;}
zip4		: INT		{$$ = $1;}

%%
// Functions

// Handle each identified token value
// input: char const* id         The tag associated with this string
// input: char const* value      The identified string
// return: none
void handle(const char* id, char* value)
{
   // Print to stderr
   fprintf(stderr, "<%s>%s</%s>\n", id, value, id);
}

// Report custom errors
// input: char const* s         error message
// return: none
void myerror (char const *s)
{
   // Print errors to stdout
   printf("%s\n", s);
}

// Bison yyerror messages
// input: char const* s         error message
// return: none
void yyerror (char const *s)
{
   // Suppress error messages from Bison
   // For bug testing only...
   //fprintf(stderr, "%s\n", s);
}

