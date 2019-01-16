#ifndef DLL_LIB_H
#define DLL_LIB_H

#include <sn_type.h>

/* structure defien */
typedef struct dll_node{
    struct dll_node *prev;
    struct dll_node *next;
}DLL_NODE;

typedef struct dll_list{
    struct dll_node *head;
    struct dll_node *tail;
}DLL_LIST;

/* func ptr define */
typedef void *(*dll_malloc)(UINT32 size);
typedef STATUS (*dll_free)(void *ptr);
typedef BOOL (*dll_each_func)(DLL_NODE * node, UINT32 param);

/* declare define */
extern STATUS dll_init(DLL_LIST *list);
extern DLL_LIST *dll_create(dll_malloc malloc);
extern STATUS dll_delete(DLL_LIST *list, dll_free free);
extern STATUS dll_terminate(DLL_LIST * list);
extern STATUS dll_insert(DLL_LIST *list, DLL_NODE *prev, DLL_NODE *node);
extern STATUS dll_add(DLL_LIST *list, DLL_NODE *node);
extern STATUS dll_remove(DLL_LIST *list, dll_free free, DLL_NODE *node);
extern DLL_NODE *dll_get(DLL_LIST * list);
extern int dll_count(DLL_LIST * list);
extern DLL_NODE * dllEach(DLL_LIST *list, dll_each_func func, UINT32 param);

#endif  /* DLL_LIB_H */
