#include <sn_common.h>
#include <sn_type.h>
#include "avl_tree.h"

/* macro defined */

#define HEIGHT(ptr) (((AVL_NODE *)(ULONG)ptr == NULL) ? 0: \
                                                      (((AVL_NODE *)(ULONG)(ptr))->height))

LOCAL AVL_NODE *backtrack[AVL_TREE_MAX_HEIGHT_32] = {NULL};

/* why the node stack number is AVL_TREE_MAX_HEIGHT_32 * 2 ? */
LOCAL AVL_NODE *node_stack[AVL_TREE_MAX_HEIGHT_32 * 2];

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
    k1->height  = MAX(HEIGHT(k1->left), k2->height) + 1;

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
    k1->height  = MAX(k2->height, HEIGHT(k1->right)) + 1;

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

LOCAL inline void avltree_rebalance(AVL_NODE ***backtrack, UINT32 track_count)
{
    AVL_NODE *  node_p = NULL;
    AVL_NODE ** node_pp;
    AVL_NODE *  node_left_left;
    AVL_NODE *  node_left_right;
    AVL_NODE *  node_right_right;
    AVL_NODE *  node_right_left;
    INT32  height = 0;

    while(track_count > 0){
        AVL_NODE *  node_left;
        AVL_NODE *  node_right;

        node_pp = backtrack[--track_count];
        node_p  = *node_pp;

        node_left   = node_p->left;
        node_right  = node_p->right;
        height = HEIGHT(node_left) - HEIGHT(node_right);

        if(height > 1){
            /* LL LR */

            node_left_left  = node_left->left;
            node_left_right = node_left->right;

            if((node_left_left != NULL) && (HEIGHT(node_left_left) >= HEIGHT(node_left_right))){
                /* LL */
                *node_pp = ll_rotation(node_p);
            }else{
                /* LR */
                *node_pp = lr_rotation(node_p);
            }
        }else if(height < -1){
            /* RR RL */

            node_right_left  = node_right->left;
            node_right_right = node_right->right;

            if((node_right_right != NULL) && (HEIGHT(node_right_right) >= HEIGHT(node_right_left))){
                /* RR */
                *node_pp = rr_rotation(node_p);
            }else{
                /* RL */
                *node_pp = rl_rotation(node_p);
            }
        }else{

            /* the sub tree of the node is balanced
            * so just set the height of the node.
            */
            height = MAX(HEIGHT(node_left), HEIGHT(node_right)) + 1;

            if(node_p->height != height){
                node_p->height = height;
            }else{
                /* if deleted or inserted a node from a tree and not changed
                * the height of sub tree we can confirm that whole tree still balanced.
                * so stop here.
                */
                break;
            }
        }
    }
}

STATUS avltree_insert(AVL_TREE *root, AVL_NODE * node)
{
    AVL_NODE ** node_pp = root;
    AVL_NODE *  node_p  = NULL;
    AVL_NODE ** backtrack[AVL_TREE_MAX_HEIGHT_32] = {NULL};
    UINT32 track_count = 0;

    if(NULL == root || NULL == node)
        return ERROR;

    /* get the insert location */ 
    while(track_count < AVL_TREE_MAX_HEIGHT_32){
        node_p = *node_pp;
        if(node_p == NULL)
            break;

        backtrack[track_count ++] = node_pp;

        /* add node that key is existed in the tree is forbided */
        if(node->key == node_p->key){
            return ERROR;
        }
        else if(node->key > node_p->key){
            node_pp   = &node_p->right;
        }
        else{
            node_pp   = &node_p->left;
        }
    }

    if(track_count == AVL_TREE_MAX_HEIGHT_32)
        return ERROR;

    /* init the node to be inserted */
    node->height    = 1;
    node->left      = NULL;
    node->right     = NULL;

    /* insert the node */
    *node_pp        = node;

    /* check balance of the tree  */
    avltree_rebalance(backtrack, track_count);

    return OK;
}

AVL_NODE *avltree_delete(AVL_TREE *root, UINT32 key)
{
    AVL_NODE *  del_p = NULL;
    AVL_NODE ** del_p_rep;
    AVL_NODE *  node_p = NULL ;
    AVL_NODE ** node_pp;
    AVL_NODE ** backtrack[AVL_TREE_MAX_HEIGHT_32] = {NULL};
    UINT32 track_count = 0;
    UINT32 track_count_rep = 0;

    if(root != NULL){
        node_pp = root;
    }else{
        return NULL;
    }

    /* find the node which to be del */
    while(track_count < AVL_TREE_MAX_HEIGHT_32){
        node_p = *node_pp;

        if(node_p == NULL)
            return NULL;

        backtrack[track_count ++] = node_pp;

        if(key == node_p->key){
            break;
        }else if(key < node_p->key){
            node_pp = &node_p->left;
        }else{
            node_pp = &node_p->right;
        }
    }

    if(track_count == AVL_TREE_MAX_HEIGHT_32)
        return NULL;

    del_p = node_p;
    del_p_rep = node_pp;
    track_count_rep = track_count;

    /* replace del node with maxnum of the left child tree or
    * minnum of the right child tree.
    */
    if(node_p->left == NULL){
        *node_pp = node_p->right;
        track_count --;
    }else{
        node_pp = &node_p->left;

        /* get the maxnum of the left child tree */
        while(track_count < AVL_TREE_MAX_HEIGHT_32){
            node_p = *node_pp;

            if(node_p->right == NULL)
                break;

            backtrack[track_count ++] = node_pp;
            node_pp = &node_p->right;
        }

        if(track_count == AVL_TREE_MAX_HEIGHT_32)
            return NULL;

        node_p = *node_pp;

        /* we don't care leftchild is NULL or not, if it is,
        * then the node set NULL
        */
        *node_pp = node_p->left;

        node_p->height  = del_p->height;
        node_p->left    = del_p->left;
        node_p->right   = del_p->right;

        *del_p_rep = node_p;

        /* node had exchanged
        * replace the addr of delnode leftchild with
        * addr of node_p leftchild in the backtrack
        */
        backtrack[track_count_rep] = &node_p->left;
    }

    /* check balance of the tree  */
    avltree_rebalance(backtrack, track_count);

    return del_p;
}

AVL_NODE *avltree_search(AVL_TREE root, UINT32 key)
{
    AVL_NODE * node_p = root;

    if(NULL == root)
        return NULL;

    while(node_p != NULL){
        if(node_p->key == key)
            break;

        if(key > node_p->key)
            node_p = node_p->right;
        else
            node_p = node_p->left;
    }

    return node_p;
}

AVL_NODE *avltree_successor_get(AVL_TREE root, UINT32 key)
{
    AVL_NODE *node_p = root;
    AVL_NODE *node_succesor = NULL;

    if(NULL == root)
        return NULL;

    while(node_p != NULL){
        if(key >= node_p->key){
            node_p = node_p->right;
        }else{
            node_succesor = node_p;
            node_p = node_p->left;
        }
    }

    return node_succesor;
}

AVL_NODE *avltree_predecessor_get(AVL_TREE root, UINT32 key)
{
    AVL_NODE *node_p = root;
    AVL_NODE *node_predecessor = NULL;

    if(NULL == root)
        return NULL;

    while(node_p != NULL){
        if(key <= node_p->key){
            node_p = node_p->left;
        }else{
            node_predecessor = node_p;
            node_p = node_p->right;
        }
    }

    return node_predecessor;
}

AVL_NODE *avltree_maxnum_get(AVL_TREE root)
{
    if(NULL == root)
        return NULL;

    while(root->right != NULL){
        root = root->right;
    }

    return root;
}

AVL_NODE *avltree_minnum_get(AVL_TREE root)
{
    if(NULL == root)
        return NULL;

    while(root->left != NULL){
        root = root->left;
    }

    return root;
}

/* only in-orde(left, root, right) tree walk */
STATUS avltree_tree_travel(AVL_TREE root, in_order_callback call_back, void *para)
{
    AVL_NODE * node_p = root;
    UINT32 node_cnt = 0;

    if(NULL == root || NULL == call_back)
        return ERROR;

    while(node_cnt < AVL_TREE_MAX_HEIGHT_32 * 2){

        while(node_p != NULL){
            node_stack[node_cnt++] = node_p;
            node_p = node_p->left;
        }

        if(0 == node_cnt)
            break;

        node_p = node_stack[--node_cnt];

        /* get the right node and give it to call_back */
        call_back(node_p, para);

        node_p = node_p->right;
    }

    return OK;
}
