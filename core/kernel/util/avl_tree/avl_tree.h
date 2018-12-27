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

/* funcs extern */

extern AVL_TREE LL_rotation(AVL_TREE k2);
extern AVL_TREE LL_rotation(AVL_TREE k2);

#endif //AVL_TREE_H
