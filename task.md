# Mooshak Meta 3 Fixes Checklist

- [ ] Create `ast.h` and `ast.c` and extract AST logic from `jucompiler.y`
- [ ] Create `semantics.h` and `semantics.c` and extract semantic logic from `jucompiler.y`
- [ ] Fix Lexer string buffer overflow (use dynamic reallocation for strings)
- [ ] Fix formatting: `String[]` instead of `String []`
- [ ] Fix formatting: Parameter lists spacing `(int,int)` instead of `( int, int )`
- [ ] Fix method invocation annotation: Add parameter signature to `Identifier` on success
- [ ] Fix invalid symbols logic: Do not add duplicate/reserved methods to symbol table and do not annotate their bodies
- [ ] Fix invalid symbols logic: Do not add duplicate/reserved fields/variables to symbol tables
- [ ] Fix method resolution errors: Include argument types in `Cannot find symbol` and `ambiguous` messages
- [ ] Recompile with new files and run all `meta3` test cases to verify fixes
