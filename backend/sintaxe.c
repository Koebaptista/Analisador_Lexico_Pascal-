#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "sintaxe.h"

static FILE  *fonte;      
static FILE  *saida;  
static Token  tokenAtual; 
static int    erros = 0;  


typedef struct {
    char linhas[500][200];
    int qtd;
} Arvore;

Arvore arvore;

void addArvore(char *texto) {

    strcpy(arvore.linhas[arvore.qtd], texto);
    arvore.qtd++;
}

void imprimirArvore() {

    fprintf(saida,
        "\n========================================\n"
        "ARVORE SINTATICA\n"
        "========================================\n\n");

    for(int i = 0; i < arvore.qtd; i++) {

        fprintf(saida,
                "%s\n",
                arvore.linhas[i]);
    }
}


static void emiteProd(const char *regra) {
    fprintf(saida,  "%s\n", regra);
    printf("%s\n", regra);
}

static void erroSintatico(const char *msg) {

    FILE *ferr = fopen("../saida/erros.err", "a");

    if (strcmp(tokenAtual.token, "EOF") == 0) {

        fprintf(stderr,
                "%d:fim de arquivo nao esperado.\n",
                tokenAtual.linha);

        fprintf(saida,
                "%d:fim de arquivo nao esperado.\n",
                tokenAtual.linha);

        if (ferr) {
            fprintf(ferr,
                    "%d:fim de arquivo nao esperado.\n",
                    tokenAtual.linha);
        }

    } else {

        fprintf(stderr,
                "%d:token nao esperado [%s].\n",
                tokenAtual.linha,
                tokenAtual.lexema);

        fprintf(saida,
                "%d:token nao esperado [%s].\n",
                tokenAtual.linha,
                tokenAtual.lexema);

        if (ferr) {
            fprintf(ferr,
                    "%d:token nao esperado [%s].\n",
                    tokenAtual.linha,
                    tokenAtual.lexema);
        }
    }

    if (ferr)
        fclose(ferr);

    (void)msg;
    erros++;

    exit(1);
}

static void avanca(void) {
    tokenAtual = proximoToken(fonte);
}

static void casaToken(const char *esperado) {
    if (strcmp(tokenAtual.token, esperado) == 0) {
        avanca();
    } else {
        erroSintatico(esperado);
    }
}

static void bloco(void);
static void parteDeclaracoesVar(void);
static void declaracaoVar(void);
static void listaIdentificadores(void);
static void tipo(void);
static void comandoComposto(void);
static void comando(void);
static void atribuicao(void);
static void cmdCondicional(void);
static void cmdRepetitivo(void);
static void expressao(void);
static void exprSimples(void);
static void termo(void);
static void fator(void);


void programa(void) {
    addArvore("programa");
    emiteProd("<programa> ::= program <identificador> ; <bloco> .");
    casaToken("KW_program");
    casaToken("ID");
    casaToken("SMB_SEM");
    bloco();
    casaToken("SMB_DOT");
    /* Após o ponto final esperamos EOF */
    if (strcmp(tokenAtual.token, "EOF") != 0) {
        erroSintatico("EOF apos ponto final");
    }
}

static void bloco(void) {
    addArvore("└── bloco");
    emiteProd("<bloco> ::= <parte_decl_var> <cmd_composto>");
    parteDeclaracoesVar();
    comandoComposto();
}

static void parteDeclaracoesVar(void) {
    if (strcmp(tokenAtual.token, "KW_var") == 0) {
        emiteProd("<parte_decl_var> ::= var <decl_var> { ; <decl_var> } ;");
        casaToken("KW_var");
        declaracaoVar();
        while (strcmp(tokenAtual.token, "SMB_SEM") == 0) {
           
            casaToken("SMB_SEM");
            if (strcmp(tokenAtual.token, "ID") == 0) {
                declaracaoVar();
            } else {
                break; 
            }
        }
    } else {
        emiteProd("<parte_decl_var> ::= (vazio)");
    }
}

static void declaracaoVar(void) {
     addArvore("    ├── declaracao");
    emiteProd("<decl_var> ::= <lista_id> : <tipo>");
    listaIdentificadores();
    casaToken("SMB_COL");
    tipo();
}

static void listaIdentificadores(void) {
    emiteProd("<lista_id> ::= <identificador> { , <identificador> }");
    casaToken("ID");
    while (strcmp(tokenAtual.token, "SMB_COM") == 0) {
        casaToken("SMB_COM");
        casaToken("ID");
    }
}

static void tipo(void) {
    if (strcmp(tokenAtual.token, "KW_integer") == 0) {
        emiteProd("<tipo> ::= integer");
        casaToken("KW_integer");
    } else if (strcmp(tokenAtual.token, "KW_real") == 0) {
        emiteProd("<tipo> ::= real");
        casaToken("KW_real");
    } else {
        erroSintatico("tipo esperado (integer ou real)");
    }
}

static void comandoComposto(void) {
    emiteProd("<cmd_composto> ::= begin <comando> ; { <comando> ; } end");
    casaToken("KW_begin");
    comando();
    casaToken("SMB_SEM");
    while (strcmp(tokenAtual.token, "KW_end") != 0) {
        comando();
        casaToken("SMB_SEM");
    }
    casaToken("KW_end");
}


static void comando(void) {
    if (strcmp(tokenAtual.token, "ID") == 0) {
        emiteProd("<comando> ::= <atribuicao>");
        atribuicao();
    } else if (strcmp(tokenAtual.token, "KW_begin") == 0) {
        emiteProd("<comando> ::= <cmd_composto>");
        comandoComposto();
    } else if (strcmp(tokenAtual.token, "KW_if") == 0) {
        emiteProd("<comando> ::= <cmd_condicional>");
        cmdCondicional();
    } else if (strcmp(tokenAtual.token, "KW_while") == 0) {
        emiteProd("<comando> ::= <cmd_repetitivo>");
        cmdRepetitivo();
    } else {
        erroSintatico("comando esperado");
    }
}


static void atribuicao(void) {
    addArvore("        ├── atribuicao");
    emiteProd("<atribuicao> ::= <variavel> := <expressao>");
    emiteProd("<variavel> ::= <identificador>");
    casaToken("ID");
    casaToken("OP_ASS");
    expressao();
}


static void cmdCondicional(void) {
    addArvore("        ├── if");
    emiteProd("<cmd_condicional> ::= if <expressao> then <comando> [ else <comando> ]");
    casaToken("KW_if");
    expressao();
    casaToken("KW_then");
    comando();
    if (strcmp(tokenAtual.token, "KW_else") == 0) {
        casaToken("KW_else");
        comando();
    }
}

static void cmdRepetitivo(void) {
    addArvore("        └── while");
    emiteProd("<cmd_repetitivo> ::= while <expressao> do <comando>");
    casaToken("KW_while");
    expressao();
    casaToken("KW_do");
    comando();
}


static int ehRelacao(void) {
    return (strcmp(tokenAtual.token, "OP_EQ") == 0 ||
            strcmp(tokenAtual.token, "OP_NE") == 0 ||
            strcmp(tokenAtual.token, "OP_LT") == 0 ||
            strcmp(tokenAtual.token, "OP_LE") == 0 ||
            strcmp(tokenAtual.token, "OP_GT") == 0 ||
            strcmp(tokenAtual.token, "OP_GE") == 0);
}


static void expressao(void) {
    emiteProd("<expressao> ::= <expr_simples> [ <relacao> <expr_simples> ]");
    exprSimples();
    if (ehRelacao()) {
        char buf[80];
        sprintf(buf, "<relacao> ::= %s", tokenAtual.lexema);
        emiteProd(buf);
        avanca();
        exprSimples();
    }
}

static void exprSimples(void) {
    emiteProd("<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }");
    if (strcmp(tokenAtual.token, "OP_AD")  == 0 ||
        strcmp(tokenAtual.token, "OP_MIN") == 0) {
        avanca();
    }
    termo();
    while (strcmp(tokenAtual.token, "OP_AD")  == 0 ||
           strcmp(tokenAtual.token, "OP_MIN") == 0) {
        avanca();
        termo();
    }
}

static void termo(void) {
    emiteProd("<termo> ::= <fator> { ( * | / ) <fator> }");
    fator();
    while (strcmp(tokenAtual.token, "OP_MUL") == 0 ||
           strcmp(tokenAtual.token, "OP_DIV") == 0) {
        avanca();
        fator();
    }
}


static void fator(void) {
    if (strcmp(tokenAtual.token, "ID") == 0) {
        emiteProd("<fator> ::= <variavel>");
        emiteProd("<variavel> ::= <identificador>");
        casaToken("ID");
    } else if (strcmp(tokenAtual.token, "NUM_INT")  == 0 ||
               strcmp(tokenAtual.token, "NUM_REAL") == 0) {
        emiteProd("<fator> ::= <numero>");
        avanca();
    } else if (strcmp(tokenAtual.token, "SMB_OPA") == 0) {
        emiteProd("<fator> ::= ( <expressao> )");
        casaToken("SMB_OPA");
        expressao();
        casaToken("SMB_CPA");
    } else {
        erroSintatico("fator esperado");
    }
}

void initParser(FILE *fp, FILE *out) {
    fonte = fp;
    saida = out;
    avanca();
}