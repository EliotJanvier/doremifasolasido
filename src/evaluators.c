#include "../include/structs.h"
#include "../include/tree.h"

obj_t eval_node_int(tree_t tree)
{
    return (obj_t) tree->obj.ival;
}

obj_t eval_node_op(tree_t tree)
{
    tree->node_type = NODE_INT;
    tree->obj.ival = tree->obj.op(evaluate(tree->first).ival, evaluate(tree->second).ival);
    return (obj_t) tree->obj.ival;
}

obj_t eval_node_kw(tree_t tree)
{
    return tree->obj.kw_hdl(tree);
}
