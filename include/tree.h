#ifndef TREE_H_
#define TREE_H_
#include "structs.h"

obj_t evaluate(tree_t);
tree_t new_tree(enum node_type, obj_t, int, tree_t, tree_t, tree_t);

void tree_destroy(tree_t tree);

#endif
