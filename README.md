# Analisador Léxico para MicroPascal

## Descrição

Este projeto implementa um analisador léxico para uma linguagem baseada em MicroPascal. O analisador é responsável por ler um arquivo de entrada contendo código-fonte e transformá-lo em uma sequência de tokens, identificando elementos como palavras reservadas, identificadores, números, operadores e símbolos.

Além disso, o sistema realiza a detecção de erros léxicos e mantém uma tabela de símbolos.

---

## Funcionalidades

* Reconhecimento de identificadores e palavras reservadas
* Reconhecimento de números inteiros e reais
* Reconhecimento de operadores aritméticos e relacionais
* Reconhecimento de símbolos especiais
* Ignora comentários delimitados por `{ }`
* Controle de linha e coluna para cada token
* Geração de tabela de símbolos
* Registro de erros léxicos

---

## Estrutura do Projeto

```
.
├── backend/
│   ├── lexer.c            # Implementação do analisador léxico
│   ├── lexer.h            # Definição da estrutura de tokens
│   ├── tabela_simbolos.c  # Implementação da tabela de símbolos
│   ├── tabela_simbolos.h  # Interface da tabela de símbolos
│   └── main.c             # Programa principal
├── input/
│   └── entrada.pas        # Arquivo de entrada (código-fonte)
│
├── saida/
│   ├── saida.lex          # Tokens gerados
│   ├── tabela.ts          # Tabela de símbolos
│   └── erros.err          # Erros léxicos
```

---

## Tokens Reconhecidos

### Palavras Reservadas

```
program, var, integer, real, begin, end,
if, then, else, while, do
```

---

### Identificadores

* Sequência iniciada por letra, seguida de letras ou dígitos

Exemplo:

```
x, teste, variavel1
```

---

### Números

* Inteiros:

```
10, 25, 100
```

* Reais:

```
2.5, 10.75
```

---

### Operadores

* Aritméticos:

```
+, -, *, /
```

* Relacionais:

```
<, <=, <>, >, >=, =
```

* Atribuição:

```
:=
```

---

### Símbolos

```
; , ( ) . :
```

---

## Tratamento de Erros

O analisador detecta os seguintes erros léxicos:

* Caractere inválido
* Número mal formado (ex: `20.`)
* Comentário não fechado

Os erros são registrados no arquivo:

```
saida/erros.err
```

---

## Exemplo de Entrada

Arquivo: `input/entrada.pas`

```
program Teste;
var
x, y : integer;
z : real;
begin
x := 10;
y := 20;
z := 2.5;

x := 20.;      { erro número mal formado }
y := 10 @ 2;   { erro caractere inválido }

{ comentário não fechado
end.
```

---

## Exemplo de Saída

Arquivo: `saida/saida.lex`

```
<KW_program   program     > ( 1,  1)
<ID           teste       > ( 1,  9)
<SMB_SEM      ;           > ( 1, 14)
...
```

---

## Tabela de Símbolos

Arquivo: `saida/tabela.ts`

Contém todos os identificadores e palavras reservadas reconhecidos.

---

## Como Compilar

No terminal, dentro da pasta backend:

```
gcc main.c lexer.c tabela_simbolos.c -o lexer
```

---

## Como Executar

```
./lexer
```

O programa irá:

1. Ler o arquivo `input/entrada.pas`
2. Gerar os arquivos de saída em `saida/`

---

## Funcionamento do Analisador

O analisador léxico foi implementado utilizando um Autômato Finito Determinístico (AFD), responsável por:

* Classificar lexemas com base no primeiro caractere
* Processar tokens sequencialmente
* Retornar ao estado inicial após cada token

---

## Observações

* Espaços em branco e quebras de linha são ignorados
* O analisador não verifica erros sintáticos
* O reconhecimento de palavras reservadas é case-insensitive

---

## Autores

Arthur Lemos Bendini  
Gabriel Baptista Gallo  
Bacharelado em Ciência da Computação - 5° Semestre  
LINGUAGENS FORMAIS, AUTÔMATOS E COMPILADORES  
Universidade Católica de Brasília
