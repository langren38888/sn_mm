#include <sn_common.h>
#include "pool_lib.h"

DLL_LIST pool_list_gbl = {NULL,NULL};  /* global pool list */

/* ---------- tmp */
#include "stdlib.h"
char *mem_part_alloc(PART_ID part_id, UINT32 size)
{
    return (char *)malloc(size);
}
void mem_part_free(PART_ID part_id, char *ptr)
{
    free(ptr);
}
/* ++++++++++ tmp */

STATUS pool_lib_init (void)
{
    //semMInitUl
    return OK;
}

LOCAL PART_ID pool_part_id_get(PART_ID part_id) /* partition ID */
{
    if(NULL != part_id)
        return part_id;

    /* Here could be return memSysPartId as well */
}

LOCAL STATUS pool_block_build
(
    POOL_ID pool_id,    /* ID of pool to which to add block */
    ULONG   item_cnt,   /* number of items in block */
    void    *p_usr_blk  /* pointer to a user block to be allocated */
)
{
    UINT32 idx;
    UINT32 size_alloc;
    POOL_BLOCK * p_blk;
    ULONG no_free = 0;
    ULONG real_item_size = pool_id->siz_itm_real;

    if(NULL ==  p_usr_blk){
        size_alloc = real_item_size * item_cnt + sizeof(POOL_BLOCK);

        p_usr_blk = mem_part_alloc(pool_id->part_id, size_alloc);
        if(NULL == p_usr_blk)
            return ERROR;

        p_blk = (POOL_BLOCK *)((char *)p_usr_blk + real_item_size * item_cnt);
    }else{
        if(NULL == pool_id->static_block.p_itm_blk){
            p_blk = &pool_id->static_block;
        }else{
            p_blk = (POOL_BLOCK *)mem_part_alloc(pool_id->part_id, sizeof(POOL_BLOCK));
            if(NULL == p_blk)
                return ERROR;
        }
        /* only could be free pool block in this type */
        no_free = ITEM_DO_NOT_FREE;
    }

    p_blk->p_itm_blk = (void *)((ULONG)p_usr_blk | no_free);
    p_blk->item_cnt = item_cnt;

    for(idx = 0; idx < item_cnt; idx ++){
        dll_add(&pool_id->free_items, (DLL_NODE *)p_usr_blk);
        pool_id->free_count++;
        p_usr_blk = (void *)((char *)p_usr_blk + real_item_size);
    }

    dll_add(&pool_id->block_list, &p_blk->block_node);

    pool_id->num_totl += item_cnt;

    return OK;
}

POOL_ID pool_initialize
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
)
{
    POOL_ID pool_id;

    if(NULL != p_pool)
        pool_id = (POOL_ID)p_pool;

    pool_id->siz_item    =   itm_size;
    pool_id->alignment   =   alignment;
    pool_id->options     =   options;
    pool_id->num_incr    =   incr_cnt;
    pool_id->pool_name   =   p_name;
    pool_id->num_totl    =   0;
    pool_id->free_count  =   0;

    if(itm_size < sizeof(DLL_NODE)){
        itm_size = sizeof(DLL_NODE);
    }

    pool_id->siz_itm_real = ROUND_UP(itm_size, alignment);

    pool_id->part_id = pool_part_id_get(part_id);

    dll_init(&pool_id->block_list);
    dll_init(&pool_id->free_items);

    pool_id->static_block.p_itm_blk = NULL;

    if(0 != init_cnt){
        if(ERROR == pool_block_build(pool_id, init_cnt, NULL))
            return NULL;
    }

    //TODO: pool_id->mutex  init process

    //TODO: lock

    dll_add(&pool_list_gbl, &pool_id->pool_node);

    //TODO: unlock

    return pool_id;
}

POOL_ID pool_create
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
)
{
    POOL_ID pool_id;
    char    *p_pool;

    if(itm_size == 0 || ((alignment & (alignment -1)) != 0))
        return NULL;

    if(NULL == (p_pool = mem_part_alloc(part_id, sizeof(struct pool))))
        return NULL;

    pool_id = pool_initialize(p_pool, p_name, itm_size, alignment, init_cnt, incr_cnt,\
                                part_id, options);

    if(NULL == pool_id){
        mem_part_free(part_id, p_pool);
        return NULL;
    }

    return pool_id;
}

STATUS pool_delete(POOL_ID pool_id, BOOL force) /* force deletion if there are items in use */
{
    POOL_BLOCK * p_blk;

    if(NULL == pool_id)
        return ERROR;

    if((!force) && (pool_id->num_totl != pool_id->free_count))
        return ERROR;

    //TODO: LOCK

    dll_remove(&pool_list_gbl, NULL, &pool_id->pool_node);

    //TODO: UNLOCK

    while((p_blk = (POOL_BLOCK *)dll_get(&pool_id->block_list)) != NULL){
        if(((ULONG)(p_blk->p_itm_blk) & ITEM_DO_NOT_FREE) == 0){
            mem_part_free(pool_id->part_id, p_blk->p_itm_blk);
        }else{
            if(p_blk != &pool_id->static_block)
                mem_part_free(pool_id->part_id, (char *)p_blk);
        }
    }

    //TODO: delete samphore

    mem_part_free(pool_id->part_id, (char *)pool_id);

    return OK;
}

ULONG pool_block_add
(
    POOL_ID pool_id,    /* ID of pool to add block to */
    void    *p_block,   /* base address of block to add */
    size_t  size        /* size of block to add */
)
{
    void * p_block_aligned;
    ULONG itm_cnt;
    ULONG real_item_size = pool_id->siz_itm_real;

    if(NULL == p_block || NULL == pool_id)
        return ERROR;

    p_block_aligned = (void *)ROUND_UP(p_block, pool_id->alignment);

    itm_cnt = (ULONG)(size - ((ULONG)p_block_aligned - (ULONG)p_block))/\
                real_item_size;

    if((itm_cnt < 1) || (size < ((ULONG)p_block_aligned - (ULONG)p_block)))
        return ERROR;

    //TODO:pool_lock
    pool_block_build(pool_id, itm_cnt, p_block_aligned);
    //TODO:pool_unlock

    return itm_cnt;
}

BOOL pool_find_item
(
    DLL_LIST *p_list,     /* pointer to list to check */
    DLL_NODE *p_item      /* pointer to item to locate */
)
{
    DLL_NODE *p_node = dll_first(p_list);

    while((NULL != p_node) && (p_node != p_item)){
        p_node = dll_next(p_node);
    }

    if(NULL == p_node)
        return FALSE;

    return TRUE;
}

LOCAL BOOL pool_block_is_free
(
    POOL_ID     pool_id,    /* pool the block belongs to */
    POOL_BLOCK  *p_blk      /* block to check */
)
{
    void *item_tmp;
    int idx;
    BOOL is_free = TRUE;
    ULONG real_item_size = pool_id->siz_itm_real;

    item_tmp = (void *)((ULONG)(p_blk->p_itm_blk) & (ULONG)(~ITEM_DO_NOT_FREE));

    for(idx = 0; idx < p_blk->item_cnt; idx ++){
        if(pool_find_item(&pool_id->free_items, item_tmp) == FALSE){
            is_free = FALSE;
            break;
        }

        item_tmp = (void *)((char *)item_tmp + real_item_size);
    }

    return is_free;
}

STATUS pool_unused_blocks_free(POOL_ID pool_id)
{
    POOL_BLOCK *p_block, *p_pre_block;
    char *p_item;
    ULONG idx;
    ULONG real_item_size = pool_id->siz_itm_real;

    if(NULL == pool_id)
        return ERROR;

    //TODO: POOL_LOCK

    p_block = (POOL_BLOCK *)dll_first(&pool_id->block_list);

    while(p_block != NULL){
        p_pre_block = p_block;
        p_block = (POOL_BLOCK *)dll_next((DLL_NODE *)p_block);

        if(pool_block_is_free(pool_id, p_pre_block) && \
            (((ULONG)(p_pre_block->p_itm_blk) & ITEM_DO_NOT_FREE) == 0)){

            for(idx = 0; idx < p_pre_block->item_cnt; idx ++){
                p_item = (char *)(p_pre_block->p_itm_blk) + idx * real_item_size;
                dll_remove(&pool_id->free_items, NULL, (DLL_NODE *)p_item);
                pool_id->free_count--;
            }

            pool_id->num_totl -= p_block->item_cnt;

            dll_remove(&pool_id->block_list, NULL, &p_pre_block->block_node);

            mem_part_free(pool_id->part_id, p_pre_block->p_itm_blk);
        }
    }

    //TODO: POOL_UNLOCK

    return OK;
}

/* this routine can be called from interrupt context if the \
pool was created without the POOLTHREAD_SAFE option */
void *pool_item_get(POOL_ID pool_id)
{
    void *p_item = NULL;
    BOOL malc = TRUE;

    if(NULL == pool_id)
        return NULL;

    //TODO:LOCK

    if(NULL == dll_first(&pool_id->free_items)){
        if(0 == pool_id->num_incr){
            malc = FALSE;
        }
#if 0
/* could be happend from ISR */
        else if(INT_CONTEXT()){
            malc = FALSE;
        }
#endif
        else if(pool_block_build(pool_id, pool_id->num_incr, NULL) == ERROR){
            malc = FALSE;
        }
    }

    if(malc == TRUE){
        p_item = (void *)dll_get(&pool_id->free_items);
        pool_id->free_count--;
    }

    //TODO:UNLOCK

    return p_item;
}

LOCAL BOOL pool_item_is_valid
(
    POOL_ID pool_id,    /* ID of pool to be validated against */
    void    *p_item     /* pointer to item to be validated */
)
{
    POOL_BLOCK * p_blk;
    char * p_item_t;
    ULONG offset;
    ULONG real_item_size = pool_id->siz_itm_real;

    if(NULL == pool_id || NULL == p_item)
        return FALSE;

    p_blk = (POOL_BLOCK *)dll_first(&pool_id->block_list);

    while(p_blk != NULL){
        p_item_t = (char *)((ULONG)(p_blk->p_itm_blk) & (ULONG)~ITEM_DO_NOT_FREE);

        if(((char *)p_item >= p_item_t) && \
            ((char *)p_item < (p_item_t + real_item_size * p_blk->item_cnt))){

            offset = (char *)p_item - p_item_t;
            if(offset/real_item_size * real_item_size == offset){
                return TRUE;
            }else{
                return FALSE;
            }
        }

        p_blk = (POOL_BLOCK *)dll_next(&p_blk->block_node);
    }

    return FALSE;
}

STATUS pool_item_return
(
    POOL_ID pool_id,    /* ID of pool to which to return item */
    void    *p_item     /* pointer to item to return */
)
{
    UINT32 ret = ERROR;
    UINT32 condition = TRUE;

    if(NULL == pool_id || NULL == p_item)
        return ERROR;

    //TODO:POOL LOCK

    if(pool_id->options & POOL_CHECK_ITEM){
        if(pool_find_item(&pool_id->free_items, p_item) == TRUE){
            condition = FALSE;
        }else if(pool_item_is_valid(pool_id, p_item) != TRUE){
            condition = FALSE;
        }
    }

    if(condition == TRUE){
        dll_add(&pool_id->free_items, (DLL_NODE *)p_item);
        pool_id->free_count++;
        ret = OK;
    }

    //TODO:POOL UNLOCK

    return ret;
}

STATUS pool_increment_set(POOL_ID pool_id, ULONG incr_cnt)
{
    if(NULL != pool_id)
        return ERROR;

    pool_id->num_incr = incr_cnt;
    return OK;
}

ULONG pool_increment_get(POOL_ID pool_id)
{
    if(NULL != pool_id)
        return ERROR;

    return (pool_id->num_incr);
}

ULONG pool_total_count(POOL_ID pool_id)
{
    if(NULL != pool_id)
        return ERROR;

    return (pool_id->num_totl);
}

ULONG pool_free_count(POOL_ID pool_id)
{
    if(NULL != pool_id)
        return ERROR;

    return (pool_id->free_count);
}

int pool_id_list_get
(
    POOL_ID pool_id_list[],     /* array to store pool ID */
    int     list_size           /* array size */
)
{
    int count = 0;
    POOL_ID poolid;
    //TODO: lock

    poolid = (POOL_ID)dll_first(&pool_list_gbl);
    while((count < list_size) && (poolid != NULL)){
        pool_id_list[count++] = poolid;
        poolid = (POOL_ID)dll_next(&poolid->pool_node);
    }

    //TODO: unlock
    return count;
}
