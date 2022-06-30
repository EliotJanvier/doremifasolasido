
#ifndef CF5310F0_0525_487F_9AD3_4DA63F5BD456
    #define CF5310F0_0525_487F_9AD3_4DA63F5BD456
    #include <stdlib.h>

typedef struct list_internal_s list_internal_t;
struct list_internal_s {
    list_internal_t *next;
    list_internal_t *prev;
    void (*destroy)(void *);
};

void l_list_init(void *list, void (*destructor)(void *));
void l_list_push(void *list, void *node);
void l_list_remove_node(void *list);
void *_list_new_node(void *item, size_t size);
void l_list_pushback(void *head, void *node);
void l_list_insert_before(void *here, void *node);

    #define list(type) \
    struct { \
        list_internal_t base; \
        type data; \
    }

    #define list_set_ptr(dest, list) \
    dest = (void *) list;

    #define list_init(list, destructor) \
    l_list_init(list, destructor)

    #define list_push(head_ptr, node) \
    do { \
        l_list_push(head_ptr, node); \
        *head_ptr = (typeof(*head_ptr)) node;\
    } while (0)

    #define list_destroy_node(node) \
    do { \
        if (node == NULL) \
            break; \
        if (node->base.destroy) { \
            node->base.destroy(node); \
        } \
        if (node->base.next == &(node->base)) {\
            free(node); \
            node = NULL; \
            break; \
        } \
        free(node); \
    } while (0)

    #define next(list) \
    ((typeof(list)) ((list)->base.next))

    #define prev(list) \
    ((typeof(list)) ((list)->base.prev))

    #define list_pop(node_ptr, popped) \
    do { \
        if (*node_ptr == NULL) { \
            popped = NULL; \
            break; \
        } \
        if (next(*node_ptr) == *node_ptr) { \
            popped = (typeof(popped)) *node_ptr; \
            *node_ptr = NULL; \
        } else { \
            l_list_remove_node(*node_ptr); \
            popped = (typeof(popped)) (*node_ptr); \
            *node_ptr = next(*node_ptr); \
        } \
    } while (0)

    #define list_erase_node(node_ptr) \
    do { \
        typeof((*node_ptr)) popped; \
        list_pop(node_ptr, popped); \
        list_destroy_node(popped); \
    } while (0)

    #define list_create_node(item, node, destructor) \
    do { \
        node = malloc(sizeof(list(typeof(item)))); \
        if (node == NULL) \
            break; \
        list_init(node, destructor); \
        node->data = item; \
    } while (0)

    #define list_foreach(varname, list) \
    for (typeof(list) varname = list; varname != NULL; \
    varname = (next(varname) == list) ? NULL : next(varname))

    #define list_clear(list) \
    do { \
        list_erase_node(&list); \
    } while (list != NULL)

    #define list_pushback(head, node) \
    do { \
        if (head == NULL) { \
            head = (typeof(head)) node; \
            break; \
        } \
        l_list_pushback(head, node); \
    } while (0)

    #define list_insert_before(here, node) \
    do {\
        l_list_insert_before(here, node); \
    } while (0)

#endif
