#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../include/structs.h"
#include "../hel.tab.h"

void show_variable(variable_t *var)
{
    if (!var)
        return;
    switch (var->type)
    {
    case TYPE_INT:
        printf("%s = %d\n", var->name, *((int *) var->ptr));
        break;
    default:
        break;
    }
}
