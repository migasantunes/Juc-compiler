# Relatório Final — Compilador Juc

**Autores:** José Miguel Luís Antunes (2023211288), André Jorge Balula Leão (2023210870)

---

## (i) Gramática Re-escrita

A gramática EBNF fornecida no enunciado foi transformada para uma gramática BNF compatível com análise ascendente em yacc, tendo sido necessário resolver ambiguidades, eliminar construções EBNF e impor precedência/associatividade dos operadores.

### Eliminação de Notação EBNF

As construções `{...}` (zero ou mais repetições) foram convertidas em não-terminais recursivos à esquerda, seguindo o padrão natural do yacc. Por exemplo, a lista de declarações no `Program` foi transformada no não-terminal `DeclList`, que acumula recursivamente `MethodDecl`, `FieldDecl` e `SEMICOLON`. As construções `[...]` (opcionais) foram desdobradas em alternativas explícitas: por exemplo, o `if` com e sem `else` resultou em duas produções separadas para `Statement`.

A declaração de múltiplos identificadores separados por vírgulas em `FieldDecl` e `VarDecl` foi tratada pelo não-terminal auxiliar `AuxIdList`, que acumula os identificadores adicionais. Na ação semântica, cada identificador extra origina um nó separado de declaração, replicando o nó do tipo.

### Resolução de Ambiguidades em Expressões

A gramática original define `Expr` com produções ambíguas para operadores binários. A solução adotada foi a decomposição em múltiplos níveis de precedência, cada um representado por um não-terminal dedicado: `OrExpr`, `AndExpr`, `XorExpr`, `EqExpr`, `RelExpr`, `ShiftExpr`, `AddExpr`, `MulExpr`, `UnaryExpr` e `Primary`. Cada nível é recursivo à esquerda, garantindo associatividade à esquerda para os operadores binários. A precedência segue as convenções de Java: `||` (mais baixa), `&&`, `^`, `==`/`!=`, `<`/`>`/`<=`/`>=`, `<<`/`>>`, `+`/`-`, `*`/`/`/`%` (mais alta). Os operadores unários (`-`, `+`, `!`) têm precedência superior aos binários, resolvida via o não-terminal `UnaryExpr` com marcadores `%prec UNARY_MINUS` e `%prec UNARY_PLUS`.

A atribuição (`IDENTIFIER ASSIGN Expr`) foi tratada como uma alternativa de topo em `Expr`, com associatividade à direita, e também como alternativa em `Statement` seguida de `SEMICOLON`.

### Dangling Else

O conflito *dangling else* foi resolvido com o marcador de precedência `%prec LOWER_THAN_ELSE` na produção `if` sem `else`, e a declaração `%nonassoc ELSE` com precedência superior, garantindo que o `else` se associa ao `if` mais próximo.

### Distinção entre StatementList e MethodBodyDecls

O não-terminal `MethodBodyDecls` permite tanto `Statement` como `VarDecl`, enquanto `StatementList` (usado dentro de blocos `{...}` aninhados) aceita apenas `Statement`. Esta distinção garante que declarações de variáveis locais só são permitidas ao nível do corpo do método, tal como especificado pela gramática Juc.

### Recuperação de Erros

Foram incluídas regras de erro com `error` nos pontos especificados no enunciado: `FieldDecl`, `Statement`, `ParseArgs`, `MethodInvocation` e expressões entre parêntesis.

---

## (ii) Algoritmos e Estruturas de Dados da AST e da Tabela de Símbolos

### Árvore de Sintaxe Abstrata (AST)

A AST é construída durante a análise sintática através de ações semânticas nas produções yacc. A estrutura base é o nó `Node`, definido em `ast.h`, com os campos: `type` (tipo do nó, e.g., "Program", "If", "Add"), `value` (valor léxico para terminais, e.g., nome do identificador), ponteiros `child` e `sibling` para filhos e irmãos, e `line`/`col` para a localização no código-fonte. O campo `annot` é usado para armazenar a anotação de tipo atribuída durante a análise semântica.

A construção da árvore usa três operações fundamentais: `new_node_at` (cria um nó com posição), `add_child` (adiciona como filho, ou como irmão do último filho existente) e `add_sibling` (percorre a lista de irmãos até ao fim e liga o novo nó). A lista de irmãos implementa uma lista ligada simples. A função `create_block` implementa a regra de eliminação de blocos supérfluos: blocos com exatamente um statement são desembrulhados, evitando nós `Block` desnecessários.

A impressão da AST é feita recursivamente com `print_tree`, incrementando a indentação (pontos `.`) em dois por nível de profundidade, visitando primeiro os filhos e depois os irmãos. A versão anotada (`print_tree_annotated`) acrescenta o tipo após ` - ` quando o campo `annot` não é nulo.

### Tabela de Símbolos

A tabela de símbolos é organizada em duas camadas: uma tabela global da classe (`class_table`) e uma tabela por método (`MethodInfo.table`). Ambas usam a estrutura `SymTable`, que contém uma lista ligada de `Symbol`. Cada `Symbol` armazena o nome, tipo (`TypeKind`), flags `is_param` e `is_method`, uma lista de tipos de parâmetros (para métodos) e o nó da AST de declaração.

A construção das tabelas (`build_symbol_tables`) percorre a AST em duas fases: primeiro regista variáveis globais (`FieldDecl`) e assinaturas de métodos, depois processa os parâmetros de cada método. Erros de símbolo reservado (`_`) e símbolo já definido são reportados durante a construção. A anotação dos tipos (`annotate_program`) percorre método a método, analisando o corpo. As variáveis locais (`VarDecl`) são registadas na tabela do método à medida que são encontradas durante a análise semântica.

A resolução de métodos (`resolve_method`) implementa as regras simplificadas de Java: primeiro procura correspondência exata de tipos de parâmetros; caso não encontre, procura métodos compatíveis (com promoção `int → double`), reportando ambiguidade se houver mais de um candidato. A informação de métodos é mantida na lista ligada `method_list`, preservando a ordem de declaração. Toda a memória é libertada em `free_symbol_tables`.

---

## (iii) Geração de Código

### Arquitetura do Gerador

O gerador de código LLVM IR está implementado em `codegen.c` e produz código para execução com `lli` ou compilação com `llc`. A estrutura central `CG` mantém o estado da geração: ficheiro de saída, contadores de registos (`%t0`, `%t1`, ...) e labels, uma lista de constantes string, um mapa de variáveis locais (`VarSlot`) e o estado do bloco básico atual.

### Mapeamento de Tipos

Os tipos Juc são mapeados diretamente: `boolean → i1`, `int → i32`, `double → double`. O tipo `String[]` é representado como um tipo agregado `%StringArray = type { i8**, i32 }`, contendo o array de ponteiros para strings e o seu comprimento. A conversão `int → double` (promoção numérica) usa `sitofp`.

### Variáveis e Funções

Variáveis locais e parâmetros são alocados com `alloca` no bloco de entrada de cada função. Os parâmetros são copiados para as allocas correspondentes com `store`. Variáveis locais são inicializadas a zero/0.0/false. Variáveis globais (`FieldDecl`) são emitidas como globais LLVM (`@nome = global i32 0`). O acesso a variáveis usa `load`/`store` sobre os ponteiros das allocas ou globais.

Os nomes das funções são *mangled* para evitar conflitos entre métodos com o mesmo nome mas assinaturas diferentes, concatenando o nome com os tipos dos parâmetros (e.g., `factorial__int`). A função `main` de Java recebe `%StringArray` e é invocada por um wrapper `@main(i32 %argc, i8** %argv)` que constrói o `%StringArray` a partir de `argc`/`argv`, ignorando `argv[0]`.

### Expressões e Statements

A geração de expressões (`gen_expr`) é recursiva, produzindo um par `(tipo, registo)`. Operadores aritméticos usam `add`/`sub`/`mul`/`sdiv`/`srem` para inteiros e `fadd`/`fsub`/`fmul`/`fdiv`/`frem` para doubles. Comparações usam `icmp`/`fcmp` com predicados adequados. A avaliação em curto-circuito de `&&` e `||` é implementada com branching e `phi`: avalia o operando esquerdo, e apenas avalia o direito se necessário, juntando o resultado com um nó `phi`.

O `if` gera três labels (then/else/end) com branching condicional. O `while` gera um ciclo com condição/corpo/retorno ao topo. O `return` emite a instrução `ret` e marca o bloco como terminado para evitar geração de código morto. O `System.out.print` usa `printf` com formatos `%d` (int), `%.16e` (double), `%s` (strings), e `select` entre literais "true"/"false" para booleanos. O `Integer.parseInt` invoca `atoi`. As constantes string são recolhidas durante a geração e emitidas como constantes globais LLVM, com escape sequences devidamente codificadas para o formato LLVM IR.
