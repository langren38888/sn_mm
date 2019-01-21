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

typedef void *(*list_malloc)(UINT32 size);
typedef void  (*list_free_func)(void *ptr);

extern STATUS list_init(LIST *list);

#endif /* LIST_LIB_H */
