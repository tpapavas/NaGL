void emitTempCode (char* line, char* prt1, char* prt2, char* prt3) {
	int pos = 0;
	int i;

	i = 0;
	for(char c = prt1[i]; c != '\0'; c = prt1[++i] ) {
		line[pos++] = c;
	}
	for(i; i<12; i++) 
		line[pos++] = ' ';


	i = 0;
	for(char c = prt2[i]; c != '\0'; c = prt2[++i] )
		line[pos++] = c;
	for(i; i<12; i++) 
		line[pos++] = ' ';


	i = 0;
	for(char c = prt3[i]; c != '\0'; c = prt3[++i] )
		line[pos++] = c;
	for(i; i<12; i++) 
		line[pos++] = ' ';

	line[36] = '\n';
	line[37] = '\0';
}

void emitCode(char* prt1, char* prt2, char* prt3) {
	char line[37];
	int pos = 0;
	int i;

	i = 0;
	for(char c = prt1[i]; c != '\0'; c = prt1[++i] ) {
		line[pos++] = c;
	}
	for(i; i<12; i++) 
		line[pos++] = ' ';


	i = 0;
	for(char c = prt2[i]; c != '\0'; c = prt2[++i] )
		line[pos++] = c;
	for(i; i<12; i++) 
		line[pos++] = ' ';


	i = 0;
	for(char c = prt3[i]; c != '\0'; c = prt3[++i] )
		line[pos++] = c;
	for(i; i<12; i++) 
		line[pos++] = ' ';

	line[36] = '\0';

	fprintf(fOut, "%s\n", line);
}

void _emitCode(char* prt1, char* prt2, char* prt3) {
	char line[37];
	int pos = 0;
	int i;

	i = 0;
	for(char c = prt1[i]; c != '\0'; c = prt1[++i] )
		line[pos++] = c;
	
	line[pos++] = '\t';


	i = 0;
	for(char c = prt2[i]; c != '\0'; c = prt2[++i] )
		line[pos++] = c;
	
	line[pos++] = '\t';


	i = 0;
	for(char c = prt3[i]; c != '\0'; c = prt3[++i] )
		line[pos++] = c;
	
	line[pos++] = '\t';

	line[36] = '\0';

	fprintf(fOut, "%s\n", line);
}