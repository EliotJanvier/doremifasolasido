#ifndef TREE_H_
#define TREE_H_

typedef union obj {
    int i;
    char *s;
} obj_t;


typedef struct node {
    obj_t obj;
    int node_id;
    struct node *first;
    struct node *second;
    struct node *third;
} node_t;

typedef node* tree_t;

int evalute(tree_t);
tree_t new_tree(obj_t, int, tree_t, tree_t, tree_t);

#endif
