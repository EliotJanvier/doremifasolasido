#ifndef EVALUTATORS_H_
#define EVALUTATORS_H_
#include "structs.h"

obj_t eval_node_int(tree_t tree);
obj_t eval_node_op(tree_t tree);
obj_t eval_node_kw(tree_t tree);

#endif
