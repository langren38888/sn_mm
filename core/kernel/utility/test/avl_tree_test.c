#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

/* global define */
struct avl_node root_node = {
    .key = 0,
};

AVL_TREE tree_root = &root_node;

/*-------------------------insert test func--------------------------------*/
STATUS avl_tree_insert_test_00(UINT32 node_num)
{
    AVL_NODE * node_p = NULL;

    printf("\n --- insert_00 started! tree_root->key %d\r\n", tree_root->key);

    while(node_num){
        if(avltree_search(tree_root, node_num) != NULL){
             printf("the key of the node (%d) have existed in the tree!\r\n", node_p->key);
             node_num --;
             continue;
         }

        node_p = (AVL_NODE *)malloc(sizeof(struct avl_node));

        if(NULL == node_p){
            printf("malloc failed\r\n");
            return ERROR;
        }

        node_p->key = node_num;

        //printf("avl_tree_insert_test_00 key : %d\r\n", node_p->key);
        if(avltree_insert(&tree_root, node_p) != OK){
            printf("\n  insert failed\r\n");
            return ERROR;
        }

        node_num --;
    }

    printf(" +++ insert_00 end! tree_root->key %d \r\n", tree_root->key);
    printf(" +++ insert_00 end! tree_root->height %d \r\n\n", tree_root->height);

    return OK;
}

STATUS avl_tree_insert_test_01(UINT32 node_num)
{
    UINT32 count = 1;
    AVL_NODE * node_p = NULL;

    printf("\n --- insert_01 started! tree_root->key %d\r\n", tree_root->key);

    while(count <= node_num){
        if(avltree_search(tree_root, count) != NULL){
             printf("the key of the node (%d) have existed in the tree!\r\n", node_p->key);
             count ++;
             continue;
         }

        node_p = (AVL_NODE *)malloc(sizeof(struct avl_node));

        if(NULL == node_p){
            printf("malloc failed\r\n");
            return ERROR;
        }

        node_p->key = count;

        //printf("avl_tree_insert_test_01 key : %d\r\n", node_p->key);
        if(avltree_insert(&tree_root, node_p) != OK){
            printf("\n  insert failed\r\n");
            return ERROR;
        }

        count ++;
    }

    printf(" +++ insert_01 end! tree_root->key %d \r\n", tree_root->key);
    printf(" +++ insert_01 end! tree_root->height %d \r\n\n", tree_root->height);

    return OK;
}

/*-------------------------delete test func--------------------------------*/
STATUS avl_tree_delete_test_00(UINT32 node_num)
{
    AVL_NODE *node_p = NULL;
    printf("\n --- delete_00 started! tree_root->key %d \r\n", tree_root->key);

    while(node_num){
        //printf("avl_tree_delete_test_00 key : %d\r\n", node_num);
        node_p = avltree_delete(&tree_root, node_num);

        if(node_p != NULL){
            free(node_p);
        }else{
            return ERROR;
        }

        node_num --;
    }

    printf(" +++ delete_00 end! tree_root->key %d \r\n\n", tree_root->key);

    return OK;
}

STATUS avl_tree_delete_test_01(UINT32 node_num)
{
    UINT32 count = 1;
    AVL_NODE *node_p = NULL;
    printf("\n --- delete_01 started! tree_root->key %d \r\n", tree_root->key);

    while(count <= node_num){
        //printf("avl_tree_delete_test_01 key : %d\r\n", count);
        node_p = avltree_delete(&tree_root, count);

        if(node_p != NULL){
            free(node_p);
        }else{
            return ERROR;
        }

        count ++;
    }

    printf(" +++ delete_01 end! tree_root->key %d \r\n\n", tree_root->key);

    return OK;
}

/*-------------------------travel test func--------------------------------*/
STATUS travel_cb(AVL_NODE *node_p, void *param)
{
    if(NULL == node_p)
        return ERROR;

    //printf(" key: %d\r\n", node_p->key);

    return OK;
}

STATUS avl_tree_travel_test(void)
{
    STATUS ret;
    printf("\n --- travel_00 started! \r\n");
    ret = avltree_tree_travel(tree_root, travel_cb, NULL);
    printf(" +++ travel_00 end! ret %d\r\n\n", ret);

    return ret;
}

STATUS avl_tree_minnum_get_test_00(void)
{
    AVL_NODE * node_p;

    node_p = avltree_minnum_get(tree_root);

    if(NULL == node_p)
        return ERROR;

    printf("avl_tree_minnum_get_test_00 node_p->key %d\r\n", node_p->key);

    return OK;
}

STATUS avl_tree_maxnum_get_test_00(void)
{
    AVL_NODE * node_p;

    node_p = avltree_maxnum_get(tree_root);

    if(NULL == node_p)
        return ERROR;

    printf("avl_tree_maxnum_get_test_00 node_p->key %d\r\n", node_p->key);

    return OK;
}


STATUS avl_tree_successor_get_test_00(UINT32 key)
{
    AVL_NODE * node_p;

    node_p = avltree_successor_get(tree_root, key);

    if(NULL == node_p)
        return ERROR;

    printf("avl_tree_successor_get_test_00 node_p->key %d\r\n", node_p->key);

    return OK;
}

STATUS avl_tree_predecessor_get_test_00(UINT32 key)
{
    AVL_NODE * node_p;

    node_p = avltree_predecessor_get(tree_root, key);

    if(NULL == node_p)
        return ERROR;

    printf("avl_tree_predecessor_get_test_00 node_p->key %d\r\n\n", node_p->key);

    return OK;
}

/*-------------------------main test func----------------------------------*/
void main(void)
{
    UINT32 add_del_node_n = 190000;

    printf("\n ------------test started!!!---------- \r\n");
    printf("---insert--- \r\n");

/* insert */
    if(avl_tree_insert_test_00(add_del_node_n) != OK){
        printf("\n avl_tree_insert_test_00 failed \r\n");
    }

    printf("---travel--- \r\n");
    avl_tree_travel_test();

    avl_tree_minnum_get_test_00();
    avl_tree_maxnum_get_test_00();
    avl_tree_successor_get_test_00(add_del_node_n/2);
    avl_tree_predecessor_get_test_00(add_del_node_n/2);

    printf("---delete--- \r\n");
/* delete */
    if(avl_tree_delete_test_00(add_del_node_n) != OK){
        printf("\n avl_tree_delete_test_00 failed \r\n");
    }

    printf("---insert--- \r\n");

/* insert */
    if(avl_tree_insert_test_01(add_del_node_n) != OK){
        printf("\n avl_tree_insert_test_00 failed \r\n");
    }

    printf("---travel--- \r\n");
    avl_tree_travel_test();

    avl_tree_minnum_get_test_00();
    avl_tree_maxnum_get_test_00();
    avl_tree_successor_get_test_00(add_del_node_n/2);
    avl_tree_predecessor_get_test_00(add_del_node_n/2);

    printf("---delete--- \r\n");
/* delete */
    if(avl_tree_delete_test_01(add_del_node_n) != OK){
        printf("\n avl_tree_delete_test_00 failed \r\n");
    }

}
