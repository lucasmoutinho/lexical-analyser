# Analisador Léxico

- Aluno: Lucas da Silva Moutinho (150015747)

## Requerimentos

- Flex 2.6.4
- GCC 7.5.0

## Compilando e Executando

```bash
lex lexical.l
gcc lex.yy.c
./a.out testes/arquivo_teste
```

## Exemplos de teste

### 1) Exemplo sem erros

Código de entrada:
```
1. text = "ola";
2. strUpper(text);
3. print(text);
```

Saída do lexico:
```
ID              (text) LENGTH 4 ADDRESS 0
ASSIGN          (=) LENGTH 1
STRING          ("ola") LENGTH 5
SEP             (;) LENGTH 1
STMT            (strUpper) LENGTH 8
SEP             (() LENGTH 1
ID              (text) LENGTH 4 ADDRESS 0
SEP             ()) LENGTH 1
SEP             (;) LENGTH 1
STMT            (print) LENGTH 5
SEP             (() LENGTH 1
ID              (text) LENGTH 4 ADDRESS 0
SEP             ()) LENGTH 1
SEP             (;) LENGTH 1


------SYMBOL TABLE--------
0 -- Simbolo: text
----------------------
```

### 2) Exemplo com erros

Código de entrada:
```
1. text = "ola";
2. strUpper(@text);
3. print(text);
```

Saída do lexico:
```
ID              (text) LENGTH 4 ADDRESS 0
ASSIGN          (=) LENGTH 1
STRING          ("ola") LENGTH 5
SEP             (;) LENGTH 1
STMT            (strUpper) LENGTH 8
SEP             (() LENGTH 1
ID              (text) LENGTH 4 ADDRESS 0
SEP             ()) LENGTH 1
SEP             (;) LENGTH 1
STMT            (print) LENGTH 5
SEP             (() LENGTH 1
ID              (text) LENGTH 4 ADDRESS 0
SEP             ()) LENGTH 1
SEP             (;) LENGTH 1


------SYMBOL TABLE--------
0 -- Simbolo: text
----------------------


----------------------
Number of errors: 1

------ERROR 1--------
Simbolo: @
Simbolo nao reconhecido pela analise lexica
Line: 2
----------------------
```