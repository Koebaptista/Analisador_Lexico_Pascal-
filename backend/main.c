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

    fprintf(out,
        "========================================\n"
        "ANALISE LEXICA\n"
        "========================================\n\n");

    Token tk;

    while (1) {

        tk = proximoToken(fp);

        if (strcmp(tk.token, "EOF") == 0)
            break;

        fprintf(out,
            "<%-12s %-12s> (%2d, %2d)\n",
            tk.token,
            tk.lexema,
            tk.linha,
            tk.coluna);
    }

    rewind(fp);

    fprintf(out,
        "\n\n========================================\n"
        "ANALISE SINTATICA\n"
        "========================================\n\n");

    initParser(fp, out);

    programa();

    imprimirArvore();

    fprintf(out,
        "\nAnalise sintatica concluida com sucesso!\n");

    printf("\nAnalise sintatica concluida com sucesso!\n");

    salvarTS();

    fclose(fp);
    fclose(out);

    return 0;
}