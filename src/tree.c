#include <stdlib.h>
#include "../include/tree.h"
#include "../include/evaluators.h"

typedef const obj_t(*evaluator_t)(tree_t);
static evaluator_t evaluators[] = {
    eval_node_int,
    eval_node_op,
    eval_node_kw
};

obj_t evaluate(tree_t tree)
{
    obj_t result;

    if (!tree)
        return (obj_t) 0;
    if (evaluators[tree->node_type])
        result = evaluators[tree->node_type](tree);
    else
        result = (obj_t) 0;
    evaluate(tree->next);
    return result;
}

tree_t new_tree(enum node_type type, obj_t obj, int node_id, tree_t first, tree_t second, tree_t third)
{
    tree_t tree = malloc(sizeof(node_t));

    if (!tree)
        return NULL;
    tree->node_type = type;
    tree->obj = obj;
    tree->node_id = node_id;
    tree->first = first;
    tree->second = second;
    tree->third = third;
    tree->next = NULL;
    return tree;
}

void tree_destroy(tree_t tree)
{
    if (!tree)
        return;
    if (tree->first)
        tree_destroy(tree->first);
    if (tree->second)
        tree_destroy(tree->second);
    if (tree->third)
        tree_destroy(tree->third);
    if (tree->next)
        tree_destroy(tree->next);
    free(tree);
}
