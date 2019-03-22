        /*
        Program 4
        Author: Jimmy Nguyen
        Email: Jimmy@JimmyWorks.net

        Lex file for identifying tokens in postal address input stream.
	The Yacc file associated with this project needs these tokens
	to output the final XML document.  This Lex file needs the enumerated
	token names identified by the Yacc file through tab.h header.
        */

%option noyywrap
%option nounput
%option noinput

%{
// Include the tab.h header from the Yacc file
#include "grammar.tab.h"

/*
   The next section identifies the tokens found in the input stream.
*/
%}
%%
[A-Z][\.]?			{yylval.name = strdup(yytext); return NAME_INITIAL;}
"Sr"\.?				{yylval.name = strdup(yytext); return SR;}
"Jr"\.?				{yylval.name = strdup(yytext); return JR;}
[VXLCDM]|[IVXLCDM][IVXLCDM]+	{yylval.name = strdup(yytext); return ROMAN_NUM;}
[a-zA-Z][a-zA-Z]+		{yylval.name = strdup(yytext); return NAME;}
[0-9]+				{yylval.name = strdup(yytext); return INT;}
[a-zA-Z0-9]+			{yylval.name = strdup(yytext); return IDENTIFIER;}
[ \t]+         		        {return SPACE;/*No newline is identified as space*/}
[ \t\n]+			{return EOL; /*Group together whitespace if newline*/}
,				{return COMMA;}
-				{return DASH;}
#				{return HASH;}
.				{/* toss other tokens */}
%%

