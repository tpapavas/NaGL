This is a compiler for Knuth MIX Machine.
It compiles a simple custom language to MIXAL (assembly language for D. Knuth's ideal machine).

Compiler consists of:
-lexer.l
-ssnanal.y
-defs.h
-funcs.c
-main.c
-emit.c
-zyywrap.c

lex.yy.c is produced by passing lexer.l to flex.exe.
y.tab.h, y.tab.c and y.output are produced by passing ssanal.y to yacc.exe
Compiling all *.c (written and produced) files, we get the compiler.

Compiler is the cmm.exe file.
To compile a file you can write on cmd "cmm <path-to-filename"
The produced file (ass.mix) can now given to the MIX Builder.
In MIX Builder, you can assemble the file (ass.mix) and run it.

Language's functionality:
-everything is done inside main class(mainclass), inside a main method (public static void main())
-data types: int, float
-if statements
-for, while loops
-print function (println)

Compiler was based on the code in "base code" folder. This code was given by my professor Georgios Makris.

Have fun!
