%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "defs.h"

AstNode* rootNode;

Symbol* symbStack[STACK_SIZE];
int stackPos = -1;

Symbol* symbTable[SYMB_TABLE_LENGTH];

Symbol* p1;
Symbol* p2;
Symbol* p3;
Symbol* p4;

//Symbol* runtimeSyb[MAX_DEPTH];
int currDepth = -1;

%}

%union {
	int yint;
	char ystr[80];
	AstNode* node;
}

%start Program

%token MAINCLASS STATIC VOID PUBLIC MAIN INT FLOAT PRINTLN FOR WHILE IF ELSE
%token EQ NEQ LE GE
%token <ystr> ID NUM

%type <node> Program CompStmt StmtList Stmt
%type <node> Decleration IdList Type DecId
%type <node> NullStmt AssignStmt ForStmt WhileStmt IfStmt
%type <node> BoolExpr AssignExpr AssId Expr OpAssignExpr
%type <node> OpBoolExpr ElsePart CompOp
%type <node> RVal Term Factor

%%

Program		:	MAINCLASS ID '{' PUBLIC STATIC VOID MAIN '(' ')' CompStmt '}'
				{
					negateSymbols(currDepth);
					currDepth--;
					rootNode = mkNode(astProgram,NULL,$10,NULL,NULL,NULL);
				}
			
			|	
				{
					rootNode = mkNode(astEmptyProgram,NULL,NULL,NULL,NULL,NULL);
				}

			;

CompStmt	:	'{' StmtList '}'
				{
					$$ = $2;
				}

			;

StmtList	:	StmtList Stmt
				{
					$$ = mkNode(astStmtList,NULL,$1,$2,NULL,NULL);
				}
			
			|	
				{
					currDepth++;
					$$ = mkNode(astEmptyStmtList,NULL,NULL,NULL,NULL,NULL);
				}

			;

Stmt 		:	AssignStmt
				{
					$$ = $1;
				}

			|	ForStmt
				{
					$$ = $1;
				}

			|	WhileStmt
				{
					$$ = $1;
				}

			|	IfStmt
				{
					$$ = $1;
				}
			
			|	CompStmt
				{
					negateSymbols(currDepth);
					currDepth--;
					$$ = $1;
				}
			
			|	Decleration
				{
					$$ = $1;
				}
			
			|	NullStmt
				{
					$$ = $1;
				}
			
			|	PRINTLN '(' Expr ')'
				{
					$$ = mkNode(astPrintStmt,NULL,$3,NULL,NULL,NULL);
				}

			;

Decleration	:	Type IdList ';'
				{
					$$ = mkNode(astDecleration,NULL,$1,$2,NULL,NULL);
				}
			;

Type 		:	INT
				{
					p1 = mkSymbol("",INT);
					$$ = mkNode(astInt,NULL,NULL,NULL,NULL,NULL);
					pushStack(p1);
				}

			|	FLOAT
				{
					p1 = mkSymbol("",FLOAT);
					$$ = mkNode(astFloat,NULL,NULL,NULL,NULL,NULL);
					pushStack(p1);
				}

			;

IdList		:	DecId ',' IdList
				{
					$$ = mkNode(astIdList,NULL,$1,$3,NULL,NULL);
				}

			| 	DecId	
				{
					$$ = mkNode(astIdList,NULL,$1,NULL,NULL,NULL);
				}

			;

DecId 		: 	ID
				{
					p1 = popStack();
					p2 = mkSymbol($1,p1->varType);
					p2->isVar = TRUE;
					p2->accessible = TRUE;
					p2->depth = currDepth;
					if(!addToTable(p2)) {
						strcpy(p2->errMsg,"Error: id already declared");
						$$ = mkNode(astError,p2,NULL,NULL,NULL,NULL);
					} else {
						$$ = mkNode(astDecId,p2,NULL,NULL,NULL,NULL);
						//TO DO: add ID to symbTable
						pushStack(p1);
					}
				}

			;

NullStmt	:	';'
				{
					$$ = mkNode(astNullStmt,NULL,NULL,NULL,NULL,NULL);
				}
			
			;

AssignStmt	:	AssignExpr ';'
				{
					$$ = mkNode(astAssignStmt,NULL,$1,NULL,NULL,NULL);
				}
			
			;

AssignExpr 	:	AssId '=' Expr
				{
					p3 = popStack();
					p4 = popStack();
					// if(p4->varType == INT && p3->varType == FLOAT ) {
					// 	printf("%s\n", "Error: id and rValue not compatible types");
					// 	exit(1);
					// }
					p1 = mkSymbol("",p4->varType);
					pushStack(p1);
					$$ = mkNode(astAssignExp,NULL,$1,$3,NULL,NULL);	
				}

			;

AssId		:	ID
				{
					p1 = findId($1,currDepth);
					if(p1) {
						if(p1->accessible == TRUE)
							pushStack(p1);
						else {
							//printf("id %s in wrong scope\n", p1->name);
							strcpy(p1->errMsg,"Error: id in wrong scope");
							$$ = mkNode(astError,p1,NULL,NULL,NULL,NULL);
							break;
						}
						$$ = mkNode(astAssId,p1,NULL,NULL,NULL,NULL);
					} else {
						p1 = mkSymbol("",INT);
						strcpy(p1->errMsg, "Error: Undeclered id was used");
						$$ = mkNode(astError,p1,NULL,NULL,NULL,NULL);
					}
				}

Expr 		:	AssignExpr
				{
					//nothing at the moment
					$$ = $1;
				}

			|	RVal
				{
					$$ = $1;
				}

			;

ForStmt		:	FOR '(' OpAssignExpr ';' OpBoolExpr ';' OpAssignExpr ')' Stmt
				{
					$$ = mkNode(astForStmt,NULL,$3,$5,$7,$9);
				}
			;

OpAssignExpr:	AssignExpr
				{
					$$ = $1;
				}
			
			|	
				{
					$$ = NULL;
				}
			
			;

OpBoolExpr	:	BoolExpr
				{
					$$ = $1;
				}

			|	
				{
					$$ = NULL;
				}

			;

WhileStmt	:	WHILE '(' BoolExpr ')' Stmt
				{	
					$$ = mkNode(astWhileStmt,NULL,$3,$5,NULL,NULL);
				}

			;

IfStmt		:	IF '(' BoolExpr ')' Stmt ElsePart
				{
					$$ = mkNode(astIfStmt,NULL,$3,$5,$6,NULL);
				}

			;

ElsePart	:	ELSE Stmt
				{
					$$ = mkNode(astElseStmt,NULL,$2,NULL,NULL,NULL);
				}
			
			|	{
					$$ = NULL;
				}
			
			;

BoolExpr 	:	Expr CompOp	Expr
				{
					$$ = mkNode(astBoolExp,NULL,$1,$2,$3,NULL);
				}

			;

CompOp		:	EQ
				{
					$$ = mkNode(astEqEqOp,NULL,NULL,NULL,NULL,NULL);
				}

			|	'<'
				{
					$$ = mkNode(astLessOp,NULL,NULL,NULL,NULL,NULL);
				}

			|	'>'
				{
					$$ = mkNode(astGreaterOp,NULL,NULL,NULL,NULL,NULL);
				}

			|	LE
				{
					$$ = mkNode(astLessEqOp,NULL,NULL,NULL,NULL,NULL);
				}

			|	GE
				{
					$$ = mkNode(astGreaterEqOp,NULL,NULL,NULL,NULL,NULL);
				}

			|	NEQ
				{
					$$ = mkNode(astNotEqOp,NULL,NULL,NULL,NULL,NULL);
				}

			;

RVal		:	RVal '+' Term
				{
					p3 = popStack();
					p4 = popStack();
					p1 = checkAdd(p3,p4);
					// if(p1 != NULL)
						pushStack(p1);
					// else {
					// 	printf("incompatible operands\n");
					// 	exit(1);
					// }
					$$ = mkNode(astAddExp,NULL,$1,$3,NULL,NULL);
				}

			|	RVal '-' Term
				{
					p3 = popStack();
					p4 = popStack();
					p1 = checkSub(p3,p4);
					// if(p1 != NULL)
						pushStack(p1);
					// else {
					// 	printf("incompatible operands\n");
					// 	exit(1);
					// }
					$$ = mkNode(astSubExp,NULL,$1,$3,NULL,NULL);
				}
			
			|	Term
				{
					$$ = $1;
				}
			
			;

Term		:	Term '*' Factor
				{
					p3 = popStack();
					p4 = popStack();
					p1 = checkMult(p3,p4);
					pushStack(p1);
					$$ = mkNode(astMultExp,NULL,$1,$3,NULL,NULL);
				}

			|	Term '/' Factor
				{
					p3 = popStack();
					p4 = popStack();
					p1 = checkDiv(p4,p3); //division: p4/p3
					// if(p1 != NULL)
						pushStack(p1);
					// else {
					// 	printf("incompatible operands\n");
					// 	exit(1);
					// }
					$$ = mkNode(astDivExp,NULL,$1,$3,NULL,NULL);
				}
			
			|	Factor
				{
					$$ = $1;
				}
			
			;

Factor		:	'(' Expr ')'
				{
					$$ = $2;
				}

			|	'-' Factor
				{
					/* if($2->nodeType == astNum) {
						if($2->nodSymbol->varType == INT)
							$2->nodSymbol->value.i = -$2->nodSymbol->value.i;
						else
							$2->nodSymbol->value.f = -$2->nodSymbol->value.f;
					} else {

					} */

					$$ = mkNode(astUminus,NULL,$2,NULL,NULL,NULL);
				}
			
			|	AssId
				{
					$$ = $1;
				}

			|	NUM
				{
					if(isInt($1)) {
						p3 = mkSymbol("",INT);
						p3->value.i = atoi($1);
					} else {
						p3 = mkSymbol("",FLOAT);
						p3->value.f = atof($1);
					}
					p3->isVar = FALSE;
					$$ = mkNode(astNum,p3,NULL,NULL,NULL,NULL);
					pushStack(p3);
				}

			;

%%

#include "funcs.c"
#include "main.c"