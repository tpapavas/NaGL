void yyerror(char* err) {
	fputs(err,stderr);
	putc('\n',stderr);
}

AstNode* mkNode(int type, Symbol* s, AstNode* n1, AstNode* n2, AstNode* n3, AstNode* n4) {
	AstNode* newNode = (AstNode*)malloc(sizeof(AstNode));

	if(newNode) {
		newNode->nodeType = type;
		newNode->nodSymbol = s;
		newNode->pAstNode[0] = n1; 
		newNode->pAstNode[1] = n2;
		newNode->pAstNode[2] = n3; 
		newNode->pAstNode[3] = n4;	
	} else {
		printf("no more memory\n");
		exit(1);
	}

	return newNode;
}

Symbol* mkSymbol(char* name, int type) { 
	Symbol* s = (Symbol*)malloc(sizeof(Symbol));

	if(s) {
		strcpy(s->name,name);
		s->varType = type;
		s->rVal = 0;
		switch (type) {
			case INT:
				s->value.i = 0;
				break;

			case FLOAT:
				s->value.f = 0;
		}
		s->nextInTable = NULL;
		s->accessible = FALSE;
	} else {
		printf("no more memory\n");
		exit(1);
	}

	return s; 
}

int pushStack(Symbol* s) {
	if(stackPos < STACK_SIZE-1) {
		symbStack[++stackPos] = s;
		return 1;
	}

	return 0;
}

Symbol* popStack() {
	if(stackPos >= 0)
		return symbStack[stackPos--];

	return NULL;
}

int culcKey(char* name) {
	int weight = NAME_LENGTH;
	int val = 0;
	
	for(char c = *name; c != '\0'; c=*name, name++) {
		val += weight*c;
		weight--;
	}

	return val % SYMB_TABLE_LENGTH;
}

int addToTable(Symbol* s) {
	int tPos = culcKey(s->name);

	if(symbTable[tPos] == NULL) {
		symbTable[tPos] = s;
		return 1;
	} else {
		Symbol* s1 = symbTable[tPos];
		Symbol* thisS = NULL;
		while(s1 != NULL) {
			if(strcmp(s1->name,s->name) == 0)
				if(s1->depth == s->depth)
					return FALSE;
			thisS = s1;
			s1 = s1->nextInTable;
		}
		thisS->nextInTable = s;
	}

	return TRUE;
}

Symbol* findId(char* name, int depth) {
	int tPos = culcKey(name);
	int maxDepth = -1;
	
	Symbol* tmp = NULL;
	Symbol* s = symbTable[tPos];
	while(s != NULL) {
		if(strcmp(s->name,name) == 0) {
			if(s->depth <= depth && s->depth > maxDepth) {
				maxDepth = s->depth;
				tmp = s;
			}
		}
		//scope check must be done
		s = s->nextInTable;
	}
	
	return tmp;
}

int isInt(char* num) {
	for(char c = *num; c != '\0'; c=*num, num++) {
		if(c == '.')
			return 0;
	}

	return 1;
}

Symbol* checkMult(Symbol* s1, Symbol* s2) {
	Symbol* result = mkSymbol("",FLOAT);
	if(s1->varType == INT && s2->varType == INT)
		result->varType = INT;

	return result;
};

Symbol* checkDiv(Symbol* s1, Symbol* s2) {
	Symbol* quotient = mkSymbol("",FLOAT);
	
	if(!s2->isVar && s2->value.f == 0) {
		printf("%s\n", "Error: Division by zero");
		exit(1);
	}
	// float k = 1;

	// if(!s2->isVar) {
	// 	switch (s2->varType) {
	// 		case INT:
	// 			k = s2->value.i;
	// 			break;

	// 		case FLOAT:
	// 			k = s2->value.f;
	// 	}
	// 	if(k == 0) {
	// 		printf("%s\n", "Error: Division by zero");
	// 		exit(1);
	// 	}
	// }



	if(s1->varType == INT && s2->varType == INT)
		quotient->varType = INT;

	return quotient;
}

Symbol* checkAdd(Symbol* s1, Symbol* s2) {
	Symbol* sum = mkSymbol("",FLOAT);
	if(s1->varType == INT && s2->varType == INT)
		sum->varType = INT;

	return sum;
}

Symbol* checkSub(Symbol* s1, Symbol* s2) {
	Symbol* difference = mkSymbol("",FLOAT);
	if(s1->varType == INT && s2->varType == INT)
		difference->varType = INT;

	return difference;
}

void negateSymbols(int d) {
	Symbol* s;
	for(int i = 0; i < SYMB_TABLE_LENGTH; i++) {
		for(s = symbTable[i]; s != NULL; s = s->nextInTable) {
			if(s->depth == d)
				s->accessible = FALSE;
		}
	}

	return;
}


void normalizeFloat(float flt, int* number, int* multiplier){
	float numErr = 0.00001;
	*multiplier = 1;
	while ((flt - floor(flt)) > numErr) {
		*multiplier *= 10;
		flt = flt * 10;
	}
	*number = (int) (flt+0.5);

	return;
}