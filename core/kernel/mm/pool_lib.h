#ifndef POOL_LIB_H
#define POOL_LIB_H

#include <sn_type.h>
#include <dll_lib.h>

#define ITEM_DO_NOT_FREE   0x00000001

#define POOL_THREAD_SAFE    1       /* enable multi-task protection */
#define POOL_CHECK_ITEM     2       /* enable item check on return */

/* ----------temperory */
struct mem_part{
    UINT32  tmp;
};
typedef struct mem_part *PART_ID;

typedef struct semaphore{ /* SEMAPHORE */
    UINT32  tmp;
}SEMAPHORE;
/* ++++++++++temperory */

/* Pool Block records */
typedef struct pool_block{
    DLL_NODE    block_node;  /* block node for pool */
    void        *p_itm_blk;  /* ptr to start of item pool block */
    ULONG       item_cnt;    /* count of items in this block */
}POOL_BLOCK;

/* Pool structure */
typedef struct pool{
    DLL_NODE        pool_node;      /* pool list for pond */
    const char      *pool_name;     /* pool name */
    SEMAPHORE       mutex;          /* Mutex to use for thread-safe pools */
    size_t          siz_item;       /* individual item size in bytes */
    size_t          siz_itm_real;   /* actual item size, due to alignment */
    size_t          alignment;      /* individual item alignment in bytes */
    ULONG           num_incr;       /* nr. of incrementally allocated itm */
    ULONG           num_totl;       /* total number of items created */
    PART_ID         part_id;        /* memory partition ID */
    ULONG           options;        /* pool options word */
    DLL_LIST        block_list;     /* allocated block list */
    DLL_LIST        free_items;     /* free item list */
    ULONG           free_count;     /* length of freeItems list */
    POOL_BLOCK      static_block;   /* for the first static block */
} POOL;

typedef struct pool *   POOL_ID;

#endif
