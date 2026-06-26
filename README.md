# jucompiler

Compilador da linguagem Juc, desenvolvido em C com `lex` e `yacc`, cobrindo:
- Meta 2: analise sintatica e AST
- Meta 3: analise semantica, tabelas de simbolos e AST anotada
- Meta 4: geracao de codigo LLVM IR

O executavel final chama-se `jucompiler`, le do `stdin` e escreve para `stdout`.

## Estrutura do Projeto

- `src/`: implementacao principal (AST, semantica, codegen, io)
- `include/`: headers
- `parser/`: `jucompiler.l` e `jucompiler.y`
- `Makefile`: build principal
- `README.md`: este ficheiro

Diretorias de apoio local (ignoradas no Git, ver `.gitignore`):
- `tests/`: testcases locais (`all_meta_tests/...`)
- `scripts/`: scripts locais de execucao de testes
- `docs/`: relatorios/enunciados locais
- `archive/`: historico local de entregas
- `build/` e `bin/`: artefactos de compilacao

## Requisitos

Ferramentas necessarias no sistema:
- `clang` (ou outro compilador C compativel)
- `make`
- `lex` (ou `flex`)
- `yacc` (ou `bison`)
- `lli` (opcional, para executar LLVM IR em testes da meta 4)

## Compilar

```bash
make
```

Isto gera o executavel em `bin/jucompiler`.

Para limpar artefactos:

```bash
make clean
```

## Modos de Execucao

Uso base:

```bash
bin/jucompiler [opcao] < programa.java
```

Opcoes suportadas:
- `-l`: analise lexical; imprime tokens e erros lexicais
- `-e1`: analise lexical; imprime apenas erros lexicais
- `-t`: analise sintatica; imprime erros lexicais/sintaticos e AST (se nao houver erros sintaticos)
- `-e2`: analise sintatica; imprime apenas erros lexicais/sintaticos
- `-s`: analise semantica; imprime erros semanticos, tabelas de simbolos e AST anotada
- `-e3`: analise semantica; imprime apenas erros (com comportamento de `-e2` se houver erros lex/sint)
- sem opcao: gera LLVM IR apenas se nao houver erros

Exemplo (gerar IR):

```bash
bin/jucompiler < Factorial.java > Factorial.ll
```

Executar IR:

```bash
lli Factorial.ll 7
```

## Testes Locais

Os testcases sao tratados como dados locais de desenvolvimento fornecidos pelo professor num repositorio de git privado.
