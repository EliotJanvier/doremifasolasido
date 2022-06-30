%{
    #include "./include/structs.h"
    #include "./include/variable.h"
    #include "./include/show.h"
    #include "./include/list.h"
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

    extern int *depth_execute = NULL;
    extern int detpth = 1;
%}

%union {
    int num;
    char character;
    char *string;
    struct variable *var;
};

%token DEBUG

%token ANY
%token EOL
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

%token KW_SHOW
%token KW_IF

%type<num> exp
%type<var> variable
%type<num> type
%type<num> condition

%%

input:
|   line input
;

line:
    debug
|   line_jumps
|   statement

;

exp:
    NUM {$$ = $1;}
|   LPAREN exp RPAREN {$$ = $2;}
|   exp MINUS exp {$$ = $1 - $3;}
|   exp PLUS exp {$$ = $1 + $3;}
|   exp TIMES exp {$$ = $1 * $3;}
|   exp DIVIDED_BY exp {$$ = $1 / $3;}
|   variable {$$ = *(int *) $1->ptr;}
;

line_jumps:
    EOL
|   line_jumps EOL
;

type:
    TYPE_INT {$$ = yylval.num;}

new_var:
    type STRING {
            create_var($1, $2, 0);
        }
;

debug:
    DEBUG {
        for (int i = 0; i < mem_size; ++i) {
            printf("var: [%s]\n", memory[i].name);
        }
    }

show:
    KW_SHOW STRING {show_variable(get_var_by_name($2));}
;

variable:
    STRING {$$ = get_var_by_name(yyval.string);}
;

if_else:
    KW_IF condition EOL statement

condition:
    exp {$$ = $1}
;

statement:
    SEMICOLON
|   statement statement
|   new_var EQUALS exp SEMICOLON {assign_value_to_var_from_index(mem_size - 1, $3);}
|   new_var SEMICOLON
|   variable EQUALS exp SEMICOLON {assign_value_to_var($1, $3);}
|   show SEMICOLON
|   exp SEMICOLON {printf("%d\n", $1);}
|   exp SEMICOLON EOL {printf("%d\n", $1);}
|   exp EOL {printf("%d\n", $1);}
;

block:
    LBRACKET {
        depth_execute = realloc(depth_execute, sizeof(int) * (depth + 1));
        depth_execute[depth] = 1;
        ++depth;
    }
|   RBRACKET {
        depth_execute = realloc(depth_execute, sizeof(int) * (depth - 1));
        --depth;
    }
;
%%

int main()
{
    depth_execute = malloc(sizeof(int));
    depth_execute[0] = 1; //execute entry point;

    yyparse();

    free(memory);
    return 0;
}

extern int yyerror(char *s)
{
    printf("Error: [%s]\n", s);
    return 0;
}
