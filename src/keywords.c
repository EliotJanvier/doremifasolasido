#include <stdio.h>
#include "../include/keyword.h"
#include "../include/tree.h"
#include "structs.h"

obj_t keyword_show(tree_t tree)
{
    if (tree->first == NULL) {
        printf("null\n");
        return (obj_t) 0;
    }
    switch (tree->first->node_type)
    {
    case NODE_INT:
        printf("%d\n", tree->first->obj.ival);
        break;
    default:
        break;
    }
    return (obj_t) 0;
}
