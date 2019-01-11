#ifndef SLL_LIB_H
#define SLL_LIB_H

#include <sn_type.h>

typedef struct sll_node{
    struct sll_node *next;
}SLL_NODE;

typedef struct sll_list{
    SLL_NODE *head;
    SLL_NODE *tail;
}SLL_LIST;

typedef void * (*pmalloc)(UINT32 size);
typedef STATUS (*pfree)(void *ptr);

typedef BOOL (*node_handle)(SLL_NODE *node, INT32 param);



extern SLL_LIST * sll_create(pmalloc func_malloc);
extern STATUS sll_delete(pfree func_free, SLL_LIST *list);
extern STATUS sll_init(SLL_LIST *list);
extern STATUS sll_terminate(SLL_LIST *list);
extern INT32 sll_count(SLL_LIST *list);
extern SLL_NODE *sll_get(SLL_LIST * list);
extern STATUS sll_put_at_head(SLL_LIST *list, SLL_NODE * node);
extern STATUS sll_put_at_tail(SLL_LIST *list, SLL_NODE * node);
extern STATUS sll_remove_node(SLL_LIST * list, pfree func_free, SLL_NODE *node);
extern SLL_NODE *sll_previous(SLL_LIST *list, SLL_NODE *node);
extern SLL_NODE *sll_each(SLL_LIST *list, node_handle handle, UINT32 param);

#endif /* SLL_LIB_H */
