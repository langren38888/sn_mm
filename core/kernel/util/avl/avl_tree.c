#include <stdio.h>
#include "sn_common.h"
#include "avl_tree.h"

/* for LL type of AVL tree to rotate.
 *       k2
 *      / \
 *     k1  d  ->     k1
 *    / \           / \
 *   b   c         b   k2
 *  /             /   / \
 * a             a   c   d
 */
AVL_NODE *LL_rotation(AVL_NODE * k2)
{
    AVL_NODE *k1 = NULL;

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
AVL_NODE *RR_rotation(AVL_NODE * k2)
{
    AVL_NODE *k1 = NULL;

    k1          = k2->right;
    k2->right   = k1->left;
    k1->left    = k2;

    k2->height  = MAX(HEIGHT(k2->left), HEIGHT(k2->right)) + 1;
    k1->height  = MAX(HEIGHT(k1->left), HEIGHT(k2->height)) + 1;

    return k1;
}

/*LR*/
AVL_NODE *LR_rotation(AVL_NODE * k2)
{
    return NULL;
}

/*RL*/
AVL_NODE *RL_rotation(AVL_NODE * k2)
{
    return NULL;
}

void main(void)
{
    printf("Hello world!\r\n");
}
