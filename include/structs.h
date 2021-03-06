#ifndef STRUCTS_H_
#define STRUCTS_H_
#include "operators.h"

typedef struct variable variable_t;

//AST

typedef struct node node_t;

typedef node_t* tree_t;

typedef union obj obj_t;
typedef obj_t (*keyword_handler_t)(tree_t tree);

typedef int (*basic_operator_t)(int, int);

enum node_type {
    NODE_INT,
    NODE_OPERATOR,
    NODE_KW
};

union obj {
    int ival;
    char *sval;
    basic_operator_t op;
    keyword_handler_t kw_hdl;
};

struct node {
    obj_t obj;
    int node_id;
    int node_type;
    struct node *first;
    struct node *second;
    struct node *third;
    struct node *next;
};

enum keywords {
    KWORD_SHOW
};

static const basic_operator_t operators[] = {
    op_add,
    op_sub,
    op_mul,
    op_div
};

enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV
};



#endif


