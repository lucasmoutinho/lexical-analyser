program: lexical.l syntax.y; bison -vdt -Wconflicts-sr --graph syntax.y; flex lexical.l; gcc -Wall syntax.tab.c lex.yy.c -o program.out