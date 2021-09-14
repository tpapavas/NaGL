#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "emit.c"

void dfs(AstNode* n,int t) {
	int tabs = t*3;
	char space[tabs+1];
	
	memset((char*)space,' ',tabs);
	space[tabs] = '\0';
	printf("%s", space);
	
	switch(n->nodeType) {
		case astProgram:
			printf("%s\n", "astProgram");
			break;

		case astDecleration:
			printf("%s\n", "astDecleration");
			break;

		case astIdList:
			printf("%s\n", "astIdList");
			break;

		case astDecId:
			printf("%s %s\n", "astDecId", n->nodSymbol->name);
			break;

		case astInt:
			printf("%s\n", "astInt");
			break;

		case astFloat:
			printf("%s\n", "astFloat");
			break;

		case astStmtList:
			printf("%s\n", "astStmtList");
			break;

		case astEmptyStmtList:
			printf("%s\n", "astEmptyStmtList");
			break;

		case astEmptyProgram:
			printf("%s\n", "astEmptyProgram");
			break;

		case astAssignStmt:
			printf("%s\n", "astAssignStmt");
			break;

		case astForStmt:
			printf("%s\n", "astForStmt");
			break;		

		case astWhileStmt:
			printf("%s\n", "astWhileStmt");
			break;

		case astIfStmt:
			printf("%s\n", "astIfStmt");
			break;

		case astNullStmt:
			printf("%s\n", "astNullStmt");
			break;

		case astNum:
			printf("%s = ", "astNum");
			if(n->nodSymbol->varType == INT)
				printf("%d\n", n->nodSymbol->value.i);
			else
				printf("%g\n", n->nodSymbol->value.f);
			break;

		case astAssId:
			printf("%s %s\n", "astAssId", n->nodSymbol->name);
			break;

		case astBoolExp:
			printf("%s\n", "astBoolExp");
			break;

		case astUminus:
			printf("%s\n", "astUminus");
			break;

		case astMultExp:
			printf("%s\n", "astMultExp");
			break;

		case astDivExp:
			printf("%s\n", "astDivExp");
			break;

		case astAddExp:
			printf("%s\n", "astAddExp");
			break;

		case astSubExp:
			printf("%s\n", "astSubExp");
			break;

		case astAssignExp:
			printf("%s\n", "astAssignExp");
			break;

		case astEqEqOp:
			printf("%s\n", "astEqEqOp");
			break;

		case astLessOp:
			printf("%s\n", "astLessOp");
			break;

		case astGreaterOp:
			printf("%s\n", "astGreaterOp");
			break;

		case astLessEqOp:
			printf("%s\n", "astLessEqOp");
			break;

		case astGreaterEqOp:
			printf("%s\n", "astGreaterEqOp");
			break;

		case astNotEqOp:
			printf("%s\n", "astNotEqOp");
			break;

		case astElseStmt:
			printf("%s\n", "astElseStmt");
			break;

		case astPrintStmt:
			printf("%s\n", "astPrintStmt");
			break;

		case astError:
			printf("%s\n", n->nodSymbol->errMsg);
			exit(1);
			break;

	}
	
	for(int i = 0; i < 4; i++)
		if(n->pAstNode[i] != NULL)
			dfs(n->pAstNode[i],t+1);
}

void genAssignCode(AstNode* n) {
	// Symbol* id;
	// Symbol* value;

	// char val[13];
	// char name[13];

	// char valPos[13];
	// char idPos[13];

	traverseNodeForCode(n->pAstNode[0]);

	// value = popStack();
	// sprintf(valPos,"STACK+%d",stackPos+1);
	// id = popStack();
	// sprintf(idPos,"STACK+%d",stackPos);
	
	// sprintf(name,"VAR%d",id->codeId);
	// emitCode("","LDA",valPos);
	// if(id->varType == INT && value->varType == FLOAT)
	// 	emitCode("","FIX","");
	// else if(id->varType == FLOAT && value->varType == INT)
	// 	emitCode("","FLOAT","");
	// emitCode("","STA",name);
	// pushStack(value);
	// sprintf(idPos,"STACK+%d",stackPos);
	// emitCode("","STA",idPos);
	// fprintf(fOut, "\n");
}

void genAssignExprCode(AstNode* n) {
	Symbol* id;
	Symbol* value;

	char val[13];
	char name[13];

	char valPos[13];
	char idPos[13];

	traverseNodeForCode(n->pAstNode[0]);
	traverseNodeForCode(n->pAstNode[1]);

	value = popStack();
	sprintf(valPos,"STACK+%d",stackPos+1);
	id = popStack();
	sprintf(idPos,"STACK+%d",stackPos);
	
	sprintf(name,"VAR%d",id->codeId);
	emitCode("","LDA",valPos);
	if(id->varType == INT && value->varType == FLOAT)
		emitCode("","FIX","");
	else if(id->varType == FLOAT && value->varType == INT)
		emitCode("","FLOT","");
	emitCode("","STA",name);
	pushStack(value);
	sprintf(idPos,"STACK+%d",stackPos);
	emitCode("","STA",idPos);
	fprintf(fOut, "\n");
}

void genProgramCode(AstNode* n) {
	traverseNodeForCode(n->pAstNode[0]);
}

void genStmtListCode(AstNode* n) {
	traverseNodeForCode(n->pAstNode[0]);
	traverseNodeForCode(n->pAstNode[1]);
}

void genDeclerationCode(AstNode* n) {
	traverseNodeForCode(n->pAstNode[0]);
	traverseNodeForCode(n->pAstNode[1]);
}

void genIdListCode(AstNode* n) {
	traverseNodeForCode(n->pAstNode[0]);
	traverseNodeForCode(n->pAstNode[1]);	
}

void genAssIdCode(AstNode* n) {
	Symbol* s = n->nodSymbol;
	pushStack(s);

	//MUST DEFINE LEFT - RIGHT PART

	char var[13];
	char pos[13];

	sprintf(var,"VAR%d",s->codeId);	
	emitCode("","LDA",var);

	sprintf(pos,"STACK+%d",stackPos);
	emitCode("","STA",pos);
	fprintf(fOut, "\n");

	return;
}

void genNumCode(AstNode* n) {
	Symbol* s = n->nodSymbol;
	pushStack(s);

	char val[13];
	char pos[13];

	if(s->varType == INT) {
		sprintf(val,"=%d=",s->value.i);

		emitCode("","LDA",val);
	} else {
		//assign value to float
		int multiplier = 0;
		int number = 0;
		normalizeFloat(s->value.f,&number,&multiplier);
		sprintf(val,"=%d=",multiplier);
		emitCode("","LDA",val);
		emitCode("","FLOT","");
		emitCode("","STA","FLT");
		fprintf(fOut, "\n");
		sprintf(val,"=%d=",number);
		emitCode("","LDA",val);
		emitCode("","FLOT","");
		emitCode("","FDIV","FLT");
	}

	sprintf(pos,"STACK+%d",stackPos);
	emitCode("","STA",pos);
	
	fprintf(fOut, "\n");
	return;
}

void genAddCode(AstNode* n) {
	Symbol* oprd1;
	Symbol* oprd2;
	Symbol* sum;
	char op1pos[13];
	char op2pos[13];

	traverseNodeForCode(n->pAstNode[0]);
	traverseNodeForCode(n->pAstNode[1]);

	oprd2 = popStack();
	sprintf(op2pos,"STACK+%d",stackPos+1);
	emitCode("","LDA",op2pos);
	emitCode("","STA","TEMP");
	oprd1 = popStack();
	sprintf(op1pos,"STACK+%d",stackPos+1);
	emitCode("","LDA",op1pos);

	if(oprd1 -> varType == INT && oprd2->varType == FLOAT) {
		emitCode("","FLOT","");
		emitCode("","FADD","TEMP");
	} else if(oprd1 -> varType == FLOAT && oprd2->varType == INT) {
		emitCode("","STA","TEMP2");
		emitCode("","LDA","TEMP");
		emitCode("","FLOT","");
		emitCode("","FADD","TEMP2");
	} else if(oprd1 -> varType == FLOAT && oprd2->varType == FLOAT) {
		emitCode("","FADD","TEMP");
	} else {
		emitCode("","ADD","TEMP");
		emitCode("","JOV","TELOS");
	}
	sum = checkAdd(oprd1,oprd2);
	pushStack(sum);

	sprintf(op1pos,"STACK+%d",stackPos);
	emitCode("","STA",op1pos);
	fprintf(fOut, "\n");

}

void genSubCode(AstNode* n) {
	Symbol* oprd1;
	Symbol* oprd2;
	Symbol* diff;
	char op1pos[13];
	char op2pos[13];

	traverseNodeForCode(n->pAstNode[0]);
	traverseNodeForCode(n->pAstNode[1]);

	oprd2 = popStack();
	sprintf(op2pos,"STACK+%d",stackPos+1);
	emitCode("","LDA",op2pos);
	emitCode("","STA","TEMP");
	oprd1 = popStack();
	sprintf(op1pos,"STACK+%d",stackPos+1);
	emitCode("","LDA",op1pos);

	if(oprd1 -> varType == INT && oprd2->varType == FLOAT) {
		emitCode("","FLOT","");
		emitCode("","FSUB","TEMP");
	} else if(oprd1 -> varType == FLOAT && oprd2->varType == INT) {
		emitCode("","STA","TEMP2");
		emitCode("","LDA","TEMP");
		emitCode("","FLOT","");
		emitCode("","FSUB","TEMP2");
	} else if(oprd1 -> varType == FLOAT && oprd2->varType == FLOAT) {
		emitCode("","FSUB","TEMP");
	} else {
		emitCode("","SUB","TEMP");
		emitCode("","JOV","TELOS");
	}
	diff = checkSub(oprd1,oprd2);
	pushStack(diff);

	sprintf(op1pos,"STACK+%d",stackPos);
	emitCode("","STA",op1pos);
	fprintf(fOut, "\n");
}

void genMultCode(AstNode* n) {
	Symbol* oprd1;
	Symbol* oprd2;
	Symbol* result;
	char op1pos[13];
	char op2pos[13];

	traverseNodeForCode(n->pAstNode[0]);
	traverseNodeForCode(n->pAstNode[1]);

	oprd2 = popStack();
	sprintf(op2pos,"STACK+%d",stackPos+1);
	emitCode("","LDA",op2pos);
	emitCode("","STA","TEMP");
	oprd1 = popStack();
	sprintf(op1pos,"STACK+%d",stackPos+1);
	emitCode("","LDA",op1pos);

	if(oprd1 -> varType == INT && oprd2->varType == FLOAT) {
		emitCode("","FLOT","");
		emitCode("","FMUL","TEMP");
	} else if(oprd1 -> varType == FLOAT && oprd2->varType == INT) {
		emitCode("","STA","TEMP2");
		emitCode("","LDA","TEMP");
		emitCode("","FLOT","");
		emitCode("","FMUL","TEMP2");
	} else if(oprd1 -> varType == FLOAT && oprd2->varType == FLOAT) {
		emitCode("","FMUL","TEMP");
	} else {
		emitCode("","MUL","TEMP");
		emitCode("","JANZ","TELOS");
	}
	result = checkMult(oprd1,oprd2);
	pushStack(result);

	sprintf(op1pos,"STACK+%d",stackPos);
	if(oprd1 -> varType == INT && oprd2->varType == INT)
		emitCode("","STX",op1pos);
	else
		emitCode("","STA",op1pos);
	fprintf(fOut, "\n");
	return;
}

void genDivCode(AstNode* n) {
	Symbol* oprd1;
	Symbol* oprd2;
	Symbol* quotient;
	char op1pos[13];
	char op2pos[13];

	traverseNodeForCode(n->pAstNode[0]);
	traverseNodeForCode(n->pAstNode[1]);

	oprd2 = popStack();
	sprintf(op2pos,"STACK+%d",stackPos+1);
	emitCode("","LDA",op2pos);
	emitCode("","STA","TEMP");
	oprd1 = popStack();
	sprintf(op1pos,"STACK+%d",stackPos+1);
	emitCode("","LDA",op1pos);

	if(oprd1 -> varType == INT && oprd2->varType == INT) {
		emitCode("","SRAX","5");
		emitCode("","DIV","TEMP");
	} else {
		if(oprd1 -> varType == INT && oprd2->varType == FLOAT) {
			emitCode("","FLOT","");
		} else if(oprd1 -> varType == FLOAT && oprd2->varType == INT) {
			emitCode("","STA","TEMP2");
			emitCode("","LDA","TEMP");
			emitCode("","FLOT","");
			emitCode("","STA","TEMP");
			emitCode("","LDA","TEMP2");
			// emitCode("","FDIV","TEMP2");
		} 
		emitCode("","FDIV","TEMP");
	}
	emitCode("","JOV","TELOS");
	quotient = checkDiv(oprd1,oprd2);
	pushStack(quotient);

	sprintf(op1pos,"STACK+%d",stackPos);
	emitCode("","STA",op1pos);
	fprintf(fOut, "\n");
	return;
}

void genIfCode(AstNode* n) {
	char afterElsePos[13];
	char afterIfPos[13];

	traverseNodeForCode(n->pAstNode[0]);

	//read if part
	traverseNodeForCode(n->pAstNode[1]);

	sprintf(afterElsePos,"%dF",flag+1);
	emitCode("","JMP",afterElsePos);
	

	sprintf(afterIfPos,"%dH",flag);
	emitCode(afterIfPos,"NOP","");

	//read else part
	traverseNodeForCode(n->pAstNode[2]);

	//pending

	sprintf(afterIfPos,"%dH",flag+1);
	emitCode(afterIfPos,"NOP","");

	flag--;

	return;
}

void genBoolExpCode(AstNode* n) {
	Symbol* leftOp;
	Symbol* rightOp;

	char posR[13];
	char posL[13];

	traverseNodeForCode(n->pAstNode[0]);
	traverseNodeForCode(n->pAstNode[2]);

	rightOp = popStack();
	sprintf(posR,"STACK+%d",stackPos+1);
	leftOp = popStack();
	sprintf(posL,"STACK+%d",stackPos+1);

	emitCode("","LDA",posR);
	emitCode("","STA","TEMP");

	emitCode("","LDA",posL);

	if(leftOp->varType == INT && rightOp->varType == INT)
		emitCode("","CMPA","TEMP");
	else {
		if(leftOp->varType == INT && rightOp->varType == FLOAT) {
			emitCode("","FLOT","");
		} else 	if(leftOp->varType == FLOAT && rightOp->varType == INT) {
			emitCode("","STA","TEMP2");
			emitCode("","LDA","TEMP");
			emitCode("","FLOT","");
			emitCode("","STA","TEMP");
			emitCode("","LDA","TEMP2");
		}
		emitCode("","FCMP","TEMP");
	}

	traverseNodeForCode(n->pAstNode[1]);

	return;
}

void genElseCode(AstNode* n) {
	char pos[13];
	char afterElsePos[13];
	
	traverseNodeForCode(n->pAstNode[0]);
}

void genEqEqCode(AstNode* n) {
	char pos[13];

	sprintf(pos,"%dF",++flag);
	emitCode("","JNE",pos);
	return;
}

void genNotEqCode(AstNode* n) {
	char pos[13];

	sprintf(pos,"%dF",++flag);
	emitCode("","JE",pos);
	return;
}

void genGreaterCode(AstNode* n) {
	char pos[13];

	sprintf(pos,"%dF",++flag);
	emitCode("","JLE",pos);
	return;	
}

void genLessEqCode(AstNode* n) {
	char pos[13];

	sprintf(pos,"%dF",++flag);
	emitCode("","JG",pos);
	return;	
}

void genLessCode(AstNode* n) {
	char pos[13];

	sprintf(pos,"%dF",++flag);
	emitCode("","JGE",pos);
	return;	
}

void genGreaterEqCode(AstNode* n) {
	char pos[13];

	sprintf(pos,"%dF",++flag);
	emitCode("","JL",pos);
	return;	
}

void genWhileCode(AstNode* n) {
	char whilePos[13];
	char afterElsePos[13];
	char afterIfPos[13];


	sprintf(whilePos,"J%d",whileFlag++);
	emitCode(whilePos,"NOP","");

	traverseNodeForCode(n->pAstNode[0]);

	// //read if part
	traverseNodeForCode(n->pAstNode[1]);

	// // sprintf(afterElsePos,"%dF",flag+1);
	// // emitCode("","JMP",afterElsePos);
	
	sprintf(whilePos,"J%d",whileFlag-1);
	emitCode("","JMP",whilePos);

	sprintf(afterIfPos,"%dH",flag);
	emitCode(afterIfPos,"NOP","");

	flag--;
	whileFlag--;

	return;
}

void genForCode(AstNode* n) {
	char whilePos[13];
	char afterElsePos[13];
	char afterIfPos[13];

	traverseNodeForCode(n->pAstNode[0]);

	sprintf(whilePos,"J%d",whileFlag++);
	emitCode(whilePos,"NOP","");

	traverseNodeForCode(n->pAstNode[1]);

	// //read if part
	traverseNodeForCode(n->pAstNode[3]);

	// // sprintf(afterElsePos,"%dF",flag+1);
	// // emitCode("","JMP",afterElsePos);

	traverseNodeForCode(n->pAstNode[2]);
	
	sprintf(whilePos,"J%d",whileFlag-1);
	emitCode("","JMP",whilePos);

	sprintf(afterIfPos,"%dH",flag);
	emitCode(afterIfPos,"NOP","");

	flag--;
	whileFlag--;

	return;
}

void genPrintCode(AstNode* n) {
	Symbol* s;

	char pos[13];
	char positivePos[13];

	char pros[COMMAND_LENGTH];
	char great[COMMAND_LENGTH];
	char common[COMMAND_LENGTH];
	char big[COMMAND_LENGTH];
	char r1[COMMAND_LENGTH];
	char j1[COMMAND_LENGTH];
	char sst[COMMAND_LENGTH];
	char yeah[COMMAND_LENGTH];
	char mpos[COMMAND_LENGTH];
	char nneg[COMMAND_LENGTH];
	char mneg[COMMAND_LENGTH];
	char next[COMMAND_LENGTH];

	traverseNodeForCode(n->pAstNode[0]);


	sprintf(pos,"STACK+%d",stackPos);
	sprintf(positivePos,"M%d",printFlag);

	s = popStack();

////////////////////////////////////
	// if(n->pAstNode[0]->nodSymbol->varType == INT) {
	if(s->varType == INT) {
		emitCode("","LDA",pos);
		emitCode("","CHAR","");
		emitCode("","STA","OUTP+1");
		emitCode("","STX","OUTP+2");
		
		emitCode("","JANN",positivePos);
		emitCode("","LDA","MINUS");
		emitCode("","STA","OUTP");
		
		emitCode(positivePos,"OUT","OUTP(18)");
		emitCode("","JBUS","*(18)");

		emitCode("","LDA","MIDEN");
		emitCode("","STA","OUTP+1");
		emitCode("","STA","OUTP+2");

	} else {
		sprintf(pros,"PROS%d",printFlag);
		sprintf(great,"GREAT%d",printFlag);
		sprintf(common,"COMMON%d",printFlag);
		sprintf(big,"BIG%d",printFlag);
		sprintf(r1,"R1%d",printFlag);
		sprintf(j1,"J1%d",printFlag);
		sprintf(sst,"SST%d",printFlag);
		sprintf(yeah,"YEAH%d",printFlag);
		sprintf(mpos,"MPOS%d",printFlag);
		sprintf(nneg,"NNEG%d",printFlag);
		sprintf(mneg,"MNEG%d",printFlag);
		sprintf(next,"NEXT%d",printFlag);


		// emitCode("","LDA","=100=");
		// emitCode("","FLOT","");
		// emitCode("","STA","TEMP");

		// emitCode("","LDA","=5721122=");
		// emitCode("","FLOT","");

		// // if(mul)
		// emitCode("","FMUL","TEMP");
		// // else
		// // emitCode("","FDIV","TEMP");

		emitCode("","LDA",pos);
		emitCode("","STA","TEMP");

		emitCode("","JANN",pros);
		emitCode("","STA","TEMP");
		emitCode("","LDAN","TEMP");
		emitCode("","LDX","MINUS");
		emitCode("","STX","OUTP");

		emitCode(pros,"STA","TEMP");

		emitCode("","CMPA","C2");
		emitCode("","JL",common);
		emitCode(great,"ENT4","1");
		emitCode("","ST4","LARGE");

		emitCode(common,"ENT1","0");

		emitCode("","LDA","TEMP");		//RA = xxxxx,xxxxxx

		emitCode("","J4Z",r1);
		emitCode(big,"FCMP","C2");

		emitCode("","JL",j1);
		emitCode("","INC1","-1");
		emitCode("","FDIV","TENF");

		emitCode("","JMP",big);

		emitCode(r1,"FCMP","C");

		emitCode("","JG",j1);
		emitCode("","INC1","1");
		emitCode("","FMUL","TENF");

		emitCode("","JMP",r1);
		emitCode(j1,"NOP","");

		emitCode("","ST1","N");
		emitCode("","FIX","");
		emitCode("","ENTX","0");

		emitCode("","CHAR","");
		emitCode("","STA","NUM1");
		emitCode("","STX","NUM2");

		emitCode("","SRC","4");

		emitCode("","ENT2","10");
		emitCode(sst,"CMPA","N30(5:5)");
		emitCode("","JNE",yeah);
		emitCode("","SLC","1");
		emitCode("","INC2","-1");
		emitCode("","JMP",sst);
		emitCode(yeah,"ST1","LENGTH");

		emitCode("","ENN1","0,1");
		emitCode("","INC2","0,1");
		emitCode("","ST2","M");

		emitCode("","ENT1","1");	//FOR OUTPUT + THIS
		emitCode("","ENT2","1");	//FOR 1-5
		emitCode("","ENT3","1");	//	FOR N

		emitCode("","LD4","M");
		emitCode("","J4NP",mneg);

		emitCode("","LD5","N");
		emitCode("","J5NP",nneg);
		emitCode(mpos,"ST4","LIMIT");
		emitCode("","JMP","INT");
		emitCode("","JMP","COM");
		emitCode("","JMP","DE");
		emitCode("","JMP",next);

		emitCode(nneg,"NOP","");
		emitCode("","ENT4","7");
		emitCode("","ST4","LIMIT");
		emitCode("","JMP","INT");
		emitCode("","LD4","M");
		emitCode("","INC4","-7");
		emitCode("","ST4","LIMIT");
		emitCode("","LDA","ZERO");
		emitCode("","LDX","ZERO");
		emitCode("","ENT3","1");
		emitCode("","JMP","INT");
		emitCode("","JMP","COM");
		emitCode("","ENT4","1");
		emitCode("","ST4","LIMIT");
		emitCode("","ENT3","1");
		emitCode("","JMP","INT");
		emitCode("","JMP",next);

		emitCode(mneg,"NOP","");
		emitCode("","STA","NUM3");
		emitCode("","STX","NUM4");
		emitCode("","LDA","ZERO");
		emitCode("","LDX","ZERO");
		emitCode("","ENT4","1");
		emitCode("","ST4","LIMIT");
		emitCode("","JMP","INT");
		emitCode("","JMP","COM");
		emitCode("","LD4N","M");
		emitCode("","ST4","LIMIT");
		emitCode("","ENT3","1");
		emitCode("","JMP","INT");
		emitCode("","ENT3","1");
		emitCode("","ENT4","7");
		emitCode("","ST4","LIMIT");
		emitCode("","LDA","NUM3");
		emitCode("","LDX","NUM4");
		emitCode("","JMP","INT");

		emitCode(next,"JMP","AFTER");
		emitCode("","JMP","PRINT");
		emitCode("","ENT4","0");

		printCode = TRUE;
	}
////////////////////////////////////

	printFlag++;

	return;
}

void genUminusCode(AstNode* n) {
	char pos[13];

	traverseNodeForCode(n->pAstNode[0]);

	sprintf(pos,"STACK+%d",stackPos);

	emitCode("","LDAN",pos);
	emitCode("","STA",pos);
}

void traverseNodeForCode(AstNode* n) {
	if(n)
	switch(n->nodeType) {
		case astProgram:
			genProgramCode(n);
			break;

		case astDecleration:
			genDeclerationCode(n);
			break;

		case astIdList:
			genIdListCode(n);
			break;

		case astDecId:
			//do nothing
			break;

		case astInt:
			//do nothing
			break;

		case astFloat:
			//do nothing
			break;

		case astStmtList:
			genStmtListCode(n);
			break;

		case astEmptyStmtList:
			//do nothing
			break;

		case astEmptyProgram:
			//do nothing
			break;

		case astAssignStmt:
			genAssignCode(n);
			stackPos--;
			break;

		case astForStmt:
			genForCode(n);
			break;		

		case astWhileStmt:
			genWhileCode(n);
			break;

		case astIfStmt:
			genIfCode(n);
			break;

		case astElseStmt:
			genElseCode(n);
			break;

		case astPrintStmt:
			genPrintCode(n);
			break;

		case astNullStmt:
			break;

		case astNum:
			genNumCode(n);
			break;

		case astAssId:
			genAssIdCode(n);
			break;

		case astBoolExp:
			genBoolExpCode(n);
			break;

		case astUminus:
			genUminusCode(n);
			break;

		case astMultExp:
			genMultCode(n);
			break;

		case astDivExp:
			genDivCode(n);
			break;

		case astAddExp:
			genAddCode(n);
			break;

		case astSubExp:
			genSubCode(n);
			break;

		case astAssignExp:
			genAssignExprCode(n);
			break;

		case astEqEqOp:
			genEqEqCode(n);
			break;

		case astLessOp:
			genLessCode(n);
			break;

		case astGreaterOp:
			genGreaterCode(n);
			break;

		case astLessEqOp:
			genLessEqCode(n);
			break;

		case astGreaterEqOp:
			genGreaterEqCode(n);
			break;

		case astNotEqOp:
			genNotEqCode(n);
			break;
	}
	
	return;
}

void mkDeclerationCode() {
	char prt1[13];		//symbol for memory reference
	char prt2[13];		//command
	char prt3[13];		//command's parameter

	char line[38];
	char floatDecCommands[120];

	currFlDec = -1;

	int id = 0;
	
	Symbol* s;

	_emitCode("MINUS","ALF","    -");
	_emitCode("COMMA","ALF","    ,");
	for(int i = 0; i < SYMB_TABLE_LENGTH; i++) {
		for(s = symbTable[i]; s != NULL; s = s->nextInTable) {
			s->codeId = id++;
			sprintf(prt1,"VAR%d",s->codeId);
			strcpy(prt2,"CON");
			strcpy(prt3,"0");
			emitCode(prt1,prt2,prt3);

			if(s->varType == FLOAT) {
				currFlDec++;
				emitTempCode(line,"","ENTA","0");
				strcpy(floatDecCommands,line);
				
				emitTempCode(line,"","FLOT","");
				strcat(floatDecCommands,line);
				
				emitTempCode(line,"","STA",prt1);
				strcat(floatDecCommands,line);

				strcpy(floatDeclerations[currFlDec],floatDecCommands);
			}
		}
	}
	emitCode("TEMP","CON","0");
	emitCode("TEMP2","CON","0");
	emitCode("FLT","CON","0");
	emitCode("TENF","CON","10");
	emitCode("C","CON","262144");
	emitCode("C2","CON","16777216");
	emitCode("ZERO","CON","0");
	emitCode("LARGE","CON","0");
	emitCode("N","CON","0");
	emitCode("NUM1","CON","0");
	emitCode("NUM2","CON","0");
	emitCode("N30","CON","30");
	emitCode("LENGTH","CON","10");
	emitCode("M","CON","0");
	emitCode("LIMIT","CON","0");
	emitCode("NUM3","CON","0");
	emitCode("NUM4","CON","0");
	emitCode("POS","CON","0");
	emitCode("POS1","CON","0");
	emitCode("CFLAG","CON","1");
	emitCode("DECFLAG","CON","0");
	emitCode("CNT","CON","5");
	emitCode("MIDEN","CON","0");
	emitCode("STACK","ORIG","*+30");
	emitCode("OUTP","ORIG","*+24");
	fprintf(fOut, "\n");
	return;
}

void emitPrintCode() {

	emitCode("","JMP","PREEND");
	emitCode("INT","STJ","POS(4:5)");    
    emitCode("","LD4","POS");
	emitCode("A3","CMP3","LIMIT") ;     
    emitCode("","JG","A1");
	emitCode("COPY","STA","OUTP,1(5:5)");
    emitCode("","LD6","CFLAG");     
    emitCode("","J6Z","AF");    
    emitCode("","STA","NUM1");   
  	emitCode("","STX","NUM2");     
	emitCode("AF","NOP","");           
   	emitCode("","LDA","OUTP,1");
   	emitCode("","INC2","1");  
   	emitCode("","CMP2","=5=");        
    emitCode("","JLE","A2");         
    emitCode("","INC1","1");          
   	emitCode("","ENT2","1");           
    emitCode("","JMP","A5");        
	emitCode("A2","SLA","1");           
    emitCode("","STA","OUTP,1");     
	emitCode("A5","INC3","1");          
    emitCode("","LDA","NUM1");        
  	emitCode("","SLC","1");       
    emitCode("","JMP","A3");       
	emitCode("A1","JMP","0,4");         
	emitCode("COM","ENT3","1");           
    emitCode("","STJ","POS(4:5)");   
    emitCode("","LD4","POS" );       
    emitCode("","LD6","CFLAG");      
    emitCode("","J6NP","DE");       
    emitCode("","LDA","COMMA");       
    emitCode("","ENT6","1");          
    emitCode("","ST6","LIMIT");       
    emitCode("","ENT6","0");          
    emitCode("","ST6","CFLAG");      
    emitCode("","JMP","COPY");    
	emitCode("DE","ENT3","1");          
   	emitCode("","STJ","POS(4:5)");    
    emitCode("","LD4","POS");      
   	emitCode("","LD6","CFLAG");      
    emitCode("","INC6","-1");         
   	emitCode("","ST6","CFLAG");     
   	emitCode("","LD6","DECFLAG");     
    emitCode("","J6NZ","AFTER");      
    emitCode("","LDA","NUM1");        
   	emitCode("","LDX","NUM2");      
    emitCode("","SLC","1");        
    emitCode("","ENT6","1");          
    emitCode("","ST6","DECFLAG");     
    emitCode("","LD6","N" );         
    emitCode("","ST6","LIMIT");       
    emitCode("","JMP","COPY");      
	emitCode("SHIFT","STJ","POS1(4:5)");    
    emitCode("","LD4","POS1");      
    emitCode("","LD5","CNT");      
   	emitCode("","LDA","OUTP,1");    
	emitCode("WHILE","CMPA","MIDEN(1:1)");  
    emitCode("","JNE","HERE");     
    emitCode("","J5Z","HERE");      
    emitCode("","SLA","1");         
    emitCode("","INC5","-1");          
    emitCode("","JMP","WHILE");

	emitCode("HERE","STA","OUTP,1");      
    emitCode("","JMP","0,4");

	emitCode("INIT","STJ","POS1(4:5)");
	emitCode("","LD6","POS1");
	emitCode("","ENT1","0");
	emitCode("","ENT2","0");
	emitCode("","ENT3","0");
	emitCode("","ENT5","1");
	emitCode("","ST5","CFLAG");
	emitCode("","ENT5","5");
	emitCode("","ST5","CNT");
	emitCode("","ENT5","0");
	emitCode("","ST5","DECFLAG");

	emitCode("","LDA","MIDEN");
	emitCode("","ENT5","24");
	emitCode("","ENT3","0");
	emitCode("REPLAY","J5Z","FIN");
	emitCode("","STA","OUTP,3");
	emitCode("","INC3","1");
	emitCode("","INC5","-1");
	emitCode("","JMP","REPLAY");
	emitCode("FIN","NOP","");
	emitCode("","JMP","0,6");

	emitCode("AFTER","STJ","POS(4:5)");
	emitCode("","JMP","SHIFT");
	emitCode("","LD4","POS");
	emitCode("","JMP","0,4");

	emitCode("PRINT","STJ","POS(4:5)");
	emitCode("","LD4","POS");
	emitCode("","OUT","OUTP(18)");  
    emitCode("","JBUS","*(18)" );  
    emitCode("","JMP","INIT");
	emitCode("","JMP","0,4");

	emitCode("PREEND","NOP","");
}

void mkProgramCode() {
	char startingLine[37] = "START       NOP         ";
	char preendingLine[37] = "TELOS       HLT         ";
	char endingLine[37] = "            END         START";

	//code for beginning of program (after declerations) 
	fprintf(fOut, "%s\n", startingLine);

	//code for assigning 0.0f to float variables
	for(int i = 0; i < MAX_NUM_OF_VARS; i++)
		if(floatDeclerations[i][0] != '\0')
			fprintf(fOut, "%s\n", floatDeclerations[i]);
		else
			break;


	emitCode("","LDA","TENF");
	emitCode("","FLOT","");
	emitCode("","STA","TENF");

	emitCode("","LDA","C2");
	emitCode("","FLOT","");
	emitCode("","STA","C2");

	emitCode("","LDA","C");
	emitCode("","FLOT","");
	emitCode("","STA","C");

	emitCode("","LDA","=0=");
	emitCode("","CHAR","");
	emitCode("","STA","ZERO");

	//code for main program
	traverseNodeForCode(rootNode);

	if(printCode)
		emitPrintCode();

	//code for finishing the program
	fprintf(fOut, "%s\n", preendingLine);
	fprintf(fOut, "%s\n", endingLine);
}


int main(int argc, char* argv[]) {
	currDepth = -1;
	flag = 0;
	whileFlag = 0;
	printFlag = 0;
	printCode = FALSE;

	char fileName[40];

	if(yyparse() == 0) {
		printf("Great!!!\n");
		dfs(rootNode,0);

		stackPos = -1;

		//writing the assembly file
		if(argv[1]) {
			strcpy(fileName, argv[1]);
			strcat(fileName,".mix");
		} else
			sprintf(fileName,"ass.mix");
		fOut = fopen(fileName,"w");
		if(fOut) {
			mkDeclerationCode();
			mkProgramCode();
			fclose(fOut);
		}

	}

	return 0;
}
















void logSymbTable() {
	Symbol* s;
	for(int i = 0; i < SYMB_TABLE_LENGTH; i++) {
		s = symbTable[i];
		if(s == NULL)
			continue;
		while(s != NULL) {
			printf("%s ", s->name);
			s = s->nextInTable;
		}
		printf("\n");
	}
}