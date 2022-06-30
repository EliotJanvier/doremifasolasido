#ifndef KEYWORD_H_
#define KEYWORD_H_
#include "tree.h"
#include "structs.h"


obj_t keyword_show(tree_t tree);

static const keyword_handler_t keyword_handlers[] = {
    [KWORD_SHOW] = &keyword_show
};


#endif
