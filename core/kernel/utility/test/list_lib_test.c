#include<stdlib.h>
#include<stdio.h>
#include"list_lib.h"

LIST *g_list1, *g_list2;

void list_walk(LIST *list)
{
    LIST_NODE *node = NULL;

    printf("---nodes of the g_listX are %d\r\n", list_count(list));

    node = list->node.prev;
    while(NULL != node){
        printf("---node ptr is %p \r\n", node);
        node = node->next;
    }
}

STATUS list_add_test_00(LIST *list, UINT32 num)
{
    LIST_NODE *node = NULL;

    while(num --){
        node = (LIST_NODE *)malloc(sizeof(LIST_NODE));
        if(NULL == node){
            printf("list_add_test_00 malloc failed!\r\n");
            return ERROR;
        }
        list_add(list, node);
    }

    return OK;
}

void free_list_nodes(LIST * list)
{
    LIST_NODE *node = NULL;

    printf("free all of the nodes of the list %p\r\n", list);
    node = list->node.prev;

    while(NULL != node){
        list_delete(list, (list_free_func)free, node);
        node = node->next;
    }
}

void main(void)
{
    printf("start list test !!!\n");

    UINT32 node_num = 10;

    g_list1 = (LIST *)malloc(sizeof(LIST));
    g_list2 = (LIST *)malloc(sizeof(LIST));

    list_init(g_list1);
    list_init(g_list2);

    LIST_NODE *node_tmp = NULL;
    node_tmp = (LIST_NODE *)malloc(sizeof(LIST_NODE));
    list_insert(g_list1, NULL, node_tmp);
    printf("---node_tmp1 ptr is %p \r\n", node_tmp);

    node_tmp = (LIST_NODE *)malloc(sizeof(LIST_NODE));
    list_add(g_list1, node_tmp);
    printf("---node_tmp2 ptr is %p \r\n", node_tmp);

    node_tmp = (LIST_NODE *)malloc(sizeof(LIST_NODE));
    list_insert(g_list1, NULL, node_tmp);
    printf("---node_tmp3 ptr is %p \r\n", node_tmp);

    printf("-1--get the first node from list ptr is %p\r\n", list_get(g_list1));
    printf("-2--get the first node from list ptr is %p\r\n", list_get(g_list1));
    printf("-3--get the first node from list ptr is %p\r\n", list_get(g_list1));

    list_walk(g_list1);

    printf("\n------------------------------------------------- \r\n");
    printf("insert %d nodes into g_list1\r\n", node_num);
    list_add_test_00(g_list1, node_num);

    printf("---ptr of the next of the first node is %p\r\n", list_next(g_list1->node.prev));
    printf("---ptr of the previous of the last node is %p\r\n", list_previous(g_list1->node.next));

    list_walk(g_list1);

    printf("the count of the fist node in the list is %d\r\n", list_index_find(g_list1, g_list1->node.prev));
    printf("the count of the last node in the list is %d\r\n", list_index_find(g_list1, g_list1->node.next));
    printf("the count of the second node in the list is %d\r\n", list_index_find(g_list1, g_list1->node.prev->next));

    printf("---first node ptr is %p\r\n", list_first(g_list1));
    printf("---last node ptr is %p\r\n", list_last(g_list1));

    printf("insert %d nodes into g_list2\r\n", node_num);
    list_add_test_00(g_list2, node_num);
    list_walk(g_list2);

    printf("\n------------------------------------------------- \r\n");
    printf("the num %2d of the node in the list is %p\r\n",  1, list_Nth(g_list2, 1));
    printf("the num %2d of the node in the list is %p\r\n",  5, list_Nth(g_list2, 5));
    printf("the num %2d of the node in the list is %p\r\n", 10, list_Nth(g_list2, 10));

    printf("\n------------------------------------------------- \r\n");
    node_tmp = list_Nth(g_list2, 5);
    printf("the num %d of the node ptr is %p\r\n", -1, list_Nstep(node_tmp, -1));
    printf("the num %d of the node ptr is %p\r\n", -4, list_Nstep(node_tmp, -4));
    printf("the num %d of the node ptr is %p\r\n", -5, list_Nstep(node_tmp, -5));
    printf("the num %d of the node ptr is %p\r\n", 1, list_Nstep(node_tmp, 1));
    printf("the num %d of the node ptr is %p\r\n", 4, list_Nstep(node_tmp, 4));
    printf("the num %d of the node ptr is %p\r\n", 5, list_Nstep(node_tmp, 5));

    printf("\n----------------------list_concatenate--------------------------- \r\n");
    list_concatenate(g_list1, g_list2);
    printf("---after concatenate the two lists, the count is %d\r\n", g_list1->count);
    list_walk(g_list1);

    printf("\nmid----------------------list_extract----------------- \r\n");
    list_extract(g_list1, g_list1->node.prev->next, g_list1->node.next->prev, g_list2);
    list_walk(g_list1);
    list_walk(g_list2);
    list_concatenate(g_list1, g_list2);
    printf("---after concatenate the two lists, the count is %d\r\n", g_list1->count);
    list_walk(g_list1);

    printf("head\n");
    list_extract(g_list1, g_list1->node.prev, g_list1->node.next->prev, g_list2);
    list_walk(g_list1);
    list_walk(g_list2);
    list_concatenate(g_list1, g_list2);
    printf("---after concatenate the two lists, the count is %d\r\n", g_list1->count);
    list_walk(g_list1);

    printf("tail\n");
    list_extract(g_list1, g_list1->node.prev->next, g_list1->node.next, g_list2);
    list_walk(g_list1);
    list_walk(g_list2);
    list_concatenate(g_list1, g_list2);
    printf("---after concatenate the two lists, the count is %d\r\n", g_list1->count);
    list_walk(g_list1);

    printf("\n------------------------------------------------- \r\n");
    list_free(g_list1, free);
    list_walk(g_list1);

    list_free(g_list2, free);
    list_walk(g_list2);
}
