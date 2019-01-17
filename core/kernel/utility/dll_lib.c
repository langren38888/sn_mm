#include <sn_common.h>
#include "dll_lib.h"

DLL_LIST *dll_create(dll_malloc malloc)
{
    DLL_LIST *list = NULL;

    list = (DLL_LIST *)malloc(sizeof(DLL_LIST));

    if(NULL == list)
        return NULL;

    if(OK != dll_init(list))
        return NULL;

    return list;
}

STATUS dll_delete(DLL_LIST *list, dll_free free)
{
    if(NULL == list)
        return ERROR;

    free(list);

    return OK;
}

STATUS dll_init(DLL_LIST *list)
{
    if(NULL == list)
        return ERROR;

    list->head = NULL;
    list->tail = NULL;

    return OK;
}

STATUS dll_terminate(DLL_LIST * list)
{
    /* TODO */
    return OK;
}

/* prev node: the prevous node of the node which to be inserted 
*  if the prev node is empty, we insert the node to the heand of
*  list.
*/
STATUS dll_insert(DLL_LIST *list, DLL_NODE *prev, DLL_NODE *node)
{
    if(NULL == list || NULL == node)
        return ERROR;

    /* initialize the node to be inserted */
    node->next = NULL;
    node->prev = NULL;

    if(NULL == prev){
        if(NULL == list->head){
            list->head = node;
            list->tail = node;
        }else{
            node->next = list->head;
            list->head = node;
            node->next->prev = node;
        }
    }else{
        /* indicated that at least one node in the list */
        node->next = prev->next;
        prev->next = node;

        node->prev = prev;
        if(node->next != NULL)
            node->next->prev = node;

        if(list->tail == prev)
            list->tail = node;
    }

    return OK;
}

/* added the node at the end of the list */
STATUS dll_add(DLL_LIST *list, DLL_NODE *node)
{
    return dll_insert(list, list->tail, node);
}

STATUS dll_remove(DLL_LIST *list, dll_free free, DLL_NODE *node)
{
    if(NULL == list || NULL == node)
        return ERROR;

    if(NULL == node->prev){
        list->head = node->next;
    }else{
        node->prev->next = node->next;
    }

    if(NULL == node->next){
        list->tail = node->prev;
    }else{
        node->next->prev = node->prev;
    }

    if(free != NULL)
        free(node);

    return OK;
}

/* removed and get the first node int list */
DLL_NODE *dll_get(DLL_LIST * list)
{
    DLL_NODE *node = NULL;

    if(NULL == list || NULL == list->head)
        return NULL;

    node = list->head;

    if(NULL != node){
        list->head = node->next;
        if(NULL == node->next){
            list->tail = NULL;
        }else{
            list->head->prev = NULL;
        }
    }

    return node;
}

int dll_count(DLL_LIST * list)
{
    DLL_NODE *node = NULL;
    int ret = 0;

    if(NULL == list)
        return ERROR;

    node = list->head;

    while(node != NULL){
        ret++;
        node = node->next;
    }

    return ret;
}

DLL_NODE * dllEach(DLL_LIST *list, dll_each_func func, UINT32 param)
{
    DLL_NODE *node = NULL;

    if(NULL == list)
        return NULL;

    node = list->head;

    while(node != NULL){
        if((*func)(node, param) != OK)
            break;

        node = node->next;
    }

    return node;
}
