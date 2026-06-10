# Analisador Léxico e Sintático para MicroPascal

## Descrição

Este projeto implementa um compilador simplificado para a linguagem MicroPascal, composto por:

* Analisador Léxico
* Analisador Sintático Descendente Recursivo
* Tabela de Símbolos

O analisador léxico é responsável por transformar o código-fonte em uma sequência de tokens, enquanto o analisador sintático verifica se a sequência de tokens obedece às regras gramaticais da linguagem MicroPascal.

Além disso, o sistema realiza o tratamento de erros léxicos e sintáticos e gera uma árvore sintática simplificada da estrutura do programa.

---

## Funcionalidades

### Análise Léxica

* Reconhecimento de identificadores e palavras reservadas
* Reconhecimento de números inteiros e reais
* Reconhecimento de operadores aritméticos
* Reconhecimento de operadores relacionais
* Reconhecimento de símbolos especiais
* Ignora comentários delimitados por `{ }`
* Controle de linha e coluna
* Geração de tabela de símbolos
* Registro de erros léxicos

### Análise Sintática

* Implementação da gramática MicroPascal
* Parser descendente recursivo
* Procedimento CasaToken para validação dos tokens
* Emissão das produções utilizadas durante a análise
* Construção de árvore sintática simplificada
* Detecção de erros sintáticos
* Registro de erros sintáticos

---

## Estrutura do Projeto

```text
.
├── backend/
│   ├── lexer.c
│   ├── lexer.h
│   ├── sintaxe.c
│   ├── sintaxe.h
│   ├── tabela_simbolos.c
│   ├── tabela_simbolos.h
│   └── main.c
│
├── input/
│   └── entrada.pas
│
├── saida/
│   ├── saida.lex
│   ├── tabela.ts
│   └── erros.err
```

---

## Gramática Implementada

### Programa

```bnf
<programa> ::= program <identificador> ; <bloco> .
```

### Bloco

```bnf
<bloco> ::= <parte_decl_var> <cmd_composto>
```

### Declarações

```bnf
<parte_decl_var> ::= { var <decl_var> { ; <decl_var> } ; }

<decl_var> ::= <lista_id> : <tipo>

<lista_id> ::= <identificador> { , <identificador> }

<tipo> ::= integer | real
```

### Comandos

```bnf
<cmd_composto> ::= begin <comando> ; { <comando> ; } end

<comando> ::= <atribuicao>
            | <cmd_composto>
            | <cmd_condicional>
            | <cmd_repetitivo>

<atribuicao> ::= <variavel> := <expressao>

<cmd_condicional> ::= if <expressao>
                      then <comando>
                      [ else <comando> ]

<cmd_repetitivo> ::= while <expressao>
                     do <comando>
```

### Expressões

```bnf
<expressao> ::= <expr_simples>
                [ <relacao> <expr_simples> ]

<relacao> ::= =
            | <>
            | <
            | <=
            | >
            | >=

<expr_simples> ::= [ + | - ]
                   <termo>
                   { ( + | - ) <termo> }

<termo> ::= <fator>
            { ( * | / ) <fator> }

<fator> ::= <variavel>
          | <numero>
          | ( <expressao> )

<variavel> ::= <identificador>
```

---

## Tokens Reconhecidos

### Palavras Reservadas

```text
program
var
integer
real
begin
end
if
then
else
while
do
```

### Identificadores

```text
x
contador
valor1
```

### Números

Inteiros:

```text
10
50
1000
```

Reais:

```text
2.5
10.75
3.1415
```

### Operadores

Aritméticos:

```text
+
-
*
/
```

Relacionais:

```text
<
<=
<>
>
>=
=
```

Atribuição:

```text
:=
```

### Símbolos

```text
;
,
(
)
.
:
```

---

## Tratamento de Erros

### Erros Léxicos

O analisador detecta:

* Caractere inválido
* Número mal formado
* Comentário não fechado

Exemplos:

```text
Erro: caractere invalido '@'
Erro: numero mal formado '20.'
Erro: comentario nao fechado
```

### Erros Sintáticos

O analisador sintático segue o formato especificado no trabalho:

```text
nn:token nao esperado [lex].
```

Exemplo:

```text
5:token nao esperado [begin].
```

ou

```text
8:fim de arquivo nao esperado.
```

Todos os erros são registrados em:

```text
saida/erros.err
```

---

## Saídas Geradas

### Análise Léxica

Arquivo:

```text
saida/saida.lex
```

Exemplo:

```text
<KW_program program> (1,1)
<ID teste> (1,9)
<SMB_SEM ;> (1,14)
```

---

### Análise Sintática

Durante a análise sintática são exibidas as produções utilizadas.

Exemplo:

```text
<programa> ::= program <identificador> ; <bloco> .
<bloco> ::= <parte_decl_var> <cmd_composto>
<parte_decl_var> ::= (vazio)
<cmd_composto> ::= begin <comando> ; { <comando> ; } end
<comando> ::= <atribuicao>
<atribuicao> ::= <variavel> := <expressao>
```

---

### Árvore Sintática

O sistema também gera uma árvore sintática simplificada.

Exemplo:

```text
programa
└── bloco
    ├── declaracao
    ├── atribuicao
    ├── if
    └── while
```

---

## Tabela de Símbolos

Arquivo:

```text
saida/tabela.ts
```

Contém todos os identificadores e palavras reservadas reconhecidos durante a compilação.

---

## Como Compilar

Dentro da pasta backend:

```bash
gcc main.c lexer.c sintaxe.c tabela_simbolos.c -o lexer.exe

```

---

## Como Executar
```bash
./lexer
```

O programa irá:

1. Ler o arquivo `input/entrada.pas`
2. Executar a análise léxica
3. Executar a análise sintática
4. Gerar a árvore sintática
5. Atualizar a tabela de símbolos
6. Registrar possíveis erros

---

## Arquitetura Utilizada

### Analisador Léxico

Implementado utilizando um Autômato Finito Determinístico (AFD), responsável por:

* Reconhecimento de tokens
* Classificação de lexemas
* Controle de estados
* Tratamento de erros

### Analisador Sintático

Implementado através da técnica de Descida Recursiva (Recursive Descent Parser).

Cada símbolo não-terminal da gramática foi implementado como uma função específica:

```text
programa()
bloco()
parteDeclaracoesVar()
declaracaoVar()
listaIdentificadores()
tipo()
comandoComposto()
comando()
atribuicao()
cmdCondicional()
cmdRepetitivo()
expressao()
exprSimples()
termo()
fator()
```

O procedimento:

```text
casaToken()
```

é responsável por validar os tokens esperados pela gramática.

---

## Autores

Arthur Lemos Bendini

Gabriel Baptista Gallo

Bacharelado em Ciência da Computação – 5º Semestre

Linguagens Formais, Autômatos e Compiladores

Universidade Católica de Brasília
