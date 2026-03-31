#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>

typedef struct {
    char token[30];
    char lexema[100];
    int linha;
    int coluna;
} Token;

Token proximoToken(FILE *fp);

#endif