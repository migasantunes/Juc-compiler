CC = clang
CFLAGS = -Wall -Wextra -g

all: jucompiler

jucompiler: y.tab.c lex.yy.c ast.c semantics.c
	$(CC) $(CFLAGS) -o jucompiler y.tab.c lex.yy.c ast.c semantics.c

y.tab.c y.tab.h: jucompiler.y
	yacc -d jucompiler.y

lex.yy.c: jucompiler.l y.tab.h
	lex jucompiler.l

clean:
	rm -f y.tab.c y.tab.h lex.yy.c jucompiler
