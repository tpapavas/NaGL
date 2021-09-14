%{
	#include <stdio.h>
	#include <string.h>
	#include "defs.h"
	#include "y.tab.h"
%}

letter 	[a-zA-Z]
digit	[0-9]

%option noyywrap

%%
"mainclass"						{ 
									//printf("%s\tclass def\n",yytext);
									strcpy(yylval.ystr,yytext);
									return MAINCLASS;
								}

"public"						{ 
									//printf("%s\taccess\n",yytext);
									strcpy(yylval.ystr,yytext);
									return PUBLIC;
								}

"static"						{ 
									//printf("%s\tdef\n",yytext);
									strcpy(yylval.ystr,yytext);
									return STATIC;
								}

"void"							{ 
									//printf("%s\treturn\n",yytext);
									strcpy(yylval.ystr,yytext);
									return VOID;
								}

"main"							{ 
									//printf("%s\tmain function\n",yytext);
									strcpy(yylval.ystr,yytext);
									return MAIN;
								}

"int"							{ 
									//printf("%s\tmain function\n",yytext);
									strcpy(yylval.ystr,yytext);
									return INT;
								}

"float"							{ 
									//printf("%s\tmain function\n",yytext);
									strcpy(yylval.ystr,yytext);
									return FLOAT;
								}			

"if"							{ 
									//printf("%s\tmain function\n",yytext);
									strcpy(yylval.ystr,yytext);
									return IF;
								}

"else"							{ 
									//printf("%s\tmain function\n",yytext);
									strcpy(yylval.ystr,yytext);
									return ELSE;
								}					

"for"							{ 
									//printf("%s\tmain function\n",yytext);
									strcpy(yylval.ystr,yytext);
									return FOR;
								}

"while"							{ 
									//printf("%s\tmain function\n",yytext);
									strcpy(yylval.ystr,yytext);
									return WHILE;
								}

"println"							{ 
									//printf("%s\tmain function\n",yytext);
									strcpy(yylval.ystr,yytext);
									return PRINTLN;
								}

{letter}({letter}|{digit}|_)*  	{ 
									//printf("%s\tid\n",yytext);
									strcpy(yylval.ystr,yytext);
									return ID;
								}

{digit}+("."{digit}*)?			{ 
									//printf("%s\tnum\n",yytext);
									strcpy(yylval.ystr,yytext);
									return NUM;
								}

"*"								{ 
									//printf("%s\tmul\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '*';
								}

"/"								{ 
									//printf("%s\tdiv\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '/';
								}

"%"								{ 
									//printf("%s\tmod\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '%';
								}

"+"								{ 
									//printf("%s\tplus\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '+';
								}

"-"								{ 
									//printf("%s\tminus\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '-';
								}

"("								{ 
									//printf("%s\tlpar\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '(';
								}

")"								{ 
									//printf("%s\trpar\n",yytext);
									strcpy(yylval.ystr,yytext);
									return ')';
								}

"{"								{ 
									//printf("%s\trbracket\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '{';
								}

"}"								{ 
									//printf("%s\tlbracket\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '}';
								}

"="								{ 
									//printf("%s\tassign\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '=';
								}

"=="							{ 
									//printf("%s\tee\n",yytext);
									strcpy(yylval.ystr,yytext);
									return EQ;
								}

"!="							{ 
									//printf("%s\tne\n",yytext);
									strcpy(yylval.ystr,yytext);
									return NEQ;
								}

"<"								{ 
									//printf("%s\tl\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '<';
								}

"<="							{ 
									//printf("%s\tle\n",yytext);
									strcpy(yylval.ystr,yytext);
									return LE;
								}

">"								{ 
									//printf("%s\tg\n",yytext);
									strcpy(yylval.ystr,yytext);
									return '>';
								}

">="							{ 
									//printf("%s\tge\n",yytext);
									strcpy(yylval.ystr,yytext);
									return GE;
								}

";"								{ 
									//printf("%s\tcol\n",yytext);
									strcpy(yylval.ystr,yytext);
									return ';';
								}

","								{ 
									//printf("%s\tcommma\n",yytext);
									strcpy(yylval.ystr,yytext);
									return ',';
								}

[ \t\n\v\f\r]+					{ 
									//printf("%s\twspace\n",yytext);
									strcpy(yylval.ystr,yytext);
								}

.								{
									//printf("%s\tundefined\n",yytext);
								}

%%