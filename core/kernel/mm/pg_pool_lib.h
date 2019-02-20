#ifndef PG_POOL_LIB_H
#define PG_POOL_LIB_H

#include <sn_type.h>
#include <avl_tree.h>

#define NODE_POOL_INIT_CNT  32
#define NODE_POOL_INCR_CNT  32

typedef unsigned int PG_POOL_OPT;

/*
 * the next and prev fields in PAGE_POOL_ADDR_NODE must match
 * the locations of the first and last fields in
 * PAGE_POOL_FREE_SIZE_NODE.
 */

typedef struct pg_pool_addr_node
{
    AVL_NODE   avl_pg_num;                  /* AVL sorted by pgNum */
    struct pg_pool_addr_node *     next;    /* next in free list, if free */
    struct pg_pool_addr_node *     prev;    /* prev in free list, if free */
    ULONG        state;                     /* state of block */
    ULONG        numPages;                  /* size of block */
}PAGE_POOL_ADDR_NODE;

typedef struct pg_pool_free_size_node
{
    AVL_NODE   avl_size;                    /* AVL tree sorted by size */
    struct pg_pool_addr_node *     first;   /* first in free list */
    struct pg_pool_addr_node *     last;    /* last in free list */
}PAGE_POOL_FREE_SIZE_NODE;

typedef struct page_pool_obj    /* PAGE_POOL_OBJ */
{
    size_t      page_size;      /* page size of the pool */
    SEMAPHORE   sem;            /* page pool semaphore */
    union
    {
    PHYS_ADDR   p;
    VIRT_ADDR   v;
    }baseAddr;                  /* base addres of the pool */

    union
    {
    PHYS_ADDR   p;
    VIRT_ADDR   v;
    }addrMask;                  /* mask to verify range */

    PG_POOL_OPT options;        /* pool options */
    UINT32      pg_num_shift;   /* shift to translate address */
                                /* to/from pgNum */
    UINT32      num_pages;      /* size of pool in pages */
    UINT32      num_free_pages; /* free pages in pool */
    AVL_TREE    pg_num_tree;    /* tree sorted by page number */
    AVL_TREE    size_tree;      /* size-sorted AVL tree */
} PAGE_POOL_OBJ;

typedef struct page_pool_obj    *PAGE_POOL_ID;

/* page pool information/statistics structure */
typedef struct pgPoolInfo
{
size_t          pageSize;       /* size of a page in bytes */

PG_POOL_OPT     options;        /* options of the page pool */
UINT32          numPages;       /* pages in the page pool */
UINT32          numFreePages;   /* free pages in pool */
UINT32          maxContigPages; /* pages in the largest */
                                /* contiguous free block */
}  PAGE_POOL_INFO;

#endif
