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

LOCAL inline void avltree_rebalance(AVL_NODE **backtrack, UINT32 track_count)
{

}

STATUS avltree_insert(AVL_TREE root, AVL_NODE * node)
{
    AVL_NODE ** node_pp = &root;
    AVL_NODE *  backtrack[AVL_TREE_MAX_HEIGHT_32] = {NULL};
    UINT32 track_count = 0;

    if(root == NULL || node == NULL)
        return ERROR;

    /* get the insert location */ 
    while(track_count < AVL_TREE_MAX_HEIGHT_32){
        if(*node_pp == NULL)
            break;

        backtrack[track_count ++] = *node_pp;

        /* add node that key is existed in the tree is forbided */
        if(node->key == (*node_pp)->key){
            return ERROR;
        }
        else if(node->key > (*node_pp)->key){
            node_pp   = &(*node_pp)->right;
        }
        else{
            node_pp   = &(*node_pp)->left;
        }
    };

    if(track_count == AVL_TREE_MAX_HEIGHT_32)
        return ERROR;

    /* init the node that to be inserted */
    node->height    = 1;
    node->left      = NULL;
    node->right     = NULL;

    /* insert the node */
    *node_pp      = node;

    /* check balance of the tree  */
    avltree_rebalance(backtrack, track_count);

    return OK;
}

AVL_NODE * avltree_delete(AVL_TREE root, UINT32 key)
{
    AVL_NODE *  del_p = NULL;
    AVL_NODE ** del_p_rep;
    AVL_NODE ** node_pp;
    AVL_NODE *  node_p = NULL ;
    AVL_NODE *  backtrack[AVL_TREE_MAX_HEIGHT_32] = {NULL};
    UINT32 track_count = 0;
    UINT32 track_count_rep = 0;

    if(root != NULL){
        node_pp = &root;
    }else{
        return NULL;
    }

    /* find the node which to be del */
    while(track_count < AVL_TREE_MAX_HEIGHT_32){
        if(*node_pp == NULL)
            return NULL;

        backtrack[track_count ++] = *node_pp;

        if(key == (*node_pp)->key){
            break;
        }else if(key < (*node_pp)->key){
            node_pp = &(*node_pp)->left;
        }else{
            node_pp = &(*node_pp)->right;
        }
    };

    if(track_count == AVL_TREE_MAX_HEIGHT_32)
        return NULL;

    del_p = *node_pp;
    del_p_rep = node_pp;
    track_count_rep = track_count;

    /* replace del node with max of the left child tree or
    * min of the right child tree.
    */
    if((*node_pp)->left == NULL){
        *node_pp = (*node_pp)->right;
        track_count --;
    }else{
        node_pp = &(*node_pp)->left;

        /* get the max of the left child tree */
        while(track_count < AVL_TREE_MAX_HEIGHT_32){
            if((*node_pp)->right == NULL)
                break;
            backtrack[track_count ++] = *node_pp;
            node_pp = &(*node_pp)->right;
        }

        if(track_count == AVL_TREE_MAX_HEIGHT_32)
            return NULL;

        node_p = *node_pp;

        /* don't care leftchild is NULL or not, if it is,
        * then the node set NULL
        */
        *node_pp = (*node_pp)->left;

        node_p->height  = del_p->height;
        node_p->left    = del_p->left;
        node_p->right   = del_p->right;

        *del_p_rep = node_p;

        backtrack[track_count_rep] = node_p;
    }

    /* check balance of the tree  */
    avltree_rebalance(backtrack, track_count);

    return del_p;
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
