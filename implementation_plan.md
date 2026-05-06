# Implementation Plan for Mooshak Meta 3 Fixes

Based on analyzing the `all_meta_tests` directory and Mooshak requirements, the current compiler needs architectural and specific behavioral fixes.

## 1. File Restructuring
Mooshak expects specific files `ast.c`, `ast.h`, `semantics.c`, and `semantics.h`.
- **`ast.h` / `ast.c`**: Will contain the `Node` structure, `new_node`, `new_node_at`, `add_sibling`, `print_tree`, `free_tree`.
- **`semantics.h` / `semantics.c`**: Will contain `TypeKind`, `Symbol`, `SymTable`, `MethodInfo`, `build_symbol_tables`, `annotate_program`, `print_symbol_tables`.
- **`jucompiler.y`**: Will include these headers and orchestrate parsing and semantic analysis.
- **`Makefile`**: Ensure the compilation uses `gcc -o jucompiler y.tab.c lex.yy.c ast.c semantics.c -lfl`.

## 2. String Literal Buffer Overflow Fix
The lexer uses a static `char string_buffer[8192]`. Mooshak tests with very long strings cause buffer overflows.
- I will change `string_buffer` to a dynamically resizing buffer (using `realloc`) during string parsing in `jucompiler.l` to handle strings of any length.

## 3. Formatting Fixes (Whitespace matching)
Mooshak string matching is extremely strict.
- **`String []` vs `String[]`**: Change `type_to_str` to return `"String[]"` (no space).
- **Parameter Lists**: Method parameter types must be printed with no spaces. `(int,int)`, `()`, `(double)`. Change `print_param_types` to remove spaces.
- **Call annotations**: In the AST, an `Identifier` node corresponding to a method call must be annotated with its exact parameter signature (e.g., `- (int,int)`) upon success. Currently, we leave it unannotated on success.

## 4. Semantic Rules for Invalid Symbols
Duplicate and reserved symbols (`_`) have strict cascading rules:
- **Duplicate/Reserved Methods**: Print the error, but **DO NOT** add the method to the class symbol table, and **DO NOT** annotate any expressions inside its body. Currently, we add them and annotate them.
- **Duplicate/Reserved Fields**: Print the error, **DO NOT** add to class symbol table.
- **Duplicate/Reserved Variables/Params**: Print the error, **DO NOT** add to method symbol table.
- **`_` Usage**: Using `_` in an expression correctly prints `Symbol _ is reserved` and evaluates to `undef`.

## 5. Method Resolution Error Messages
When a method call fails to resolve or is ambiguous, the error message must include the argument types.
- **Before**: `Cannot find symbol foo`
- **After**: `Cannot find symbol foo(int,double)` or `Reference to method foo(int,double) is ambiguous`.

## Verification Plan
After making these changes:
1. Recompile using `ast.c` and `semantics.c`.
2. Run `bash test.sh -s meta3` inside `all_meta_tests` to verify that all Meta 3 tests pass perfectly and the `diff` output is empty.
