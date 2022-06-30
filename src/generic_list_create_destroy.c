/*
** EPITECH PROJECT, 2021
** rpg
** File description:
** generic_list_create_and_destroy.c
*/

#include <stdlib.h>
#include "list.h"

void *_list_new_node(
__attribute__((unused)) void *item, size_t size)
{
    void *node = malloc(size);
    return node;
}

void destroy_char_list(void *node)
{
    free(((list(char *) *) (node))->data);
}
