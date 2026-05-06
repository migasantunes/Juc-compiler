/* LLVM IR code generation for Juc (Meta 4) */
#ifndef CODEGEN_H
#define CODEGEN_H

#include <stdio.h>
#include "ast.h"

/* Emits LLVM IR to `out`. Assumes AST is semantically valid and annotated. */
void codegen_program(Node *program, FILE *out);

#endif

