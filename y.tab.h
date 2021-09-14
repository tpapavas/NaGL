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
typedef union {
	int yint;
	char ystr[80];
	AstNode* node;
} YYSTYPE;
extern YYSTYPE yylval;
