#ifndef LIST_LIB_H
#define LIST_LIB_H

#include <sn_type.h>

typedef struct list_node{
    struct list_node *prev;
    struct list_node *next;
}LIST_NODE;

typedef struct{
    LIST_NODE   node;
    UINT32      count;
}LIST;

typedef void *(*list_malloc_func)(UINT32 size);
typedef void  (*list_free_func)(void *ptr);

extern STATUS list_init(LIST *list);
extern STATUS list_insert(LIST *list, LIST_NODE *prev, LIST_NODE *node);
extern STATUS list_add(LIST *list, LIST_NODE *node);
extern STATUS list_delete(LIST *list, list_free_func free, LIST_NODE *node);
extern STATUS list_count(LIST *list);
extern LIST_NODE *list_first(LIST *list);
extern LIST_NODE *list_last(LIST *list);
extern LIST_NODE *list_get(LIST *list);
extern LIST_NODE *list_previous(LIST_NODE *node);
extern LIST_NODE *list_next(LIST_NODE *node);
extern UINT32 list_index_find(LIST *list, LIST_NODE *node);
extern STATUS list_concatenate(LIST *dst_list, LIST *add_list);
extern STATUS list_extract(LIST *src_list, LIST_NODE *start_node, \
                                    LIST_NODE *end_node, LIST *dst_list);
extern LIST_NODE *list_Nth(LIST *list, UINT32 node_num);
extern LIST_NODE *list_Nstep(LIST_NODE *node, INT32 Nstep);
extern STATUS list_free(LIST *list, list_free_func free_func);
#endif /* LIST_LIB_H */
