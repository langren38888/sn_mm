#include <sn_common.h>
#include "list_lib.h"

#define HEAD    node.prev
#define TAIL    node.next


/* there must be one node in the list */
STATUS list_init(LIST *list)
{
    if(NULL == list)
        return ERROR;

    list->count = 0;

    list->TAIL = NULL;   /* first node in list */
    list->HEAD = NULL;   /* last node in list */

    return OK;
}

STATUS list_insert(LIST *list, LIST_NODE *prev, LIST_NODE *node)
{
    if(NULL == list || NULL == node)
        return ERROR;

    /* initialize the node to be inserted */
    node->next = NULL;
    node->prev = NULL;

    if(NULL == prev){
        if(NULL == list->HEAD){
            list->HEAD = node;
            list->TAIL = node;
        }else{
            node->next = list->HEAD;
            list->HEAD = node;
            node->next->prev = node;
        }
    }else{
        /* indicated that at least one node in the list */
        node->next = prev->next;
        prev->next = node;

        node->prev = prev;
        if(node->next != NULL)
            node->next->prev = node;

        if(list->TAIL == prev)
            list->TAIL = node;
    }

    list->count++;

    return OK;
}

STATUS list_add(LIST *list, LIST_NODE *node)
{
    return list_insert(list, list->TAIL, node);
}

/* delete a specific node in the list */
STATUS list_delete(LIST *list, list_free free, LIST_NODE *node)
{
    if(NULL == list || NULL == node)
        return ERROR;

    if(NULL == node->prev){
        list->HEAD = node->next;
    }else{
        node->prev->next = node->next;
    }

    if(NULL == node->next){
        list->TAIL = node->prev;
    }else{
        node->next->prev = node->prev;
    }

    if(free != NULL)
        free(node);

    list->count--;

    return OK;
}

STATUS list_count(LIST *list)
{
    if(NULL== list)
        return ERROR;

    return list->count;
}

LIST_NODE *list_first(LIST *list)
{
    if(NULL == list)
        return NULL;

    return list->HEAD;
}

LIST_NODE *list_last(LIST *list)
{
    if(NULL == list)
        return NULL;

    return list->TAIL;
}

/* delete and return the first node from the list */
LIST_NODE *list_get(LIST *list)
{
    LIST_NODE *node = NULL;

    if(NULL == list)
        return NULL;

    node = list->HEAD;

    if(NULL != node){
        list->HEAD = node->next;
        if(NULL == node->next){
            list->TAIL = NULL;
        }else{
            list->HEAD->prev = NULL;
        }

        list->count--;
    }

    return node;
}

LIST_NODE *list_previous(LIST_NODE *node)
{
    if(NULL == node)
        return NULL;

    return node->prev;
}

LIST_NODE *list_next(LIST_NODE *node)
{
    if(NULL == node)
        return NULL;

    return node->next;
}

UINT32 list_index_find(LIST *list, LIST_NODE *node)
{
    LIST_NODE *node_tmp = NULL;
    UINT32 index = 1;

    if(NULL == list || NULL == node)
        return ERROR;

    node_tmp = list->HEAD;
    while(NULL != node_tmp){
        index ++;

        if(node_tmp == node)
            break;

        node_tmp = node_tmp->next;
    }

    if(NULL == node_tmp)
        return ERROR;

    return index;
}

/* concatenate the second list to the first */
STATUS list_concatenate(LIST *dst_list, LIST *add_list)
{
    if(NULL == dst_list || NULL == add_list)
        return ERROR;

    if(0 == add_list->count)
        return OK;

    if(0 != dst_list->count){
        dst_list->TAIL->next = add_list->HEAD;
        add_list->HEAD->prev = dst_list->TAIL;
        dst_list->TAIL       = add_list->TAIL;

        dst_list->count += add_list->count;
    }else{
        *dst_list = *add_list;
    }

    list_init(add_list);

    return OK;
}

STATUS list_extract(LIST *src_list, LIST_NODE *start_node, LIST_NODE *end_node, LIST *dst_list)
{
return OK;
}

/* find the node that be specific by node_num
*  where the first node in the list is numbered 1
*  Note that the search is optimized by searching forward from the beginning if the node is closer
*  to the head, and searching back from the end if it is closer to the tail.
*/
LIST_NODE *list_Nth(LIST *list, UINT32 node_num)
{
    LIST_NODE *node_tmp = NULL;

    if((NULL == list) || (node_num <= 0) || (node_num > list->count))
        return NULL;

    if(node_num < (list->count >> 1))
    {
        node_tmp = list->HEAD;

        while(--node_num){
            node_tmp = node_tmp->next;
        }
    }else{
        node_num = list->count - node_num + 1;
        node_tmp = list->TAIL;

        while(--node_num){
            node_tmp = node_tmp->prev;
        }
    }

    return node_tmp;
}

/* find a list node <Nstep> steps away from a specified node
*  If <Nstep> is positive, it steps toward the tail.  If
*  <Nstep> is negative, it steps toward the head.  If the number of steps is
*  out of range, NULL is returned.
*/
LIST_NODE *list_Nstep(LIST_NODE *node, INT32 Nstep)
{
    if((NULL == node) || (0 == Nstep))
        return NULL;

    if(Nstep > 0){
        while(Nstep --){
            node = node->next;
            if(NULL == node)
                return NULL;
        }
    }else if(Nstep < 0){
        while(Nstep ++){
            node = node->prev;
            if(NULL == node)
                return NULL;
        }
    }
}

#if 0
void lstFree2
    (
    LIST*        list,       /* list for which to free all nodes */
    LST_FREE_RTN freeFunc     /* free() function to call */
    )
void lstFree
    (
    LIST* list         /* list for which to free all nodes */
    )

#endif
