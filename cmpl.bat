cls
yacc -dv ssanal.y
flex lexer.l
gcc lex.yy.c zyywrap.c y.tab.c -o cmm
rem gcc lex.yy.c zyywrap.c y.tab.c main.c -o cmm
rem gcc lex.yy.c zyywrap.c -o cmm