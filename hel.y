%{
    #include "./include/structs.h"
    #include "./include/variable.h"
    #include "./include/show.h"
    #include "./include/list.h"
    #include "./include/tree.h"
    #include "./include/keyword.h"
    #include <stdlib.h>
    #include <string.h>



    int yylex();
    int yyerror();
    void create_var(int _type, char *_name, void *_value);

    #define palloc(_type, _val, name) \
    type *name = malloc(sizeof(type)); \
    *name = _val

    extern size_t mem_size = 0;
    extern variable_t *memory = NULL;

    tree_t ast_root = NULL;
    static int node_id = 0;
%}

%union {
    struct node *tree;
    int num;
    char character;
    char *string;
    struct variable *var;
};


%token DEBUG

%token ANY
%token<num> NUM
%token SEMICOLON
%token PLUS
%token MINUS
%token DIVIDED_BY
%token TIMES
%token<string> STRING
%token VARNAME
%token EQUALS
%token DQUOTES
%token LPAREN
%token RPAREN
%token LBRACKET
%token RBRACKET

%token TYPE_STRING
%token<num> TYPE_INT

%token<tree> KW_SHOW
%token KW_IF

%type<tree> exp
%type<tree> keyword_exp
%type<tree> statement


%%


input:
|   statement input
;

statement:
    statement statement     {$1->next = $2;}
|   exp SEMICOLON           {if (ast_root == NULL) ast_root = $1;}
;

exp:
    NUM                     {$$ = new_tree(NODE_INT, (obj_t) $1, node_id++, NULL, NULL, NULL);}
|   exp MINUS exp           {$$ = new_tree(NODE_OPERATOR, (obj_t) OP_SUB, node_id++, $1, $3, NULL);}
|   exp PLUS exp            {$$ = new_tree(NODE_OPERATOR, (obj_t) OP_ADD, node_id++, $1, $3, NULL);}
|   exp TIMES exp           {$$ = new_tree(NODE_OPERATOR, (obj_t) OP_MUL, node_id++, $1, $3, NULL);}
|   exp DIVIDED_BY exp      {$$ = new_tree(NODE_OPERATOR, (obj_t) OP_DIV, node_id++, $1, $3, NULL);}
|   keyword_exp
;

keyword_exp:
    KW_SHOW exp              {$$ = new_tree(NODE_KW, (obj_t) keyword_handlers[KWORD_SHOW], node_id++, $2, NULL, NULL);}
;


%%

int main()
{
    // #ifdef YYDEBUG
    //     yydebug = 1;
    // #endif

    yyparse();

    evaluate(ast_root);

    tree_destroy(ast_root);
    free(memory);
    return 0;
}

extern int yyerror(char *s)
{
    printf("Error: [%s]\n", s);
    return 0;
}
