program:  lexical.l syntax.y
	bison -d syntax.y
    flex lexical.l
    gcc syntax.tab.c lex.yy.c -o program.out