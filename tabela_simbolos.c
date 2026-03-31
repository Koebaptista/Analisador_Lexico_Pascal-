#include <stdio.h>
#include <string.h>

typedef struct {
    char lexema[50];
    char tipo[30];
} Simbolo;

Simbolo TS[1000];
int qtdTS = 0;

void inserirTS(char *lexema, char *tipo) {
    for (int i = 0; i < qtdTS; i++) {
        if (strcasecmp(TS[i].lexema, lexema) == 0)
            return;
    }

    strcpy(TS[qtdTS].lexema, lexema);
    strcpy(TS[qtdTS].tipo, tipo);
    qtdTS++;
}

void salvarTS() {
    FILE *f = fopen("saida/tabela.ts", "w");

    for (int i = 0; i < qtdTS; i++) {
        fprintf(f, "%-15s | %-20s\n", TS[i].lexema, TS[i].tipo);
    }

    fclose(f);
}