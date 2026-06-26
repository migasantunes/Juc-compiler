CC ?= clang
CFLAGS ?= -Wall -Wextra -g
CPPFLAGS ?= -Iinclude -Ibuild

SRC_DIR := src
PARSER_DIR := parser
BUILD_DIR := build
BIN_DIR := bin

TARGET := $(BIN_DIR)/jucompiler
PARSER_SRC := $(PARSER_DIR)/jucompiler.y
LEXER_SRC := $(PARSER_DIR)/jucompiler.l

PARSER_C := $(BUILD_DIR)/y.tab.c
PARSER_H := $(BUILD_DIR)/y.tab.h
LEXER_C := $(BUILD_DIR)/lex.yy.c

SRC_FILES := \
	$(SRC_DIR)/ast.c \
	$(SRC_DIR)/semantics.c \
	$(SRC_DIR)/codegen.c \
	$(SRC_DIR)/io.c

all: $(TARGET)

$(BUILD_DIR) $(BIN_DIR):
	mkdir -p $@

$(PARSER_C) $(PARSER_H): $(PARSER_SRC) | $(BUILD_DIR)
	cd $(BUILD_DIR) && yacc -d ../$(PARSER_SRC)

$(LEXER_C): $(LEXER_SRC) $(PARSER_H) | $(BUILD_DIR)
	cd $(BUILD_DIR) && lex ../$(LEXER_SRC)

$(TARGET): $(PARSER_C) $(LEXER_C) $(SRC_FILES) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $(PARSER_C) $(LEXER_C) $(SRC_FILES)

test: $(TARGET)
	./scripts/run_tests.sh all

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all test clean
