#include <stdio.h>
#include <stdlib.h>
#include "dll_lib.h"

DLL_LIST *g_dll_list = NULL;

STATUS dll_add_test_00(UINT32 num)
{
    DLL_NODE *node = NULL;

    while(num --){
        node = (DLL_NODE *)malloc(sizeof(DLL_NODE));

        if(NULL == node){
            printf("--- dll_add_test_00 malloc failed \r\n");
            return ERROR;
        }

        printf("(%2d) node ptr %p\r\n", num+1, node);

        if(OK != dll_add(g_dll_list, node)){
            printf("--- dll_add_test_00 dll_add failed \r\n");
            return ERROR;
        }
    }

    return OK;
}

STATUS dll_insert_test_00(void)
{
    DLL_NODE *node = NULL;

    node = (DLL_NODE *)malloc(sizeof(DLL_NODE));

    if(NULL == node){
        printf("--- dll_insert_test_00 malloc failed \r\n");
        return ERROR;
    }

    printf(" node ptr %p\r\n", node);

    if(OK != dll_insert(g_dll_list, NULL, node)){
        printf("--- dll_insert_test_00 dll_insert failed with prev set NULL \r\n");
        return ERROR;
    }

    return OK;
}

BOOL dll_each(DLL_NODE * node, UINT32 param)
{
    printf("dll_each ptr %p \r\n", node);
    return OK;
}

BOOL dll_each_free(DLL_NODE * node, UINT32 param)
{
    printf("dll_each ptr %p \r\n", node);
    return OK;
}

STATUS dll_remove_test_00(DLL_NODE *node)
{
    return dll_remove(g_dll_list, (dll_free)free, node);
}

STATUS free_obo_test_00(DLL_LIST *list)
{
    DLL_NODE *node_free = NULL;

    node_free = dll_get(list);

    while(NULL != node_free){
        free(node_free);
        node_free = dll_get(list);
    }

    return OK;
}

void main(void)
{
    printf("*** dll lib test start!!! \r\n");

    g_dll_list = dll_create((dll_malloc)malloc);

    if(NULL == g_dll_list)
        printf("---dll list malloc failed \r\n");

    printf("\n------------------dll_add_test_00 \r\n");
    if(OK != dll_add_test_00(20))
        printf("---dll_add_test_00 failed \r\n");

    printf("---dll_count %d \r\n", dll_count(g_dll_list));

    printf("\n------------------dll_insert_test_00 \r\n");
    if(OK != dll_insert_test_00())
        printf("---dll_insert_test_00 failed \r\n");

    printf("---dll_count %d \r\n", dll_count(g_dll_list));

    printf("\n------------------dllEach \r\n");
    dllEach(g_dll_list, dll_each, 0);

    printf("\n------------------dll_get \r\n");
    printf("dll_get ptr %p\r\n", dll_get(g_dll_list));

    printf("\n------------------dllEach \r\n");
    dllEach(g_dll_list, dll_each, 0);

    printf("\n------------------dll_remove_test_00 head\r\n");
    dll_remove_test_00(g_dll_list->head);

    printf("\n------------------dllEach \r\n");
    dllEach(g_dll_list, dll_each, 0);

    printf("\n------------------dll_remove_test_00 tail\r\n");
    dll_remove_test_00(g_dll_list->tail);

    printf("\n------------------dllEach \r\n");
    dllEach(g_dll_list, dll_each, 0);

    printf("\n------------------dll_remove_test_00 random \r\n");
    dll_remove_test_00(g_dll_list->head->next);
    dll_remove_test_00(g_dll_list->tail->prev);

    printf("\n------------------dllEach \r\n");
    dllEach(g_dll_list, dll_each, 0);

    printf("\n------------------free_obo_test_00 \r\n");
    free_obo_test_00(g_dll_list);

    printf("\n------------------dllEach \r\n");
    dllEach(g_dll_list, dll_each, 0);

    printf("dll_count num %d\r\n", dll_count(g_dll_list));

    dll_delete(g_dll_list, (dll_free)free);

    printf("*** dll lib test end!!! \r\n");
}

