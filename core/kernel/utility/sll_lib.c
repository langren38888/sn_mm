#include <sn_common.h>
#include "sll_lib.h"

SLL_LIST * sll_create(pmalloc func_malloc)
{
    SLL_LIST *list = NULL;

    if(NULL == func_malloc)
        return NULL;

    list = (SLL_LIST *)func_malloc(sizeof(SLL_LIST));

    if(NULL == list)
        return NULL;

    return list;
}

STATUS sll_delete(pfree func_free, SLL_LIST *list)
{
    if(NULL == func_free || NULL == list)
        return ERROR;

    return func_free(list);
}

STATUS sll_init(SLL_LIST *list)
{
    if(NULL == list)
        return ERROR;

    list->head = NULL;
    list->tail = NULL;

    return OK;
}

STATUS sll_terminate(SLL_LIST *list)
{
    if(NULL == list)
        return ERROR;

    /*TODO*/
    return OK;
}

INT32 sll_count(SLL_LIST *list)
{
    SLL_NODE *list_nd = NULL;
    INT32 count = 0;

    if(NULL == list)
        return ERROR;

    list_nd = list->head;

    while(NULL != list_nd){
        count++;
        list_nd = list_nd->next;
    }

    return count;
}

/* get(get, delete and return) the first node of the list */
SLL_NODE *sll_get(SLL_LIST * list)
{
    SLL_NODE *node_get = NULL;

    if(NULL == list)
        return NULL;

    node_get = list->head;

    if(NULL == node_get)
        return NULL;

    if(list->tail == node_get)
        list->tail = NULL;

    list->head = node_get->next;

    return node_get;
}

STATUS sll_put_at_head(SLL_LIST *list, SLL_NODE * node)
{
    if(NULL == list || NULL == node)
        return ERROR;

    /*list is empty and this node is the fisrt node */
    if(NULL == list->head){
        list->tail = node;
    }else{
        node->next = list->head;
    }

    list->head = node;

    return OK;
}

STATUS sll_put_at_tail(SLL_LIST *list, SLL_NODE * node)
{
    if(NULL == list || NULL == node)
        return ERROR;

    if(NULL != list->tail){
        list->tail->next = node;
    }else{/* NULL == list->tail mean's list is empty */
        list->head = node;
    }
    list->tail = node;

    return OK;
}


STATUS sll_remove_node(SLL_LIST * list, pfree func_free, SLL_NODE *node)
{
    SLL_NODE * pnode;
    SLL_NODE * pre_node = NULL;

    if(NULL == list || NULL == node)
        return ERROR;

    pnode = list->head;
    while(pnode != NULL){

        /* find the node */
        if(pnode == node)
            break;

        pnode = pnode->next;
        pre_node = pnode;
    }

    if(NULL != pnode){
        /* there is only one node in the list */
        if(NULL == pre_node){
            list->head = NULL;
            list->tail = NULL;

            if(NULL != func_free)
                return func_free(pnode);
        }

        pre_node->next = pnode->next;

        if(NULL != func_free)
            return func_free(pnode);

    }else{
        return ERROR;
    }
}

/* find the previous node, and the next node node->next */
SLL_NODE *sll_previous(SLL_LIST *list, SLL_NODE *node)
{
    SLL_NODE *pnode = NULL;
    SLL_NODE *pre_node = NULL;

    if(NULL == list || NULL == node)
        return NULL;

    pnode = list->head;

    while(pnode != NULL){

        if(pnode == node){
            /* only one node in the list, pre_node must be NULL */
            break;
        }

        pre_node = pnode;
        pnode = pnode->next;
    }

    return pre_node;
}

/* find the node that make handle return FALSE */
SLL_NODE *sll_each(SLL_LIST *list, node_handle handle, UINT32 param)
{
    SLL_NODE *node = NULL;

    if(NULL == list || NULL == handle)
        return NULL;

    node = list->head;
    while(node != NULL){

        if(handle(node, param) != TRUE)
            break;

        node = node->next;
    }

    return node;
}
