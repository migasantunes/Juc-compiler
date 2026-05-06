CC = clang
CFLAGS = -Wall -Wextra -g
SDKROOT ?= $(shell xcrun --show-sdk-path 2>/dev/null)
export CPATH := $(SDKROOT)/usr/include
export LIBRARY_PATH := $(SDKROOT)/usr/lib

all: jucompiler

jucompiler: y.tab.c lex.yy.c ast.c semantics.c codegen.c io.c
	$(CC) $(CFLAGS) -o jucompiler y.tab.c lex.yy.c ast.c semantics.c codegen.c io.c

y.tab.c y.tab.h: jucompiler.y
	yacc -d jucompiler.y

lex.yy.c: jucompiler.l y.tab.h
	lex jucompiler.l

clean:
	rm -f y.tab.c y.tab.h lex.yy.c jucompiler
