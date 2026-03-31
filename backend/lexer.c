#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "tabela_simbolos.h"
#define strcasecmp _stricmp

int linha = 1, coluna = 0;

char *reservadas[] = {
    "program","var","integer","real","begin","end",
    "if","then","else","while","do"
};

int ehReservada(char *lex) {
    for (int i = 0; i < 11; i++) {
        if (strcasecmp(lex, reservadas[i]) == 0)
            return 1;
    }
    return 0;
}

void erro(char c) {
    FILE *f = fopen("../saida/saida/erros.err", "a");
    fprintf(f, "Erro: caractere invalido '%c' linha %d coluna %d\n", c, linha, coluna);
    fclose(f);
}

Token proximoToken(FILE *fp) {
    Token tk;
    char c;
    int i = 0;

    while ((c = fgetc(fp)) != EOF) {

        coluna++;

        if (c == '\n') {
            linha++;
            coluna = 0;
            continue;
        }

        if (isspace(c)) continue;

        int col_inicio = coluna;

        // IDENTIFICADOR / PALAVRA RESERVADA
        if (isalpha(c)) {
            tk.lexema[i++] = tolower(c);

            while (isalnum(c = fgetc(fp))) {
                tk.lexema[i++] = tolower(c);
                coluna++;
            }

            tk.lexema[i] = '\0';
            ungetc(c, fp);

            if (ehReservada(tk.lexema)) {
                sprintf(tk.token, "KW_%s", tk.lexema);
                inserirTS(tk.lexema, "palavra-reservada");
            } else {
                strcpy(tk.token, "ID");
                inserirTS(tk.lexema, "identificador");
            }

            tk.linha = linha;
            tk.coluna = col_inicio;
            return tk;
        }

        // NUMEROS
        if (isdigit(c)) {
            tk.lexema[i++] = c;
            int isReal = 0;

            while (isdigit(c = fgetc(fp))) {
                tk.lexema[i++] = c;
                coluna++;
            }

            if (c == '.') {
                isReal = 1;
                tk.lexema[i++] = c;
                coluna++;

                if (!isdigit(c = fgetc(fp))) {
                    erro('.');
                    break;
                }

                do {
                    tk.lexema[i++] = c;
                    coluna++;
                } while (isdigit(c = fgetc(fp)));
            }

            tk.lexema[i] = '\0';
            ungetc(c, fp);

            strcpy(tk.token, isReal ? "NUM_REAL" : "NUM_INT");

            tk.linha = linha;
            tk.coluna = col_inicio;
            return tk;
        }

        // COMENTÁRIO
        if (c == '{') {
            while ((c = fgetc(fp)) != EOF && c != '}') {
                if (c == '\n') linha++;
            }

            if (c == EOF) {
                FILE *f = fopen("../saida/saida/erros.err", "a");
                fprintf(f, "Erro: comentario nao fechado linha %d\n", linha);
                fclose(f);
            }

            continue;
        }

        // OPERADORES
        tk.lexema[0] = c;
        tk.lexema[1] = '\0';

        switch (c) {
            case '+': strcpy(tk.token, "OP_AD"); break;
            case '-': strcpy(tk.token, "OP_MIN"); break;
            case '*': strcpy(tk.token, "OP_MUL"); break;
            case '/': strcpy(tk.token, "OP_DIV"); break;

            case '=': strcpy(tk.token, "OP_EQ"); break;

            case '<':
                c = fgetc(fp);
                if (c == '=') {
                    strcpy(tk.token, "OP_LE");
                    tk.lexema[1] = '=';
                    tk.lexema[2] = '\0';
                } else if (c == '>') {
                    strcpy(tk.token, "OP_NE");
                    tk.lexema[1] = '>';
                    tk.lexema[2] = '\0';
                } else {
                    strcpy(tk.token, "OP_LT");
                    ungetc(c, fp);
                }
                break;

            case '>':
                c = fgetc(fp);
                if (c == '=') {
                    strcpy(tk.token, "OP_GE");
                    tk.lexema[1] = '=';
                    tk.lexema[2] = '\0';
                } else {
                    strcpy(tk.token, "OP_GT");
                    ungetc(c, fp);
                }
                break;

            case ':':
                c = fgetc(fp);
                if (c == '=') {
                    strcpy(tk.token, "OP_ASS");
                    tk.lexema[1] = '=';
                    tk.lexema[2] = '\0';
                } else {
                    strcpy(tk.token, "SMB_COL");
                    ungetc(c, fp);
                }
                break;

            case ';': strcpy(tk.token, "SMB_SEM"); break;
            case ',': strcpy(tk.token, "SMB_COM"); break;
            case '(': strcpy(tk.token, "SMB_OPA"); break;
            case ')': strcpy(tk.token, "SMB_CPA"); break;
            case '.': strcpy(tk.token, "SMB_DOT"); break;

            default:
                erro(c);
                continue;
        }

        tk.linha = linha;
        tk.coluna = col_inicio;
        return tk;
    }

    strcpy(tk.token, "EOF");
    return tk;
}