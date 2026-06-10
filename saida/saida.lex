========================================
ANALISE LEXICA
========================================

<KW_program   program     > ( 1,  1)
<ID           sistema     > ( 1,  9)
<SMB_SEM      ;           > ( 1, 16)
<KW_var       var         > ( 3,  1)
<ID           x           > ( 4,  5)
<SMB_COM      ,           > ( 4,  6)
<ID           y           > ( 4,  8)
<SMB_COL      :           > ( 4, 10)
<KW_integer   integer     > ( 4, 12)
<SMB_SEM      ;           > ( 4, 19)
<ID           media       > ( 5,  5)
<SMB_COL      :           > ( 5, 11)
<KW_real      real        > ( 5, 13)
<SMB_SEM      ;           > ( 5, 17)
<KW_begin     begin       > ( 7,  1)
<ID           x           > ( 8,  5)
<OP_ASS       :=          > ( 8,  7)
<NUM_INT      10          > ( 8,  9)
<SMB_SEM      ;           > ( 8, 11)
<ID           y           > ( 9,  5)
<OP_ASS       :=          > ( 9,  7)
<NUM_INT      20          > ( 9,  9)
<SMB_SEM      ;           > ( 9, 11)
<KW_if        if          > (11,  5)
<ID           x           > (11,  8)
<OP_LT        <           > (11, 10)
<ID           y           > (11, 12)
<KW_then      then        > (11, 14)
<ID           media       > (12,  9)
<OP_ASS       :=          > (12, 15)
<SMB_OPA      (           > (12, 17)
<ID           x           > (12, 18)
<OP_AD        +           > (12, 20)
<ID           y           > (12, 22)
<SMB_CPA      )           > (12, 23)
<OP_DIV       /           > (12, 25)
<NUM_INT      2           > (12, 27)
<SMB_SEM      ;           > (12, 28)
<KW_while     while       > (14,  5)
<ID           x           > (14, 11)
<OP_LT        <           > (14, 13)
<ID           y           > (14, 15)
<KW_do        do          > (14, 17)
<ID           x           > (15,  9)
<OP_ASS       :=          > (15, 11)
<ID           x           > (15, 13)
<OP_AD        +           > (15, 15)
<NUM_INT      1           > (15, 17)
<SMB_SEM      ;           > (15, 18)
<KW_end       end         > (16,  1)
<SMB_DOT      .           > (16,  4)


========================================
ANALISE SINTATICA
========================================

<programa> ::= program <identificador> ; <bloco> .
<bloco> ::= <parte_decl_var> <cmd_composto>
<parte_decl_var> ::= var <decl_var> { ; <decl_var> } ;
<decl_var> ::= <lista_id> : <tipo>
<lista_id> ::= <identificador> { , <identificador> }
<tipo> ::= integer
<decl_var> ::= <lista_id> : <tipo>
<lista_id> ::= <identificador> { , <identificador> }
<tipo> ::= real
<cmd_composto> ::= begin <comando> ; { <comando> ; } end
<comando> ::= <atribuicao>
<atribuicao> ::= <variavel> := <expressao>
<variavel> ::= <identificador>
<expressao> ::= <expr_simples> [ <relacao> <expr_simples> ]
<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <numero>
<comando> ::= <atribuicao>
<atribuicao> ::= <variavel> := <expressao>
<variavel> ::= <identificador>
<expressao> ::= <expr_simples> [ <relacao> <expr_simples> ]
<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <numero>
<comando> ::= <cmd_condicional>
<cmd_condicional> ::= if <expressao> then <comando> [ else <comando> ]
<expressao> ::= <expr_simples> [ <relacao> <expr_simples> ]
<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <variavel>
<variavel> ::= <identificador>
<relacao> ::= <
<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <variavel>
<variavel> ::= <identificador>
<comando> ::= <atribuicao>
<atribuicao> ::= <variavel> := <expressao>
<variavel> ::= <identificador>
<expressao> ::= <expr_simples> [ <relacao> <expr_simples> ]
<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= ( <expressao> )
<expressao> ::= <expr_simples> [ <relacao> <expr_simples> ]
<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <variavel>
<variavel> ::= <identificador>
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <variavel>
<variavel> ::= <identificador>
<fator> ::= <numero>
<comando> ::= <cmd_repetitivo>
<cmd_repetitivo> ::= while <expressao> do <comando>
<expressao> ::= <expr_simples> [ <relacao> <expr_simples> ]
<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <variavel>
<variavel> ::= <identificador>
<relacao> ::= <
<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <variavel>
<variavel> ::= <identificador>
<comando> ::= <atribuicao>
<atribuicao> ::= <variavel> := <expressao>
<variavel> ::= <identificador>
<expressao> ::= <expr_simples> [ <relacao> <expr_simples> ]
<expr_simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <variavel>
<variavel> ::= <identificador>
<termo> ::= <fator> { ( * | / ) <fator> }
<fator> ::= <numero>

========================================
ARVORE SINTATICA
========================================

programa
└── bloco
    ├── declaracao
    ├── declaracao
        ├── atribuicao
        ├── atribuicao
        ├── if
        ├── atribuicao
        └── while
        ├── atribuicao

Analise sintatica concluida com sucesso!
