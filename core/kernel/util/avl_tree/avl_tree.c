#include <sn_common.h>
#include <sn_type.h>
#include "avl_tree.h"

/* macro defined */

#define HEIGHT(ptr) ((AVL_NODE *)(ULONG)ptr == NULL) ? 0: \
                                                      (((AVL_NODE *)(ULONG)(ptr))->height)

LOCAL AVL_NODE *backtrack[AVL_TREE_MAX_HEIGHT_32] = {NULL};

UINT32 track_count = 0;

/* for LL type of AVL tree to rotate.
 *       k2
 *      / \
 *     k1  d  ->     k1
 *    / \           / \
 *   b   c         b   k2
 *  /             /   / \
 * a             a   c   d
 */

LOCAL inline AVL_NODE *ll_rotation(AVL_TREE k2)
{
    AVL_TREE k1 = NULL;

    k1          = k2->left;
    k2->left    = k1->right;
    k1->right   = k2;

    k2->height  = MAX(HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
    k1->height  = MAX(HEIGHT(k1->left), HEIGHT(k2->height)) + 1;

    return k1;
}

/* for RR type of AVL tree to rotate.
 *       k2
 *      / \
 *     d  k1  ->      k1
 *       /  \        / \
 *      c    b      k2  b
 *            \    / \   \
 *             a  d   c   a
 */

LOCAL inline AVL_NODE *rr_rotation(AVL_TREE k2)
{
    AVL_TREE k1 = NULL;

    k1          = k2->right;
    k2->right   = k1->left;
    k1->left    = k2;

    k2->height  = MAX(HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
    k1->height  = MAX(HEIGHT(k1->left), HEIGHT(k2->height)) + 1;

    return k1;
}

/* for LR type of AVL tree to rotate.
 *      k3              k3              k2
 *      / \     rr      / \     ll      / \
 *     k1  d    ->     k2  d    ->    k1   k3
 *    / \             / \            / \   / \
 *   a   k2          k1   c          a   b  c  d
 *       / \        / \
 *      b   c      a   b
 */

LOCAL inline AVL_NODE *lr_rotation(AVL_TREE k3)
{
    k3->left = rr_rotation(k3->left);

    return ll_rotation(k3);
}

/* for RL type of AVL tree to rotate.
 *      k1               k1                 k2
 *      / \      ll      / \       rr       / \
 *     a  k3     ->     a   k2     ->     k1   k3
 *        / \               / \          / \   / \
 *       k2  d             b   k3       a   b  c  d
 *      / \                    / \
 *     b   c                  c   d
 */

LOCAL inline AVL_NODE *rl_rotation(AVL_TREE k1)
{
    k1->right = ll_rotation(k1->right);

    return rr_rotation(k1);
}

STATUS avltree_insert(AVL_TREE root, AVL_NODE * node)
{
    AVL_NODE * node_tmp = root;

    if(root == NULL || node == NULL)
        return ERROR;

    /* get the insert location */ 
    while(node_tmp){
        if(node_tmp == NULL)
            break;

        backtrack[track_count ++] = node_tmp;

        /* could not add node that key exist in the tree */
        if(node->key == node_tmp->key)
            return ERROR;
        else if(node->key > node_tmp->key)
            node_tmp = node_tmp->right;
        else
            node_tmp = node_tmp->left;
    };


    return OK;
}

int avltree_delete(AVL_TREE root, UINT32 key)
{
    if(root == NULL)
        return ERROR;

    return OK;
}

AVL_NODE *avltree_search(AVL_TREE root, UINT32 key)
{
    if(root == NULL)
        return NULL;

    return NULL;
}

AVL_NODE *avltree_succesor_get(AVL_TREE root, UINT32 key)
{
    if(root == NULL)
        return NULL;

    return NULL;
}

AVL_NODE *avltree_predecessor_get(AVL_TREE root, UINT32 key)
{
    if(root == NULL)
        return NULL;

    return NULL;
}

AVL_NODE *avltree_minimum_get(AVL_TREE root)
{
    if(root == NULL)
        return NULL;

    return NULL;
}

AVL_NODE *avltree_maximum_get(AVL_TREE root)
{
    if(root == NULL)
        return NULL;

    return NULL;
}

LOCAL inline void avltree_rebalance()
{

}
