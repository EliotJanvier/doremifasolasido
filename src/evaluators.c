#include <stdlib.h>
#include <string.h>
#include "../include/structs.h"
#include "../include/tree.h"
#include "../include/variable.h"

obj_t eval_node_int(tree_t tree)
{
    return (obj_t) tree->obj.ival;
}

obj_t eval_node_op(tree_t tree)
{
    tree->obj.ival = tree->obj.op(evaluate(tree->first).ival, evaluate(tree->second).ival);
    tree->node_type = NODE_INT;
    return (obj_t) tree->obj.ival;
}

obj_t eval_node_kw(tree_t tree)
{
    return tree->obj.kw_hdl(tree);
}

obj_t *eval_node_variable(tree_t tree)
{
    char **tmp = NULL;

    if (tree->first) {
        tmp = malloc(sizeof(char *));
        printf("first is %p and its type is %d\n", tree->first, tree->first->node_type);
        *tmp = strdup(evaluate(tree->first).sval); //get the name of the variable
        create_var(tree->obj.ival, *tmp, 0);
        tree->first = NULL; //to prevent multiple creation when evaluating multiple times
        return (obj_t *) tmp; //returning the name
    }
    return get_var_value_by_name(tree->obj.sval);
}

obj_t eval_node_string(tree_t tree)
{
    printf("string value is [%s]\n", tree->obj.sval);
    return (obj_t) tree->obj.sval;
}
