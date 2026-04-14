#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "tabela_simbolos.h"
#include <direct.h>

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

    _mkdir("../saida"); // cria pasta automaticamente

    // cria arquivo de erros vazio
    FILE *err = fopen("../saida/erros.err", "w");
    fclose(err);

    FILE *fp = fopen("../input/entrada.pas", "r");
    FILE *out = fopen("../saida/saida.lex", "w");
    

    if (!fp || !out) {
        printf("Erro ao abrir arquivos.\n");
        return 1;
    }

    inicializarTS();

    Token tk;

    while (1) {
        tk = proximoToken(fp);

        if (strcmp(tk.token, "EOF") == 0)
            break;

        fprintf(out, "<%-12s %-12s> (%2d, %2d)\n",
            tk.token, tk.lexema, tk.linha, tk.coluna);
    }

    salvarTS();

    fclose(fp);
    fclose(out);

    return 0;
}