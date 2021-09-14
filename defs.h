#define NAME_LENGTH 40
#define STACK_SIZE 30
#define SYMB_TABLE_LENGTH 40
#define MAX_DEPTH 10
#define MAX_NUM_OF_VARS 1000
#define COMMAND_LENGTH 13

#define astProgram 400
#define astInt 401
#define astDecId 402
#define astIdList 403
#define astDecleration 404
#define astFloat 405
#define astStmtList 406
#define astEmptyProgram 407
#define astEmptyStmtList 408
#define astAssignStmt 409
#define astForStmt 410
#define astWhileStmt 411
#define astIfStmt 412
#define astNullStmt 413
#define astNum 414
#define astAssId 415
#define astBoolExp 416
#define astFact 417
#define astUminus 418
#define astMultExp 419
#define astDivExp 420
#define astAddExp 421
#define astSubExp 422
#define astAssignExp 423
#define astEqEqOp 424
#define astLessOp 425
#define astGreaterOp 426
#define astLessEqOp 427
#define astGreaterEqOp 428
#define astNotEqOp 429
#define astElseStmt 430
#define astBlockStmt 431
#define astPrintStmt 432
#define astError 433

#define TRUE 1
#define FALSE 0


char floatDeclerations[MAX_NUM_OF_VARS][120];
int currFlDec;
FILE *fOut;
int flag;
int whileFlag;
int printFlag;
int printCode;

typedef union {
	int i;
	float f;
} Value;

typedef struct Symbol_tag {
	char name[NAME_LENGTH+1];	//identification name (mainly for variables)
	int varType;				//type of variable (int/float)
	int rVal;					//true if it is right value

	int isVar;					//0 if not a variable, else <> 0
	struct Symbol_tag* nextInTable;

	Value value;				//for constants
	int scope;

	int depth; 					//number of outside blocks
	int accessible;				//true if this symbol can be accessed

	int codeId;					//var id in code

	char errMsg[80];

	struct Symbol_tag* crossLink;
} Symbol;

//Abstruct syntax tree node
typedef struct AstNode_tag {
	int nodeType;
	struct Symbol_tag *nodSymbol;
	struct AstNode_tag *pAstNode[4];
} AstNode;


AstNode* mkNode(int,Symbol*,AstNode*,AstNode*,AstNode*,AstNode*);
Symbol* mkSymbol(char*,int);

int addToTable(Symbol*);
Symbol* findId(char*,int);
int culcKey(char*);

int pushStack(Symbol*);
Symbol* popStack();

void negateSymbols(int);

Symbol* checkMult(Symbol*,Symbol*);
Symbol* checkDiv(Symbol*,Symbol*);
Symbol* checkAdd(Symbol*,Symbol*);
Symbol* checkSub(Symbol*,Symbol*);

//auxiliary functions
void logSymbTable();
int isInt(char*);

void traverseNodeForCode(AstNode*);
void normalizeFloat(float flt,int*,int*);