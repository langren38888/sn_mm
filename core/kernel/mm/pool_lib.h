#ifndef POOL_LIB_H
#define POOL_LIB_H

#include <sn_type.h>
#include <dll_lib.h>

#define ITEM_DO_NOT_FREE   0x1

#define POOL_THREAD_SAFE    1       /* enable multi-task protection */
#define POOL_CHECK_ITEM     2       /* enable item check on return */

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

typedef struct pool *POOL_ID;

extern STATUS pool_lib_init (void);
extern POOL_ID pool_initialize
(
    char *       p_pool,      /* pointer to pool structure memory */
    const char * p_name,      /* optional name to assign to pool */
    size_t       itm_size,   /* size in bytes of a pool item */
    size_t       alignment,  /* alignment of a pool item */
                             /* (must be power of 2, or 0) */
    ULONG        init_cnt,   /* initial number of items to put in pool */
    ULONG        incr_cnt,   /* min no of items to add to pool dynamically */
                             /* (if 0, no pool expansion is done) */
    PART_ID      part_id,    /* memory partition ID */
    ULONG        options     /* initial options for pool */
);
extern POOL_ID pool_create
(
    const char *p_name,      /* optional name to assign to pool */
    size_t      itm_size,   /* size in bytes of a pool item */
    size_t      alignment,  /* alignment of a pool item */
                            /* (must be power of 2, or 0) */
    ULONG       init_cnt,   /* initial number of items to put in pool */
    ULONG       incr_cnt,   /* min no of items to add to pool dynamically */
                            /* (if 0, no pool expansion is done) */
    PART_ID     part_id,    /* memory partition ID */
    ULONG       options     /* initial options for pool */
);
extern STATUS pool_delete(POOL_ID pool_id, BOOL force);
extern ULONG pool_block_add
(
    POOL_ID pool_id,    /* ID of pool to add block to */
    void    *p_block,   /* base address of block to add */
    size_t  size        /* size of block to add */
);
extern BOOL pool_find_item
(
    DLL_LIST *p_list,     /* pointer to list to check */
    DLL_NODE *p_item      /* pointer to item to locate */
);
extern STATUS pool_unused_blocks_free(POOL_ID pool_id);
extern void *pool_item_get(POOL_ID pool_id);
extern STATUS pool_item_return
(
    POOL_ID pool_id,    /* ID of pool to which to return item */
    void    *p_item     /* pointer to item to return */
);
extern STATUS pool_increment_set(POOL_ID pool_id, ULONG incr_cnt);
extern ULONG pool_increment_get(POOL_ID pool_id);
extern ULONG pool_total_count(POOL_ID pool_id);
extern ULONG pool_free_count(POOL_ID pool_id);
extern int pool_id_list_get
(
    POOL_ID pool_id_list[],     /* array to store pool ID */
    int     list_size           /* array size */
);
#endif
