#include <stdlib.h>
#include "../include/tree.h"

int evaluate(tree_t tree)
{

}

tree_t new_tree(obj_t obj, int node_id, tree_t first, tree_t second, tree_t third)
{
    tree_t tree = malloc(sizeof(node_t));

    if (!tree)
        return NULL;
    tree->obj = obj;
    tree->node_id = node_id;
    tree->first = first;
    tree->second = second;
    tree->third = third;
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
    free(tree);
}
