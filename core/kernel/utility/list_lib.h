#ifndef LIST_LIB_H
#define LIST_LIB_H

#include <sn_type.h>

typedef struct list_node{
    struct list_node *priv;
    struct list_node *next;
}LIST_NODE;

typedef struct{
    LIST_NODE   *head_node;
    UINT32      count;
}LIST;

extern STATUS list_init(LIST *list);

#endif /* LIST_LIB_H */
