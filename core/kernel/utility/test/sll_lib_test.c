#include <stdio.h>
#include <stdlib.h>
#include <sll_lib.h>

SLL_LIST *g_sll_list = NULL;

BOOL n_handle(SLL_NODE *node, INT32 param)
{
    if(NULL == node)
        return FALSE;

    printf("point of node is %p\r\n", node);

    return TRUE;
}

void free_list_obo(SLL_LIST * list)
{
    SLL_NODE * pnode = list->head;

    while(pnode != NULL){
        list->head = pnode->next;
        printf("free node %p\r\n", pnode);
        free(pnode);
        pnode = list->head;
    }

    list->head = NULL;
    list->tail = NULL;
}

STATUS sll_put_at_head_test_00()
{
    SLL_NODE *sll_node_t = NULL;

    sll_node_t = (SLL_NODE*)malloc(sizeof(SLL_NODE));
    if(NULL == sll_node_t){
        printf("malloc failed \r\n");
        return ERROR;
    }

    sll_node_t->next = NULL;

    printf("added node(%p) to head \r\n", sll_node_t);

    if(sll_put_at_head(g_sll_list, sll_node_t) != OK)
        printf("sll_put_at_head  failed \r\n");

    sll_each(g_sll_list, n_handle, 0);

    if(sll_remove_node(g_sll_list, (pfree)free, sll_node_t) != OK){
        printf("sll_remove_node failed\r\n");
        return ERROR;
    }

    return OK;
}

STATUS sll_put_at_head_test_01(UINT32 node_num)
{
    SLL_NODE *sll_node_t = NULL;

    while(node_num--){
        sll_node_t = (SLL_NODE*)malloc(sizeof(SLL_NODE));

        if(NULL == sll_node_t){
            printf("malloc failed \r\n");
            return ERROR;
        }

        sll_node_t->next = NULL;

        printf("added node(%p) to head \r\n", sll_node_t);

        if(sll_put_at_head(g_sll_list, sll_node_t) != OK)
            printf("sll_put_at_head  failed \r\n");
    }

    sll_each(g_sll_list, n_handle, 0);

    printf("tail node is %p\r\n", g_sll_list->tail);
    
    printf("previous node of tail is %p\r\n", sll_previous(g_sll_list, g_sll_list->tail));

    printf("%d number in the list\r\n", sll_count(g_sll_list));

    sll_node_t = sll_get(g_sll_list);

    printf("sll_get is %p\r\n", sll_node_t);
    free(sll_node_t);

    sll_each(g_sll_list, n_handle, 0);

    free_list_obo(g_sll_list);

    sll_each(g_sll_list, n_handle, 0);

    return OK;
}


STATUS sll_put_at_tail_test_00()
{
    SLL_NODE *sll_node_t = NULL;

    sll_node_t = (SLL_NODE*)malloc(sizeof(SLL_NODE));
    if(NULL == sll_node_t){
        printf("malloc failed \r\n");
        return ERROR;
    }

    sll_node_t->next = NULL;

    printf("added node(%p) to tail \r\n", sll_node_t);

    if(sll_put_at_tail(g_sll_list, sll_node_t) != OK)
        printf("sll_put_at_head  failed \r\n");

    sll_each(g_sll_list, n_handle, 0);

    if(sll_remove_node(g_sll_list, (pfree)free, sll_node_t) != OK)
        printf("sll_remove_node  failed \r\n");

    return OK;
}

STATUS sll_put_at_tail_test_01(UINT32 node_num)
{
    SLL_NODE *sll_node_t = NULL;

    while(node_num--){
        sll_node_t = (SLL_NODE*)malloc(sizeof(SLL_NODE));

        if(NULL == sll_node_t){
            printf("malloc failed \r\n");
            return ERROR;
        }

        sll_node_t->next = NULL;

        printf("added node(%p) to tail \r\n", sll_node_t);

        if(sll_put_at_tail(g_sll_list, sll_node_t) != OK)
            printf("sll_put_at_tail  failed \r\n");
    }

    sll_each(g_sll_list, n_handle, 0);

    printf("tail node is %p\r\n", g_sll_list->tail);

    printf("previous node of tail is %p\r\n", sll_previous(g_sll_list, g_sll_list->tail));

    printf("%d number in the list \r\n", sll_count(g_sll_list));

    sll_node_t = sll_get(g_sll_list);

    printf("sll_get is %p, free\r\n", sll_node_t);
    free(sll_node_t);

    sll_each(g_sll_list, n_handle, 0);

    free_list_obo(g_sll_list);

    sll_each(g_sll_list, n_handle, 0);

    return OK;
}

void main(void)
{
printf("--- start create list \r\n");

    g_sll_list = sll_create((pmalloc)malloc);
    if(NULL == g_sll_list)
        printf("create list failed \r\n");

printf("--- start init list \r\n");

    if(sll_init(g_sll_list) != OK)
        printf("init list failed \r\n");

printf("\n");
printf("--- start sll_put_at_head_test_00 \r\n\n");
    if(sll_put_at_head_test_00() != OK)
        printf("sll_put_at_head_test_00 failed!\r\n");

printf("\n");
printf("--- start sll_put_at_head_test_01 \r\n\n");
    if(sll_put_at_head_test_01(10) != OK)
        printf("sll_put_at_head_test_01 failed!\r\n");

printf("\n");
printf("--- start sll_put_at_tail_test_00 \r\n\n");
    if(sll_put_at_tail_test_00() != OK)
        printf("sll_put_at_head_test_00 failed!\r\n");

printf("\n");
printf("--- start sll_put_at_tail_test_01 \r\n\n");
    if(sll_put_at_tail_test_01(10) != OK)
        printf("sll_put_at_head_test_01 failed!\r\n");

printf("\n");
printf("--- start delete list \r\n");

    if(sll_delete((pfree)free, g_sll_list) != 0)
        printf("free list failed \r\n");
}
