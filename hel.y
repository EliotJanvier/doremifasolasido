%{
    #include "./include/structs.h"
    #include "./include/variable.h"
    #include "./include/show.h"
    #include "./include/list.h"
    #include "./include/tree.h"
    #include "./include/keyword.h"
    #include "./include/var_cst.h"
    #include "./include/evaluators.h"
    #include <stdlib.h>
    #include <string.h>



    int yylex();
    int yyerror();
    void create_var(int _type, char *_name, void *_value);

    #define palloc(_type, _val, name) \
    type *name = malloc(sizeof(type)); \
    *name = _val

    extern obj_t buffer = (obj_t) 0;
    extern tree_t tree_buffer[3] = {0};

    #define node_create(this, type, obj, first, second, third) \
        do { \
            buffer = (obj_t) obj; \
            tree_buffer[0] = first; \
            tree_buffer[1] = second; \
            tree_buffer[2] = third; \
            this = new_tree(type, (obj_t) obj, node_id++, first, second, third); \
        } while (0);

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
%type<tree> input

%type<num> type
%type<tree> var
%type<tree> string










%%

input:
    statement                {
        if (ast_root == NULL || ast_root->node_id > $1->node_id) {
            ast_root = $1;
        }
    }
|   statement input         {
        if (ast_root == NULL || ast_root->node_id > $1->node_id) {
            ast_root = $1;
        }
        $1->next = $2;
    }
;

statement:
    exp SEMICOLON           {
        $$ = $1;
    }
;

exp:
    NUM                     {node_create($$, NODE_INT, $1, NULL, NULL, NULL);}
|   LPAREN exp RPAREN       {$$ = $2;}
|   exp PLUS exp            {node_create($$, NODE_OPERATOR, operators[OP_ADD], $1, $3, NULL);}
|   exp MINUS exp           {node_create($$, NODE_OPERATOR, operators[OP_SUB], $1, $3, NULL);}
|   exp TIMES exp           {node_create($$, NODE_OPERATOR, operators[OP_MUL], $1, $3, NULL);}
|   exp DIVIDED_BY exp      {node_create($$, NODE_OPERATOR, operators[OP_DIV], $1, $3, NULL);}
|   keyword_exp
|   var
;

keyword_exp:
    KW_SHOW exp              {node_create($$, NODE_KW, (obj_t) keyword_handlers[KWORD_SHOW], $2, NULL, NULL);}
;

type:
    TYPE_INT                {$$ = TYPE_INT;}
;

var:
    type string             {node_create($$, NODE_VARIABLE, $1, $2, NULL, NULL);}
|   string                  {node_create($$, NODE_VARIABLE, $1, NULL, NULL, NULL);}
;

string:
    STRING                  {node_create($$, NODE_STRING, $1, NULL, NULL, NULL);}


%%










void show_tree(tree_t tree) {
    if (tree == NULL)
        return;
    printf("[%p]\n", tree);
    show_tree(tree->second);
}

int main()
{
    // #ifdef YYDEBUG
    //     yydebug = 1;
    // #endif

    yyparse();


    evaluate(ast_root);

    // tree_destroy(ast_root);
    free(memory);
    return 0;
}

extern int yyerror(char *s)
{
    printf("Error: [%s]\n", s);
    return 0;
}
