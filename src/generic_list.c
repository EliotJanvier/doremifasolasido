/*
** EPITECH PROJECT, 2021
** modular
** File description:
** main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

void l_list_init(void *list, void (*destructor)(void *))
{
    list_internal_t *base = list;

    base->next = base;
    base->prev = base;
    base->destroy = destructor;
}

void l_list_insert_before(void *here, void *node)
{
    list_internal_t *l_here = (list_internal_t *) here;
    list_internal_t *l_node = (list_internal_t *) node;

    if (node != NULL) {
        l_node->next = l_here;
        l_node->prev = l_here->prev;
    }
    if (here != NULL && l_here->prev != NULL)
        l_here->prev->next = l_node;
    if (here != NULL)
        l_here->prev = l_node;
}

void l_list_pushback(void *head, void *node)
{
    list_internal_t *base = head;
    list_internal_t *tmp = node;

    tmp->next = base;
    tmp->prev = base->prev;
    base->prev->next = tmp;
    base->prev = tmp;
}

void l_list_push(void *list, void *node)
{
    list_internal_t *l_node = node;
    list_internal_t **l_list = list;

    l_node->next = *l_list;
    l_node->prev = (*l_list)->prev;
    (*l_list)->prev = l_node;
    l_node->prev->next = l_node;
}

void l_list_remove_node(void *list)
{
    list_internal_t *l_list = list;

    if (l_list == NULL)
        return;
    if (l_list->next != NULL)
        l_list->next->prev = l_list->prev;
    if (l_list->prev != NULL)
        l_list->prev->next = l_list->next;
}
