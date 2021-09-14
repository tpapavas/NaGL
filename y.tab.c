#ifndef lint
static char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif
#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define yyclearin (yychar=(-1))
#define yyerrok (yyerrflag=0)
#define YYRECOVERING (yyerrflag!=0)
#define YYPREFIX "yy"
#line 2 "ssanal.y"

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

/*Symbol* runtimeSyb[MAX_DEPTH];*/
int currDepth = -1;

#line 26 "ssanal.y"
typedef union {
	int yint;
	char ystr[80];
	AstNode* node;
} YYSTYPE;
#line 41 "y.tab.c"
#define MAINCLASS 257
#define STATIC 258
#define VOID 259
#define PUBLIC 260
#define MAIN 261
#define INT 262
#define FLOAT 263
#define PRINTLN 264
#define FOR 265
#define WHILE 266
#define IF 267
#define ELSE 268
#define EQ 269
#define NEQ 270
#define LE 271
#define GE 272
#define ID 273
#define NUM 274
#define YYERRCODE 256
short yylhs[] = {                                        -1,
    0,    0,    1,    2,    2,    3,    3,    3,    3,    3,
    3,    3,    3,    4,    6,    6,    5,    5,    7,    8,
    9,   14,   15,   16,   16,   10,   17,   17,   18,   18,
   11,   12,   19,   19,   13,   20,   20,   20,   20,   20,
   20,   21,   21,   21,   22,   22,   22,   23,   23,   23,
   23,
};
short yylen[] = {                                         2,
   11,    0,    3,    2,    0,    1,    1,    1,    1,    1,
    1,    1,    4,    3,    1,    1,    3,    1,    1,    1,
    2,    3,    1,    1,    1,    9,    1,    0,    1,    0,
    5,    6,    2,    0,    3,    1,    1,    1,    1,    1,
    1,    3,    3,    1,    3,    3,    1,    3,    2,    1,
    1,
};
short yydefred[] = {                                      0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    5,    0,    0,    1,   15,   16,    0,    0,    0,    0,
   23,    3,   20,   10,    4,   11,    0,   12,    6,    7,
    8,    9,    0,    0,    0,    0,    0,    0,   19,    0,
    0,   21,    0,   51,    0,    0,   24,    0,    0,    0,
    0,   47,   27,    0,    0,    0,    0,   14,    0,   22,
    0,   50,   49,   13,    0,    0,    0,    0,    0,    0,
   36,   41,   39,   40,   37,   38,    0,    0,   17,   48,
    0,    0,   45,   46,   29,    0,   31,   35,    0,    0,
    0,   32,    0,   33,    0,   26,
};
short yydgoto[] = {                                       2,
   24,   13,   25,   26,   40,   27,   41,   28,   29,   30,
   31,   32,   55,   47,   34,   56,   54,   86,   92,   77,
   50,   51,   52,
};
short yysindex[] = {                                   -234,
 -229,    0,  -77, -206, -199, -198, -201,   22,   23,  -55,
    0,  -53,  -58,    0,    0,    0,   33,   34,   35,   36,
    0,    0,    0,    0,    0,    0, -196,    0,    0,    0,
    0,    0,   19,   21,  -40, -193,  -40,  -40,    0,   26,
   42,    0,  -40,    0,  -40,  -40,    0,   21,   50,  -41,
  -20,    0,    0,   37,   51,  -13,   53,    0, -196,    0,
   58,    0,    0,    0,  -40,  -40,  -40,  -40,  -40,    7,
    0,    0,    0,    0,    0,    0,  -40,    7,    0,    0,
  -20,  -20,    0,    0,    0,   41,    0,    0, -175, -193,
    7,    0,   60,    0,    7,    0,
};
short yyrindex[] = {                                    102,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   44,    0,    0,    0,    0,
   45,    0,    0,    0,    0,    0,    0,  -34,    0,  -17,
  -29,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   46,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -24,   -4,    0,    0,    0,    0,    0,    0,  -44,   65,
    0,    0,    0,    0,    0,    0,
};
short yygindex[] = {                                      0,
   97,    0,  -38,    0,   49,    0,    0,    0,    0,    0,
    0,    0,  -35,   -7,   52,  -25,   20,    0,    0,    0,
    0,  -15,    2,
};
#define YYTABLESIZE 280
short yytable[] = {                                      45,
   23,   65,   57,   66,   46,   33,   50,   50,   50,   49,
   50,   44,   50,   44,   34,   44,   42,   60,   42,   61,
   42,   67,    1,   25,   50,   50,   68,   50,   53,   44,
   44,   87,   44,   85,   42,   42,   43,   42,   43,   89,
   43,   25,   25,    3,   25,    4,   75,   63,   76,   81,
   82,   88,   94,    5,   43,   43,   96,   43,    6,    8,
    7,    9,   33,   10,   11,   23,   22,   11,   83,   84,
   33,   14,   35,   36,   37,   38,   39,   42,   34,   21,
   34,   43,   53,   33,   58,   59,   48,   33,   48,   48,
   64,   70,   91,   78,   48,   69,   48,   62,   80,   90,
   95,    2,   28,   18,   30,   28,   12,   79,    0,   93,
    0,    0,    0,    0,    0,    0,   62,   62,   62,   62,
   48,    0,    0,    0,    0,    0,    0,    0,   48,   11,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   15,   16,   17,   18,   19,   20,    0,
    0,    0,    0,    0,   21,    0,    0,   34,   34,   34,
   34,   34,   34,    0,    0,    0,    0,    0,   34,    0,
    0,    0,   21,   44,   50,   50,   50,   50,    0,   44,
   44,   44,   44,    0,   42,   42,   42,   42,    0,    0,
    0,   25,   25,   25,   25,   71,   72,   73,   74,    0,
    0,    0,    0,    0,   43,   43,   43,   43,   15,   16,
   17,   18,   19,   20,    0,    0,    0,    0,    0,   21,
};
short yycheck[] = {                                      40,
   59,   43,   38,   45,   45,   13,   41,   42,   43,   35,
   45,   41,   47,   43,   59,   45,   41,   43,   43,   45,
   45,   42,  257,   41,   59,   60,   47,   62,   36,   59,
   60,   70,   62,   69,   59,   60,   41,   62,   43,   78,
   45,   59,   60,  273,   62,  123,   60,   46,   62,   65,
   66,   77,   91,  260,   59,   60,   95,   62,  258,  261,
  259,   40,   70,   41,  123,   59,  125,  123,   67,   68,
   78,  125,   40,   40,   40,   40,  273,   59,  123,  273,
  125,   61,   90,   91,   59,   44,   35,   95,   37,   38,
   41,   41,  268,   41,   43,   59,   45,   46,   41,   59,
   41,    0,   59,   59,   59,   41,   10,   59,   -1,   90,
   -1,   -1,   -1,   -1,   -1,   -1,   65,   66,   67,   68,
   69,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   77,  123,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  262,  263,  264,  265,  266,  267,   -1,
   -1,   -1,   -1,   -1,  273,   -1,   -1,  262,  263,  264,
  265,  266,  267,   -1,   -1,   -1,   -1,   -1,  273,   -1,
   -1,   -1,  273,  274,  269,  270,  271,  272,   -1,  269,
  270,  271,  272,   -1,  269,  270,  271,  272,   -1,   -1,
   -1,  269,  270,  271,  272,  269,  270,  271,  272,   -1,
   -1,   -1,   -1,   -1,  269,  270,  271,  272,  262,  263,
  264,  265,  266,  267,   -1,   -1,   -1,   -1,   -1,  273,
};
#define YYFINAL 2
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 274
#if YYDEBUG
char *yyname[] = {
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"MAINCLASS","STATIC","VOID","PUBLIC","MAIN","INT","FLOAT",
"PRINTLN","FOR","WHILE","IF","ELSE","EQ","NEQ","LE","GE","ID","NUM",
};
char *yyrule[] = {
"$accept : Program",
"Program : MAINCLASS ID '{' PUBLIC STATIC VOID MAIN '(' ')' CompStmt '}'",
"Program :",
"CompStmt : '{' StmtList '}'",
"StmtList : StmtList Stmt",
"StmtList :",
"Stmt : AssignStmt",
"Stmt : ForStmt",
"Stmt : WhileStmt",
"Stmt : IfStmt",
"Stmt : CompStmt",
"Stmt : Decleration",
"Stmt : NullStmt",
"Stmt : PRINTLN '(' Expr ')'",
"Decleration : Type IdList ';'",
"Type : INT",
"Type : FLOAT",
"IdList : DecId ',' IdList",
"IdList : DecId",
"DecId : ID",
"NullStmt : ';'",
"AssignStmt : AssignExpr ';'",
"AssignExpr : AssId '=' Expr",
"AssId : ID",
"Expr : AssignExpr",
"Expr : RVal",
"ForStmt : FOR '(' OpAssignExpr ';' OpBoolExpr ';' OpAssignExpr ')' Stmt",
"OpAssignExpr : AssignExpr",
"OpAssignExpr :",
"OpBoolExpr : BoolExpr",
"OpBoolExpr :",
"WhileStmt : WHILE '(' BoolExpr ')' Stmt",
"IfStmt : IF '(' BoolExpr ')' Stmt ElsePart",
"ElsePart : ELSE Stmt",
"ElsePart :",
"BoolExpr : Expr CompOp Expr",
"CompOp : EQ",
"CompOp : '<'",
"CompOp : '>'",
"CompOp : LE",
"CompOp : GE",
"CompOp : NEQ",
"RVal : RVal '+' Term",
"RVal : RVal '-' Term",
"RVal : Term",
"Term : Term '*' Factor",
"Term : Term '/' Factor",
"Term : Factor",
"Factor : '(' Expr ')'",
"Factor : '-' Factor",
"Factor : AssId",
"Factor : NUM",
};
#endif
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH 500
#endif
#endif
int yydebug;
int yynerrs;
int yyerrflag;
int yychar;
short *yyssp;
YYSTYPE *yyvsp;
YYSTYPE yyval;
YYSTYPE yylval;
short yyss[YYSTACKSIZE];
YYSTYPE yyvs[YYSTACKSIZE];
#define yystacksize YYSTACKSIZE
#line 440 "ssanal.y"

#include "funcs.c"
#include "main.c"
#line 282 "y.tab.c"
#define YYABORT goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR goto yyerrlab
int
yyparse()
{
    register int yym, yyn, yystate;
#if YYDEBUG
    register char *yys;
    extern char *getenv();

    if (yys = getenv("YYDEBUG"))
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = (-1);

    yyssp = yyss;
    yyvsp = yyvs;
    *yyssp = yystate = 0;

yyloop:
    if (yyn = yydefred[yystate]) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yyssp >= yyss + yystacksize - 1)
        {
            goto yyoverflow;
        }
        *++yyssp = yystate = yytable[yyn];
        *++yyvsp = yylval;
        yychar = (-1);
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;
#ifdef lint
    goto yynewerror;
#endif
yynewerror:
    yyerror("syntax error");
#ifdef lint
    goto yyerrlab;
#endif
yyerrlab:
    ++yynerrs;
yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yyssp, yytable[yyn]);
#endif
                if (yyssp >= yyss + yystacksize - 1)
                {
                    goto yyoverflow;
                }
                *++yyssp = yystate = yytable[yyn];
                *++yyvsp = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yyssp);
#endif
                if (yyssp <= yyss) goto yyabort;
                --yyssp;
                --yyvsp;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = (-1);
        goto yyloop;
    }
yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    yyval = yyvsp[1-yym];
    switch (yyn)
    {
case 1:
#line 48 "ssanal.y"
{
					negateSymbols(currDepth);
					currDepth--;
					rootNode = mkNode(astProgram,NULL,yyvsp[-1].node,NULL,NULL,NULL);
				}
break;
case 2:
#line 55 "ssanal.y"
{
					rootNode = mkNode(astEmptyProgram,NULL,NULL,NULL,NULL,NULL);
				}
break;
case 3:
#line 62 "ssanal.y"
{
					yyval.node = yyvsp[-1].node;
				}
break;
case 4:
#line 69 "ssanal.y"
{
					yyval.node = mkNode(astStmtList,NULL,yyvsp[-1].node,yyvsp[0].node,NULL,NULL);
				}
break;
case 5:
#line 74 "ssanal.y"
{
					currDepth++;
					yyval.node = mkNode(astEmptyStmtList,NULL,NULL,NULL,NULL,NULL);
				}
break;
case 6:
#line 82 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 7:
#line 87 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 8:
#line 92 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 9:
#line 97 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 10:
#line 102 "ssanal.y"
{
					negateSymbols(currDepth);
					currDepth--;
					yyval.node = yyvsp[0].node;
				}
break;
case 11:
#line 109 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 12:
#line 114 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 13:
#line 119 "ssanal.y"
{
					yyval.node = mkNode(astPrintStmt,NULL,yyvsp[-1].node,NULL,NULL,NULL);
				}
break;
case 14:
#line 126 "ssanal.y"
{
					yyval.node = mkNode(astDecleration,NULL,yyvsp[-2].node,yyvsp[-1].node,NULL,NULL);
				}
break;
case 15:
#line 132 "ssanal.y"
{
					p1 = mkSymbol("",INT);
					yyval.node = mkNode(astInt,NULL,NULL,NULL,NULL,NULL);
					pushStack(p1);
				}
break;
case 16:
#line 139 "ssanal.y"
{
					p1 = mkSymbol("",FLOAT);
					yyval.node = mkNode(astFloat,NULL,NULL,NULL,NULL,NULL);
					pushStack(p1);
				}
break;
case 17:
#line 148 "ssanal.y"
{
					yyval.node = mkNode(astIdList,NULL,yyvsp[-2].node,yyvsp[0].node,NULL,NULL);
				}
break;
case 18:
#line 153 "ssanal.y"
{
					yyval.node = mkNode(astIdList,NULL,yyvsp[0].node,NULL,NULL,NULL);
				}
break;
case 19:
#line 160 "ssanal.y"
{
					p1 = popStack();
					p2 = mkSymbol(yyvsp[0].ystr,p1->varType);
					p2->isVar = TRUE;
					p2->accessible = TRUE;
					p2->depth = currDepth;
					if(!addToTable(p2)) {
						strcpy(p2->errMsg,"Error: id already declared");
						yyval.node = mkNode(astError,p2,NULL,NULL,NULL,NULL);
					} else {
						yyval.node = mkNode(astDecId,p2,NULL,NULL,NULL,NULL);
						/*TO DO: add ID to symbTable*/
						pushStack(p1);
					}
				}
break;
case 20:
#line 179 "ssanal.y"
{
					yyval.node = mkNode(astNullStmt,NULL,NULL,NULL,NULL,NULL);
				}
break;
case 21:
#line 186 "ssanal.y"
{
					yyval.node = mkNode(astAssignStmt,NULL,yyvsp[-1].node,NULL,NULL,NULL);
				}
break;
case 22:
#line 193 "ssanal.y"
{
					p3 = popStack();
					p4 = popStack();
					/* if(p4->varType == INT && p3->varType == FLOAT ) {*/
					/* 	printf("%s\n", "Error: id and rValue not compatible types");*/
					/* 	exit(1);*/
					/* }*/
					p1 = mkSymbol("",p4->varType);
					pushStack(p1);
					yyval.node = mkNode(astAssignExp,NULL,yyvsp[-2].node,yyvsp[0].node,NULL,NULL);	
				}
break;
case 23:
#line 208 "ssanal.y"
{
					p1 = findId(yyvsp[0].ystr,currDepth);
					if(p1) {
						if(p1->accessible == TRUE)
							pushStack(p1);
						else {
							/*printf("id %s in wrong scope\n", p1->name);*/
							strcpy(p1->errMsg,"Error: id in wrong scope");
							yyval.node = mkNode(astError,p1,NULL,NULL,NULL,NULL);
							break;
						}
						yyval.node = mkNode(astAssId,p1,NULL,NULL,NULL,NULL);
					} else {
						p1 = mkSymbol("",INT);
						strcpy(p1->errMsg, "Error: Undeclered id was used");
						yyval.node = mkNode(astError,p1,NULL,NULL,NULL,NULL);
					}
				}
break;
case 24:
#line 228 "ssanal.y"
{
					/*nothing at the moment*/
					yyval.node = yyvsp[0].node;
				}
break;
case 25:
#line 234 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 26:
#line 241 "ssanal.y"
{
					yyval.node = mkNode(astForStmt,NULL,yyvsp[-6].node,yyvsp[-4].node,yyvsp[-2].node,yyvsp[0].node);
				}
break;
case 27:
#line 247 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 28:
#line 252 "ssanal.y"
{
					yyval.node = NULL;
				}
break;
case 29:
#line 259 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 30:
#line 264 "ssanal.y"
{
					yyval.node = NULL;
				}
break;
case 31:
#line 271 "ssanal.y"
{	
					yyval.node = mkNode(astWhileStmt,NULL,yyvsp[-2].node,yyvsp[0].node,NULL,NULL);
				}
break;
case 32:
#line 278 "ssanal.y"
{
					yyval.node = mkNode(astIfStmt,NULL,yyvsp[-3].node,yyvsp[-1].node,yyvsp[0].node,NULL);
				}
break;
case 33:
#line 285 "ssanal.y"
{
					yyval.node = mkNode(astElseStmt,NULL,yyvsp[0].node,NULL,NULL,NULL);
				}
break;
case 34:
#line 289 "ssanal.y"
{
					yyval.node = NULL;
				}
break;
case 35:
#line 296 "ssanal.y"
{
					yyval.node = mkNode(astBoolExp,NULL,yyvsp[-2].node,yyvsp[-1].node,yyvsp[0].node,NULL);
				}
break;
case 36:
#line 303 "ssanal.y"
{
					yyval.node = mkNode(astEqEqOp,NULL,NULL,NULL,NULL,NULL);
				}
break;
case 37:
#line 308 "ssanal.y"
{
					yyval.node = mkNode(astLessOp,NULL,NULL,NULL,NULL,NULL);
				}
break;
case 38:
#line 313 "ssanal.y"
{
					yyval.node = mkNode(astGreaterOp,NULL,NULL,NULL,NULL,NULL);
				}
break;
case 39:
#line 318 "ssanal.y"
{
					yyval.node = mkNode(astLessEqOp,NULL,NULL,NULL,NULL,NULL);
				}
break;
case 40:
#line 323 "ssanal.y"
{
					yyval.node = mkNode(astGreaterEqOp,NULL,NULL,NULL,NULL,NULL);
				}
break;
case 41:
#line 328 "ssanal.y"
{
					yyval.node = mkNode(astNotEqOp,NULL,NULL,NULL,NULL,NULL);
				}
break;
case 42:
#line 335 "ssanal.y"
{
					p3 = popStack();
					p4 = popStack();
					p1 = checkAdd(p3,p4);
					/* if(p1 != NULL)*/
						pushStack(p1);
					/* else {*/
					/* 	printf("incompatible operands\n");*/
					/* 	exit(1);*/
					/* }*/
					yyval.node = mkNode(astAddExp,NULL,yyvsp[-2].node,yyvsp[0].node,NULL,NULL);
				}
break;
case 43:
#line 349 "ssanal.y"
{
					p3 = popStack();
					p4 = popStack();
					p1 = checkSub(p3,p4);
					/* if(p1 != NULL)*/
						pushStack(p1);
					/* else {*/
					/* 	printf("incompatible operands\n");*/
					/* 	exit(1);*/
					/* }*/
					yyval.node = mkNode(astSubExp,NULL,yyvsp[-2].node,yyvsp[0].node,NULL,NULL);
				}
break;
case 44:
#line 363 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 45:
#line 370 "ssanal.y"
{
					p3 = popStack();
					p4 = popStack();
					p1 = checkMult(p3,p4);
					pushStack(p1);
					yyval.node = mkNode(astMultExp,NULL,yyvsp[-2].node,yyvsp[0].node,NULL,NULL);
				}
break;
case 46:
#line 379 "ssanal.y"
{
					p3 = popStack();
					p4 = popStack();
					p1 = checkDiv(p4,p3); /*division: p4/p3*/
					/* if(p1 != NULL)*/
						pushStack(p1);
					/* else {*/
					/* 	printf("incompatible operands\n");*/
					/* 	exit(1);*/
					/* }*/
					yyval.node = mkNode(astDivExp,NULL,yyvsp[-2].node,yyvsp[0].node,NULL,NULL);
				}
break;
case 47:
#line 393 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 48:
#line 400 "ssanal.y"
{
					yyval.node = yyvsp[-1].node;
				}
break;
case 49:
#line 405 "ssanal.y"
{
					/* if($2->nodeType == astNum) {
						if($2->nodSymbol->varType == INT)
							$2->nodSymbol->value.i = -$2->nodSymbol->value.i;
						else
							$2->nodSymbol->value.f = -$2->nodSymbol->value.f;
					} else {

					} */

					yyval.node = mkNode(astUminus,NULL,yyvsp[0].node,NULL,NULL,NULL);
				}
break;
case 50:
#line 419 "ssanal.y"
{
					yyval.node = yyvsp[0].node;
				}
break;
case 51:
#line 424 "ssanal.y"
{
					if(isInt(yyvsp[0].ystr)) {
						p3 = mkSymbol("",INT);
						p3->value.i = atoi(yyvsp[0].ystr);
					} else {
						p3 = mkSymbol("",FLOAT);
						p3->value.f = atof(yyvsp[0].ystr);
					}
					p3->isVar = FALSE;
					yyval.node = mkNode(astNum,p3,NULL,NULL,NULL,NULL);
					pushStack(p3);
				}
break;
#line 823 "y.tab.c"
    }
    yyssp -= yym;
    yystate = *yyssp;
    yyvsp -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yyssp = YYFINAL;
        *++yyvsp = yyval;
        if (yychar < 0)
        {
            if ((yychar = yylex()) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yyssp, yystate);
#endif
    if (yyssp >= yyss + yystacksize - 1)
    {
        goto yyoverflow;
    }
    *++yyssp = yystate;
    *++yyvsp = yyval;
    goto yyloop;
yyoverflow:
    yyerror("yacc stack overflow");
yyabort:
    return (1);
yyaccept:
    return (0);
}
