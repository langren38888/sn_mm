/*
 * avl_tree.h
 */

/* struct define */

/*
 *avl node
 */
typedef struct avl_tree_node{
    struct avl_tree_node *left;     /* left child node */
    struct avl_tree_node *right;    /* right child node */
    unsigned int size;              /* the value of the node */
    unsigned int height;            /* the height of the node */
}AVL_NODE;

/* macro defined */
#define HEIGHT(ptr)      ((AVL_NODE *)ptr == NULL) ? 0: (((AVL_NODE *)(ptr))->height)

/* funcs extern */
extern AVL_NODE *LL_rotation(AVL_NODE * k2);
extern AVL_NODE *LL_rotation(AVL_NODE * k2);
