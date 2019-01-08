/*
 * avl_tree.h
 */
#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "sn_type.h"

/* constant defines */

/* can't have more than 2**28 nodes of 16 bytes in 4GB */
#define AVL_TREE_MAX_HEIGHT_32 28

/* can't have more than 2**32 nodes in a 64 bit system  why?*/
#define AVL_TREE_MAX_HEIGHT_64 32

/* struct define */

/*
 *avl node
 */

typedef struct avl_node{
    struct avl_node *left;      /* left child node */
    struct avl_node *right;     /* right child node */
    unsigned int key;           /* the value of the node */
    unsigned int height;        /* the height of the node */
}AVL_NODE, *AVL_TREE;

/* typedef */
typedef STATUS (*in_order_callback)(AVL_NODE * node, void * in_orde_para);

/* funcs extern */

STATUS avltree_insert(AVL_TREE *root, AVL_NODE * node);
AVL_NODE *avltree_delete(AVL_TREE *root, UINT32 key);
AVL_NODE *avltree_search(AVL_TREE root, UINT32 key);
AVL_NODE *avltree_successor_get(AVL_TREE root, UINT32 key);
AVL_NODE *avltree_predecessor_get(AVL_TREE root, UINT32 key);
AVL_NODE *avltree_minnum_get(AVL_TREE root);
AVL_NODE *avltree_maxnum_get(AVL_TREE root);
STATUS avltree_tree_travel(AVL_TREE root, in_order_callback call_back, void *para);

#endif //AVL_TREE_H
