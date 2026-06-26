# jucompiler

Compiler for the Juc language, developed in C using `lex` and `yacc`, covering:
- Stage 1: lexical analysis
- Stage 2: syntax analysis and AST
- Stage 3: semantic analysis, symbol tables, and annotated AST
- Stage 4: LLVM IR code generation

The final executable is called `jucompiler`, reads from `stdin`, and writes to `stdout`.

## Project Structure

- `src/`: main implementation (AST, semantics, codegen, io)
- `include/`: header files
- `parser/`: `jucompiler.l` and `jucompiler.y`
- `Makefile`: primary build file
- `README.md`: this file

Local support directories (ignored in Git, see `.gitignore`):
- `tests/`: local test cases (`all_meta_tests/...`)
- `scripts/`: local test execution scripts
- `docs/`: local reports and specifications
- `archive/`: local history of submissions
- `build/` and `bin/`: build artifacts

## Requirements

System tools required:
- `clang` (or another compatible C compiler)
- `make`
- `lex` (or `flex`)
- `yacc` (or `bison`)
- `lli` (optional, for executing LLVM IR in stage 4 tests)

## Building

```bash
make
```

This generates the executable at `bin/jucompiler`.

To clean artifacts:

```bash
make clean
```

## Execution Modes

Basic usage:

```bash
bin/jucompiler [option] < program.java
```

Supported options:
- `-l`: lexical analysis; prints tokens and lexical errors
- `-e1`: lexical analysis; prints only lexical errors
- `-t`: syntax analysis; prints lexical/syntax errors and AST (if no syntax errors)
- `-e2`: syntax analysis; prints only lexical/syntax errors
- `-s`: semantic analysis; prints semantic errors, symbol tables, and annotated AST
- `-e3`: semantic analysis; prints only errors (with `-e2` behavior if lex/syntax errors exist)
- no option: generates LLVM IR only if there are no errors

Example (generate IR):

```bash
bin/jucompiler < Factorial.java > Factorial.ll
```

Execute IR:

```bash
lli Factorial.ll 7
```

## Local Tests

Test cases are treated as local development data provided by the instructor in a private Git repository.
