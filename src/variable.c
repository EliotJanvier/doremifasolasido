#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../hel.tab.h"

#include "../include/structs.h"

extern variable_t *memory;
extern int mem_size;

void create_var(int _type, char *_name, void *_value)
{
    memory = realloc(memory, sizeof(variable_t) * ++mem_size);
    memory[mem_size - 1].type = _type;
    memory[mem_size - 1].name = strdup(yylval.string);
    memory[mem_size - 1].adress = mem_size - 1;
    memory[mem_size - 1].ptr = _value;
}

int get_var_index_by_name(char *name)
{
    for (int i = 0; i < mem_size; ++i) {
        if (strcmp(memory[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

variable_t *get_var_by_name(char *name) {
    int index = get_var_index_by_name(name);

    if (index < 0)
        return NULL;
    return &(memory[index]);
}
