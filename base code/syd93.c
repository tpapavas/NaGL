#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "y.tab.h"

extern AstNode *TreeRoot;

/* ----------------------------------------------------------- */
/* ----- Definitions & Declarations for Code Generation ------ */
/* ----------------------------------------------------------- */

char boith_kod[81];
int AXinUse=FALSE;
long szdat;
FILE *femitd;
FILE *femitc;

/* ----------------------------------------------------------- */
/* ----- Definitions & Declarations for Code Optimisation ---- */
/* ----------------------------------------------------------- */

#define NEUTRAL    8
#define PUSHST     9
#define POPST     10
#define MOVEST    11
#define UNARST    12
#define BINARST   13
#define MUMOVEST  14
#define MBMOVEST  15
#define MMOVEST   16 

struct ib {
     int  State;
     char op[7];
     char opnd1[NAME_MAX];
     char opnd2[NAME_MAX];
     char instr[81];
} InstrBuf[5];

int BufIdx=0;

/* ----------------------------------------------------------- */
/* ---------------------- FUNCTIONS -------------------------- */
/* ----------------------------------------------------------- */

void kena(int n)
{  int i;
   
   for(i=0; i<n; i++) printf(" ");
}

void traverse(AstNode *p,int n)
{  int i;

   n=n+3;
   if(p)
   {
      switch (p->NodeType)
      {
         case astEmptyProgram: 
            kena(n); printf("astEmptyProgram\n"); 
         break;
         case astProgram: 
            kena(n); printf("astProgram\n"); 
         break;
         case astEmptyDeclSeq: 
            kena(n); printf("astEmptyDeclSeq\n"); 
         break;
         case astDeclSeq: 
            kena(n); printf("astDeclSeq\n"); 
         break;
         case astDecl: 
            kena(n); printf("astDecl\n"); 
         break;
         case INT: 
            kena(n); printf("INT\n"); 
         break;
         case astVarDcltr: 
            kena(n); printf("astVarDcltr\n"); 
         break;
         case astDcltrSeq: 
            kena(n); printf("astDcltrSeq\n"); 
         break;   
         case astEmptyStmtSeq: 
            kena(n); printf("astEmptyStmtSeq\n"); 
         break;
         case astStmtSeq:
            kena(n); printf("astStmtSeq\n"); 
         break;
         case astExprStmt: 
            kena(n); printf("astExprStmt\n"); 
         break;
         case astNullStmt: 
            kena(n); printf("astNullStmt\n"); 
         break;
         case astReadStmt: 
            kena(n); printf("astReadStmt\n"); 
         break;
         case astPrintStmt: 
            kena(n); printf("astPrintStmt\n"); 
         break;
         case astDecimConst:
            kena(n); printf("astDecimConst=%s\n",(p->SymbolNode)->name); 
         break;
         case astId: 
            kena(n); printf("astId=%s\n",(p->SymbolNode)->name); 
         break;
         case astMult:
            kena(n); printf("astMult\n"); 
         break;
         case astDiv: 
            kena(n); printf("astDiv\n"); 
         break;
         case astMod: 
            kena(n); printf("astMod\n"); 
         break;
         case astAdd: 
            kena(n); printf("astAdd\n"); 
         break;
         case astSub: 
            kena(n); printf("astSub\n"); 
         break;
         case astGreater: 
            kena(n); printf("astGreater\n"); 
         break;
         case astGrEq: 
            kena(n); printf("astGrEq\n"); 
         break;
         case astLess: 
            kena(n); printf("astLess\n"); 
         break;
         case astLeEq: 
            kena(n); printf("astLeEq\n"); 
         break;
         case astEq: 
            kena(n); printf("astEq\n"); 
         break;
         case astNotEq: 
            kena(n); printf("astNotEq\n"); 
         break;
         case astAssign: 
            kena(n); printf("astAssign\n"); 
         break;
         default: 
            printf("AGNOSTO=%d\n",p->NodeType);
      }
      for(i=0; i<4; i++) traverse(p->pAstNode[i],n);
   }
}

/* ---------------------------------------- */
/* ------- INCLUDE THE OPTIMISATION ------- */
/* ------------- FUNCTION ----------------- */
/* -- OPTIM1 DOES NO OPTIMISATION --------- */
/* -- OPTIM2 DOES PUSH & POP OPTIMISATION - */
/* -- OPTIM3 DOES MORE OPTIMISATION ------- */

#include "optim1"

/* ------------------------------------------------------------------------ */
/* ProcessProgram */

void ProcessProgram(AstNode *p, int lev)
{
   CodeGeneration(p->pAstNode[0],lev+1,FALSE,TRUE);
   CodeGeneration(p->pAstNode[1],lev+1,FALSE,FALSE);
}

/* ------------------------------------------------------------------------ */
/* ProcessDeclSeq */

void ProcessDeclSeq(AstNode *p, int lev, int lvalue)
{
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,TRUE);
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,FALSE);
}

/* ------------------------------------------------------------------------ */
/* ProcessDecl */

void ProcessDecl(AstNode *p, int lev, int lvalue)
{
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,TRUE);
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,FALSE);
}

/* ------------------------------------------------------------------------ */
/* ProcessVarDcltr */

void ProcessVarDcltr(AstNode *p)
{
   strcpy(boith_kod,"_");
   strcat(boith_kod,(p->SymbolNode)->name);
   strcat(boith_kod," sword ");
   if( (p->SymbolNode)->dcl_ptr )
   {
      if(((p->SymbolNode)->dcl_ptr)->dcl_type == ARRAY)
      {
         char buf[6];
         sprintf(buf,"%d",((p->SymbolNode)->dcl_ptr)->dim);
         strcat(boith_kod,buf);
         strcat(boith_kod," dup (?)\n");
      }
   }
   else
   {
      strcat(boith_kod,"? \n");
   }
   fputs(boith_kod,femitd);
}

/* ------------------------------------------------------------------------ */
/* ProcessDcltrSeq */

void ProcessDcltrSeq(AstNode *p, int lev, int lvalue)
{
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,TRUE);
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,FALSE);
}

/* ------------------------------------------------------------------------ */
/* ProcessStmtSeq */

void ProcessStmtSeq(AstNode *p, int lev, int lvalue)
{
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,TRUE);
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,FALSE);
}

/* ------------------------------------------------------------------------ */
/* ProcessExprStmt */
 
void ProcessExprStmt(AstNode *p, int lev, int lvalue) 
{
   CodeGeneration(p->pAstNode[0],lev+1,lvalue,FALSE);
}

/* ------------------------------------------------------------------------ */
/* ProcessNullStmt */

void ProcessNullStmt(void)
{
   emit_code('y',"nop","","","");
}

/* ------------------------------------------------------------------------ */
/* ProcessReadStmt */

void ProcessReadStmt(AstNode *p, int lev)
{  symbol *rhs;

   CodeGeneration(p->pAstNode[0],lev+1,TRUE,FALSE);
   rhs=pop_vs();
   emit_code('y',"call","_ReadInt","","");
   if( rhs->comes_from == ARRAYELEM ) 
   {
      if( (rhs->sclass == MEMORY )  || (rhs->sclass == REGISTER) ) 
      {
         emit_code('y',"pop","si","","");
      }
   }
   emit_code('y',"mov",rhs->name,"ax","");
   discard_symbol(rhs);
}

/* ------------------------------------------------------------------------ */
/* ProcessPrintStmt */

void ProcessPrintStmt(AstNode *p, int lev)
{  symbol *rhs;

   CodeGeneration(p->pAstNode[0],lev+1,FALSE,FALSE);
   rhs=pop_vs();
   switch( rhs->sclass ) 
   {
      case MEMORY:
      case CONSTANT:
         emit_code('y',"mov","ax",rhs->name,"");
         emit_code('y',"push","ax","","");
      break;
      case REGISTER:
         emit_code('y',"push",rhs->name,"","");
      break;
   }
   emit_code('y',"push","10","","");
   emit_code('y',"call","_PrintInt","","");
   emit_code('y',"add","sp","4","");
   discard_symbol(rhs);
}

/* ------------------------------------------------------------------------ */
/* ProcessDecimConst */

void ProcessDecimConst(AstNode *p) 
{  symbol *sn;

   sn=create_id(p->SymbolNode);
   sn->disposable=TRUE;
   sn->sclass=CONSTANT;
   sn->comes_from=INTCONST;
   push_vs(sn);
}

/* ------------------------------------------------------------------------ */
/* ProcessId */

void ProcessId(AstNode *p)
{  char h[NAME_MAX];
   symbol *sn;

   sn=create_id(p->SymbolNode);
   strcpy(h,"_");
   strcat(h,sn->name);
   strcpy(sn->name,h);
   sn->disposable=TRUE;
   sn->sclass=MEMORY;
   sn->comes_from=IDENTIFIER;
   push_vs(sn);
}

/* ------------------------------------------------------------------------ */
/* ProcessMult */

void ProcessMult(AstNode *p, int lev, int lvalue, int leftChild)
{  symbol *sn,*rhs,*lhs;

   CodeGeneration(p->pAstNode[0],lev+1,lvalue,TRUE);
   lhs=pop_vs();
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,FALSE);
   rhs=pop_vs();
   sn = new_symbol("");
   strcpy(sn->name,"ax");
   sn->disposable = TRUE;
   sn->typos = INT;
   sn->sclass = REGISTER;
   sn->comes_from = ARITHEXPR;
   switch(lhs->sclass) 
   {
      case MEMORY:
         if(rhs->sclass == MEMORY) 
         {
            emit_code('y',"mov","ax",lhs->name,"");
            emit_code('y',"imul",rhs->name,"","");
         }
         else if(rhs->sclass == CONSTANT) 
         {
            emit_code('y',"imul","ax",lhs->name,rhs->name);
         }
         else    /* --- REGISTER --- */
         {
            emit_code('y',"imul",rhs->name,lhs->name,"");
            strcpy(sn->name,rhs->name);
         }
      break;
      case REGISTER:
         emit_code('y',"ADYNATON","","","");
      break;
      case CONSTANT:
         if(rhs->sclass == CONSTANT) 
         {
            sn->timi = lhs->timi * rhs->timi;
            sprintf(sn->name,"%d",sn->timi);
            sn->sclass=CONSTANT;
         }
         else    /* -- MEMORY or REGISTER -- */
         {
            emit_code('y',"imul","ax",rhs->name,lhs->name);
         }
      break;
      case STACK:
         if(AXinUse) 
         {
            strcpy(sn->name,"dx");
            AXinUse=FALSE;
         }
         emit_code('y',"pop",sn->name,"","");
         emit_code('y',"imul",sn->name,rhs->name,"");
      break;
   }
   if(strcmp(sn->name,"ax") == 0) AXinUse=TRUE;
   if(leftChild) 
   {
      if( (sn->sclass) == REGISTER ) 
      {
         emit_code('y',"push",sn->name,"","");
         sn->sclass=STACK;
         if(strcmp(sn->name,"ax") == 0) AXinUse=FALSE;
      }
   }
   push_vs(sn);
   discard_symbol(lhs);
   discard_symbol(rhs);
}

/* ------------------------------------------------------------------------ */
/* ProcessDivMod */

void ProcessDivMod(AstNode *p, int lev, int lvalue, int leftChild)
{  symbol *sn,*rhs,*lhs;

   CodeGeneration(p->pAstNode[0],lev+1,lvalue,TRUE);
   lhs=pop_vs();
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,FALSE);
   rhs=pop_vs();
   sn=new_symbol("");
   strcpy(sn->name,"ax");
   if( (p->NodeType) == astMod )
      strcpy(sn->name,"dx");
   sn->disposable=TRUE;
   sn->typos=INT;
   sn->sclass=REGISTER;
   sn->comes_from=ARITHEXPR;
   switch(lhs->sclass) 
   {
      case MEMORY:
         if(rhs->sclass == MEMORY) 
         {
            emit_code('y',"mov","ax",lhs->name,"");
            emit_code('y',"cwd","","","");
            emit_code('y',"idiv",rhs->name,"","");
         }
         else if(rhs->sclass == CONSTANT) 
         {
            emit_code('y',"mov","ax",lhs->name,"");
            emit_code('y',"mov","di",rhs->name,"");
            emit_code('y',"cwd","","","");
            emit_code('y',"idiv","di","","");
         }
         else    /* --- REGISTER --- */
         {
            if( strcmp(rhs->name,"ax") == 0 ) 
            {
               emit_code('y',"mov","di","ax","");
               strcpy(rhs->name,"di");
            }
            emit_code('y',"mov","ax",lhs->name,"");
            emit_code('y',"cwd","","","");
            emit_code('y',"idiv",rhs->name,"","");
         }
      break;
      case REGISTER:
         emit_code('y',"ADYNATON","","","");
      break;
      case CONSTANT:
         if(rhs->sclass == CONSTANT) 
         {  int i1,i2;
             
            i1=lhs->timi;
            i2=rhs->timi;
            if( (p->NodeType) == astDiv ) 
            {
               sn->timi = i1/i2;
            }
            else if( (p->NodeType) == astMod ) 
            { 
               sn->timi = i1%i2;
            }
            sprintf(sn->name,"%d",sn->timi);
            sn->sclass=CONSTANT;
         }
         else     /* -- MEMORY or REGISTER -- */
         {
            if(rhs->sclass == REGISTER) 
            {
               if( strcmp(rhs->name,"ax") == 0 ) 
               {
                  emit_code('y',"mov","di","ax","");
                  strcpy(rhs->name,"di");
               }
            }
            emit_code('y',"mov","ax",lhs->name,"");
            emit_code('y',"cwd","","","");
            emit_code('y',"idiv",rhs->name,"","");
         }
      break;
      case STACK:
         if(rhs->sclass == REGISTER) 
         {
            if( strcmp(rhs->name,"ax") == 0 ) 
            {
               emit_code('y',"mov","di","ax","");
               strcpy(rhs->name,"di");
            }
            emit_code('y',"pop","ax","","");
         }
         else if(rhs->sclass == CONSTANT) 
         {
            emit_code('y',"pop","ax","","");
            emit_code('y',"mov","di",rhs->name,"");
            strcpy(rhs->name,"di");
            rhs->sclass=REGISTER;
         }
         emit_code('y',"cwd","","","");
         emit_code('y',"idiv",rhs->name,"","");
      break;
   }
   if(strcmp(sn->name,"ax") == 0) AXinUse=TRUE;
   if(leftChild) 
   {
      if( (sn->sclass) == REGISTER ) 
      {
         if( (p->NodeType) == astDiv ) 
         {
            emit_code('y',"push","ax","","");
            AXinUse=FALSE;
         }
         else if( (p->NodeType) == astMod )
            emit_code('y',"push","dx","","");
         sn->sclass=STACK;
      }
   }
   push_vs(sn);
   discard_symbol(lhs);
   discard_symbol(rhs);
}

/* ------------------------------------------------------------------------ */
/* ProcessAdd */

void ProcessAdd(AstNode *p, int lev, int lvalue, int leftChild)
{  symbol *sn,*rhs,*lhs;

   CodeGeneration(p->pAstNode[0],lev+1,lvalue,TRUE);
   lhs=pop_vs();
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,FALSE);
   rhs=pop_vs();
   sn=new_symbol("");
   strcpy(sn->name,"ax");
   sn->disposable=TRUE;
   sn->typos=INT;
   sn->sclass=REGISTER;
   sn->comes_from=ARITHEXPR;
   switch(lhs->sclass) 
   {
      case MEMORY:
         if(rhs->sclass == REGISTER) 
         {
            emit_code('y',"add",rhs->name,lhs->name,"");
            strcpy(sn->name,rhs->name);
         }
         else    /* --- MEMORY or CONSTANT --- */
         {
            emit_code('y',"mov","ax",lhs->name,"");
            emit_code('y',"add","ax",rhs->name,"");
         }
      break;
      case REGISTER:
         emit_code('y',"ADYNATON","","","");
      break;
      case CONSTANT:
         if(rhs->sclass == MEMORY) 
         {
            emit_code('y',"mov","ax",lhs->name,"");
            emit_code('y',"add","ax",rhs->name,"");
         }
         else if(rhs->sclass == CONSTANT) 
         {
            sn->timi = lhs->timi + rhs->timi;
            sprintf(sn->name,"%d",sn->timi);
            sn->sclass=CONSTANT;
         }
         else   /* --- REGISTER --- */
         {
            emit_code('y',"add",rhs->name,lhs->name,"");
            strcpy(sn->name,rhs->name);
         }
      break;
      case STACK:
         if(AXinUse) 
         {
            strcpy(sn->name,"dx");
            AXinUse=FALSE;
         }
         emit_code('y',"pop",sn->name,"","");
         emit_code('y',"add",sn->name,rhs->name,"");
      break;
   }
   if(strcmp(sn->name,"ax") == 0) AXinUse=TRUE;
   if(leftChild) 
   {
      if( (sn->sclass) == REGISTER ) 
      {
         emit_code('y',"push",sn->name,"","");
         sn->sclass=STACK;
         if(strcmp(sn->name,"ax") == 0) AXinUse=FALSE;
      }
   }
   push_vs(sn);
   discard_symbol(lhs);
   discard_symbol(rhs);
}

/* ------------------------------------------------------------------------ */
/* ProcessSub */

void ProcessSub(AstNode *p, int lev, int lvalue, int leftChild)
{  symbol *sn,*rhs,*lhs;

   CodeGeneration(p->pAstNode[0],lev+1,lvalue,TRUE);
   lhs=pop_vs();
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,FALSE);
   rhs=pop_vs();
   sn=new_symbol("");
   strcpy(sn->name,"ax");
   sn->disposable=TRUE;
   sn->typos=INT;
   sn->sclass=REGISTER;
   sn->comes_from=ARITHEXPR;
   switch(lhs->sclass) 
   {
      case MEMORY:
         if(rhs->sclass == REGISTER) 
         {
            if(AXinUse) strcpy(sn->name,"dx");
         }
         emit_code('y',"mov",sn->name,lhs->name,"");
         emit_code('y',"sub",sn->name,rhs->name,"");
      break;
      case REGISTER:
         emit_code('y',"ADYNATON","","","");
      break;
      case CONSTANT:
         if(rhs->sclass == MEMORY) 
         {
            emit_code('y',"mov","ax",lhs->name,"");
            emit_code('y',"sub","ax",rhs->name,"");
         }               
         else if(rhs->sclass == CONSTANT) 
         {
            sn->timi = lhs->timi - rhs->timi;
            sprintf(sn->name,"%d",sn->timi);
            sn->sclass=CONSTANT;
         }
         else    /* -- REGISTER -- */
         {
            if(AXinUse) strcpy(sn->name,"dx");
            emit_code('y',"mov",sn->name,lhs->name,"");
            emit_code('y',"sub",sn->name,rhs->name,"");
         }
      break;
      case STACK:
         if(AXinUse) 
         {
            strcpy(sn->name,"dx");
            AXinUse=FALSE;
         }
         emit_code('y',"pop",sn->name,"","");
         emit_code('y',"sub",sn->name,rhs->name,"");
      break;
   }
   if(strcmp(sn->name,"ax") == 0) AXinUse=TRUE;
   if(leftChild) 
   {
      if( (sn->sclass) == REGISTER ) 
      {
         emit_code('y',"push",sn->name,"","");
         sn->sclass=STACK;
         if(strcmp(sn->name,"ax") == 0) AXinUse=FALSE;
      }
   }
   push_vs(sn);
   discard_symbol(lhs);
   discard_symbol(rhs);
}

/* ------------------------------------------------------------------------ */
/* ProcessComp */

void ProcessComp(AstNode *p, int lev, int lvalue, int leftChild)
{  char onoma[NAME_MAX+1];
   symbol *sn,*rhs,*lhs;

   CodeGeneration(p->pAstNode[0],lev+1,lvalue,TRUE);
   lhs=pop_vs();
   CodeGeneration(p->pAstNode[1],lev+1,lvalue,FALSE);
   rhs=pop_vs();
   sn=new_symbol("");
   strcpy(sn->name,"ax");
   sn->disposable=TRUE;
   sn->typos=INT;
   sn->sclass=REGISTER;
   sn->comes_from=LOGICEXPR;
   switch(lhs->sclass) 
   {
      case MEMORY:
         if(rhs->sclass == MEMORY) 
         {
            emit_code('y',"mov","ax",lhs->name,"");
            emit_code('y',"cmp","ax",rhs->name,"");
         }
         else    /* -- CONSTANT or REGISTER -- */
         {
            emit_code('y',"cmp",lhs->name,rhs->name,"");
         }
      break;
      case REGISTER:
         emit_code('y',"ADYNATON","","","");
      break;
      case CONSTANT:
         strcpy(onoma,sn->name);
         if(rhs->sclass == REGISTER) 
         {
            if(AXinUse) 
            {
               strcpy(onoma,"dx");
               AXinUse=FALSE;
            }
         }
         emit_code('y',"mov",onoma,lhs->name,"");
         emit_code('y',"cmp",onoma,rhs->name,"");
      break;
      case STACK:
         strcpy(onoma,sn->name);
         if(AXinUse) 
         {
            strcpy(onoma,"dx");
            AXinUse=FALSE;
         }
         emit_code('y',"pop",onoma,"","");
         emit_code('y',"cmp",onoma,rhs->name,"");
      break;
   }
   switch(p->NodeType) 
   {
      case astGreater:
         strcpy(boith_kod,"setg");
      break;
      case astGrEq:
         strcpy(boith_kod,"setge");
      break;
      case astLess:
         strcpy(boith_kod,"setl");
      break;
      case astLeEq:
         strcpy(boith_kod,"setle");
      break;
      case astEq:
         strcpy(boith_kod,"sete");
      break;
      case astNotEq:
         strcpy(boith_kod,"setne");
   }
   emit_code('y',boith_kod,"al","","");
   emit_code('y',"mov","ah","0","");
   AXinUse=TRUE;
   if(leftChild) 
   {
      emit_code('y',"push","ax","","");
      sn->sclass=STACK;
      AXinUse=FALSE;
   }
   push_vs(sn);
   discard_symbol(lhs);
   discard_symbol(rhs);
}   

/* ------------------------------------------------------------------------ */
/* ProcessAssign */

void ProcessAssign(AstNode *p, int lev, int leftChild)
{  symbol *sn,*rhs,*lhs;

   CodeGeneration(p->pAstNode[0],lev+1,TRUE,TRUE);
   lhs=pop_vs();
   CodeGeneration(p->pAstNode[1],lev+1,FALSE,FALSE);
   rhs=pop_vs();
   sn=new_symbol("");
   sn->disposable=TRUE;
   sn->typos=INT;
   sn->comes_from=ASSIGNMENT;
   if( lhs->comes_from == ARRAYELEM ) 
   {
      if( (lhs->sclass == MEMORY )  || (lhs->sclass == REGISTER) ) 
      {
         emit_code('y',"pop","si","","");
      }
      lhs->sclass = MEMORY;
   }
   switch(lhs->sclass) 
   {
      case MEMORY:
         if(rhs->sclass == MEMORY) 
         {
            if( strcmp(lhs->name,rhs->name) != 0 ) 
            {
               emit_code('y',"mov","ax",rhs->name,"");
               emit_code('y',"mov",lhs->name,"ax","");
            }
            strcpy(sn->name,rhs->name);
            sn->sclass=MEMORY;
         }
         else if(rhs->sclass == CONSTANT) 
         {
            emit_code('y',"mov",lhs->name,rhs->name,"");
            strcpy(sn->name,rhs->name);
            sn->timi = rhs->timi;
            sn->sclass = CONSTANT;
         }
         else    /* -- REGISTER -- */
         {
            emit_code('y',"mov",lhs->name,rhs->name,"");
            strcpy(sn->name,rhs->name);
            sn->sclass = REGISTER;
         }
      break;
      case CONSTANT:
         emit_code('y',"ADYNATON","","","");
      break;
      case REGISTER:
         emit_code('y',"ADYNATON","","","");
      break;
      case STACK:
         emit_code('y',"pop","bx","","");
         if(rhs->sclass == MEMORY) 
         {
            emit_code('y',"mov","ax",rhs->name,"");
            emit_code('y',"mov","word ptr [bx]","ax","");
            strcpy(sn->name,rhs->name);
            sn->sclass = MEMORY;
         }
         else     /* --- CONSTANT or REGISTER --- */ 
         {
            emit_code('y',"mov","word ptr [bx]",rhs->name,"");
            strcpy(sn->name,rhs->name);
            sn->sclass=rhs->sclass;
         }
      break;
   }
   if(strcmp(sn->name,"ax") == 0) AXinUse=TRUE;
   if(leftChild) 
   {
      if(sn->sclass == REGISTER) 
      {
         emit_code('y',"push",sn->name,"","");
         sn->sclass = STACK;
         if(strcmp(sn->name,"ax") == 0) AXinUse = FALSE;
      }
   }
   push_vs(sn);
   discard_symbol(lhs);
   discard_symbol(rhs);
}

/* ------------------------------------------------------------------------ */
/* CodeGeneration */

void CodeGeneration(AstNode *p, int lev, int lvalue, int leftChild)
{  
   switch (p->NodeType)
   {
      case astEmptyProgram: 
      break;
      case astProgram: 
         ProcessProgram(p,lev);
      break;
      case astEmptyDeclSeq: 
      break;
      case astDeclSeq:
         ProcessDeclSeq(p,lev,lvalue);
      break;
      case astDecl:
         ProcessDecl(p,lev,lvalue);
      break;
      case INT:
      break;
      case astVarDcltr:
          ProcessVarDcltr(p);
      break;
      case astDcltrSeq:
         ProcessDcltrSeq(p,lev,lvalue);
      break;
      case astEmptyStmtSeq:
      break;
      case astStmtSeq: 
         ProcessStmtSeq(p,lev,lvalue);
      break;
      case astExprStmt: 
         ProcessExprStmt(p,lev,lvalue);
      break;
      case astNullStmt:
         ProcessNullStmt();
      break;
      case astReadStmt: 
         ProcessReadStmt(p,lev); 
      break;
      case astPrintStmt:
         ProcessPrintStmt(p,lev);
      break;
      case astDecimConst: 
         ProcessDecimConst(p); 
      break;
      case astId: 
         ProcessId(p);
      break;
      case astMult:
         ProcessMult(p,lev,lvalue,leftChild);
      break;
      case astDiv: 
      case astMod:
         ProcessDivMod(p,lev,lvalue,leftChild);
      break;
      case astAdd:
         ProcessAdd(p,lev,lvalue,leftChild);
      break;
      case astSub:
         ProcessSub(p,lev,lvalue,leftChild);
      break;
      case astGreater:
      case astGrEq: 
      case astLess: 
      case astLeEq: 
      case astEq: 
      case astNotEq: 
         ProcessComp(p,lev,lvalue,leftChild);
      break;
      case astAssign: 
         ProcessAssign(p,lev,leftChild);
      break;
      default:
         printf("AGNOSTO=%d\n",p->NodeType);
   }
}

void emitArxikaDat(void)
{  FILE *f;

   f=fopen("arx.cod","w");
   fputs("      .model small\n",f);
   fputs("      .stack 100h\n",f);
   fputs("      .586\n",f);
   if(szdat > 0) 
   { 
      fputs("; The Data Segment\n",f);
      fputs("      .data\n",f);
   }
   fclose(f);
}

void emitArxikaCod(void)
{  FILE *f;

   f=fopen("coda.cod","w");
   fputs("; The Code Segment\n",f);
   fputs("      .code\n",f);
   fputs("      extrn _PrintInt:proc\n",f);
   fputs("      extrn _ReadInt:proc\n",f);
   fputs("main proc\n",f);
   if(szdat > 0) 
   { 
      fputs("      mov ax,@data\n",f);
      fputs("      mov ds,ax\n",f);
   }
   fclose(f);
}

void emitTelikaCod(void)
{  FILE *f;

   f=fopen("telik.cod","w");
   fputs(";  Return to the Operating System\n",f);
   fputs("      mov  ax,4c00h\n",f);
   fputs("      int  21h\n",f);
   fputs("main endp\n",f);
   fputs("      end main\n",f);
   fclose(f);
}

void main(void)
{  AstNode *p;
   int lathos,i;
  
   Init_Hash_Table();
   Init_Cross_Link_Head();
   lathos=yyparse();
   if(!lathos) 
   {
      p=TreeRoot;
      traverse(p,-3);
      InstrBuf[BufIdx].State=NEUTRAL;
      femitd=fopen("kodikas.dat","w");
      femitc=fopen("kodikas.cod","w");
      CodeGeneration(p,0,FALSE,FALSE);
      for(i=1; i <= BufIdx; i++) fputs(InstrBuf[i].instr,femitc);
      szdat=ftell(femitd);
      fclose(femitc);
      fclose(femitd);
      emitArxikaDat();
      emitArxikaCod();
      emitTelikaCod();
   }
}
