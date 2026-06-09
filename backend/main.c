#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "tabela_simbolos.h"
#include <direct.h>
#include "sintaxe.h"

void inicializarTS() {
    char *reservadas[] = {
        "program","var","integer","real","begin","end",
        "if","then","else","while","do"
    };

    for (int i = 0; i < 11; i++) {
        inserirTS(reservadas[i], "palavra-reservada");
    }
}

int main() {

    _mkdir("../saida"); 

    FILE *err = fopen("../saida/erros.err", "w");
    fclose(err);

    FILE *fp = fopen("../input/entrada.pas", "r");
    FILE *out = fopen("../saida/saida.lex", "w");
    

    if (!fp || !out) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    inicializarTS();

    initParser(fp, out);

    programa();

    printf("\nAnalise sintatica concluida com sucesso!\n");

    salvarTS();

    fclose(fp);
    fclose(out);

    return 0;
}