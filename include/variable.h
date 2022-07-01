#ifndef VAR_H_
#define VAR_H_
#include "structs.h"

extern int yyerror(char *s);

#define assign_value_to_var_from_index(mem_index, value) \
    do { \
        if (!memory[mem_index].ptr) \
            memory[mem_index].ptr = malloc(sizeof(value)); \
        *((typeof(value) *) (memory[mem_index].ptr)) = value; \
    } while (0)

#define assign_value_to_var(var, value) \
    do { \
        if (!var) { \
            yyerror("var does not exist"); \
        } \
        if (!var->ptr) \
            var->ptr = malloc(sizeof(value)); \
        *((typeof(value) *) (var->ptr)) = value; \
    } while (0)

void create_var(int _type, char *_name, void *_value);

variable_t *get_var_by_name(char *name);

int get_var_index_by_name(char *name);

obj_t *get_var_value_by_name(char *name);

#endif
