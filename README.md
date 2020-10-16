# Analisador Sintático

- Aluno: Lucas da Silva Moutinho (150015747)

## Requerimentos

- Flex 2.6.4
- GCC 7.5.0
- Bison 3.0.4

## Compilando e Executando

```bash
make
./program.out testes/arquivo_teste
```

## Exemplos de teste

### 1) Exemplo sem erros

Código de entrada:
```
1. int main(){
2.     print("ola");
3. }
```

Saída do Analisador sintático:
```
----------  ABSTRACT SYNTAX TREE ----------

FUNCTION_DECLARATION | type: int | main | 
-COMPOUND_STATEMENT | 
--STATEMENT_LIST | 
---PRINT | print | 
----STRING | ola | 


----------  TABELA DE SÍMBOLOS ----------

key:              main::0 | name:                 main | type:        int | symbol_type: F | scope: 0
```

### 2) Exemplo com erros

Código de entrada:
```
1. int main(){
2.     print("ola")
3. }
```

Saída do lexico:
```
syntax error, unexpected '}', expecting ';' -- linha: 3
```