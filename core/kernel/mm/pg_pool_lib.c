#include <sn_common.h>
#include "pg_pool_lib.h"

/* local typedefs */

typedef union page_pool_node
{
   PAGE_POOL_ADDR_NODE      addr_node;
   PAGE_POOL_FREE_SIZE_NODE size_node;
}PAGE_POOL_NODE;

LOCAL PAGE_POOL_NODE initial_nodes[NODE_POOL_INIT_CNT];

/* initialize the page pool library */
STATUS pg_pool_lib_init(void)
{
    return OK;
}

/* create a page pool */
PAGE_POOL_ID pg_pool_create
(
    size_t          page_size,  /* page size in bytes */
    PG_POOL_OPT     options     /* page pool options */
)
{
    return NULL;
}

/* initialize a page pool */
PAGE_POOL_ID pg_pool_init
(
    PAGE_POOL_OBJ *pgPoolObj,  /* page pool object to initialize   */
    size_t         pageSize,   /* minimum unit of allocation   */
    PG_POOL_OPT    options     /* memory pool options  */
)
{
    return NULL;
}

/* delete a page pool */
STATUS pg_Pool_Delete(PAGE_POOL_ID pool_Id)
{
    return OK;
}

/* add a block of contiguous pages to a page pool */
STATUS pg_pool_add_to_pool
(
    PAGE_POOL_ID    pool_Id,     /* page pool ID */
    UINT32          start_page,  /* start page of the block to add */
    UINT32          num_pages,   /* size in pages of the block to add */
    UINT32          state       /* pages are added allocated or free */
)
{
    return OK;
}

/* remove a block of contiguous pages from a page pool */
STATUS pg_pool_remove_from_pool
(
    PAGE_POOL_ID    poolId,     /* page pool ID */
    UINT32          startPage,  /* start page of the block to remove */
    UINT32          numPages    /* size in pages of the block to remove */
)
{
    return OK;
}

/* allocate an aligned block of contiguous page(s) */
UINT32 pg_pool_aligned_alloc
(
    PAGE_POOL_ID    pool_id,    /* page pool id to allocate from */
    UINT32          num_Pages,  /* number of pages to allocate   */
    UINT32          alignment   /* boundary to align to in pages */
)
{
    return OK;
}

/* allocate pages starting at a specified page number */
UINT32 pg_pool_alloc_at
(
    PAGE_POOL_ID    pool_id,    /* page pool id to allocate from */
    UINT32          start_Page, /* number of the first page */
    UINT32          num_Pages   /* number of pages to allocate */
)
{
    return OK;
}

/* allocate available pages */
UINT32 pg_pool_avail_alloc
(
    PAGE_POOL_ID    pool_id,         /* pool ID */
    UINT32          num_pages_req,   /* page count requested */
    UINT32          p_num_pages_got  /* page count got */
)
{
    return OK;
}

/* free pages in a page pool */
STATUS pg_pool_free
(
    PAGE_POOL_ID    pool_id,    /* page pool id */
    UINT32          start_page, /* first page of the block */
    UINT32          num_pages   /* number of pages to free */
)
{
    return OK;
}

/* set an address range to allocated or free */
LOCAL STATUS pg_pool_range_state_set
(
    PAGE_POOL_OBJ           *p_pool,        /* page pool */
    PAGE_POOL_ADDR_NODE     *p_addr_Node,   /* address node */
    UINT32                  start_page,     /* start page */
    UINT32                  num_pages,      /* number of pages */
    UINT32                  new_state       /* requested state */
)
{
    return OK;
}

/* check if an address range is all allocated or all free */
BOOL pg_pool_range_state_check
(
    PAGE_POOL_ID    pool_id,         /* ID of page pool to check 	*/
    UINT32          start_page,      /* start page of the range 	*/
    UINT32          num_pages,       /* number of pages in the range */
    UINT32          alloc_or_free    /* check if allocated or free   */
)
{
    return TRUE;
}

/* verify that a block of pages belongs to a page pool */
BOOL pg_pool_range_verify
(
    PAGE_POOL_ID    pool_id,     /* page pool id */
    UINT32          start_page,  /* start page of range */
    UINT32          num_pages    /* number of pages */
)
{
    return TRUE;
}

/* get page pool information */
STATUS pg_pool_info_get
(
    PAGE_POOL_ID    pool_id,      /* page pool ID to get info from */
    PAGE_POOL_INFO  *p_pool_info  /* return page pool info here    */
)
{
    return OK;
}

/* get next free block in pool */
STATUS pg_Pool_Next_Free_Get
(
    PAGE_POOL_ID    pool_Id,        /* pool ID */
    UINT32          pg_Num,         /* reference page */
    UINT32          *p_Pg_Num_Free, /* where to return start page */
    UINT32          *p_Num_Pages    /* where to return last page */
)
{
    return OK;
}

/* insert a PAGE_POOL_ADDR_NODE in the list of
PAGE_POOL_ADDR_NODE structures of the same size */
LOCAL STATUS pg_pool_insert_free
(
    PAGE_POOL_OBJ       *p_pool,        /* page pool */
    PAGE_POOL_ADDR_NODE *p_addr_node    /* pointer to the address node */
)
{
    return OK;
}

/* remove a PAGE_POOL_ADDR_NODE from the list of
PAGE_POOL_ADDR_NODE structures of the same size */
LOCAL void pg_pool_delete_free
(
    PAGE_POOL_OBJ       *p_pool,        /* page pool object */
    PAGE_POOL_ADDR_NODE *p_addr_node    /* pointer to address node to remove */
)
{

}

/* return tree nodes to pool */
LOCAL STATUS pg_pool_node_return_callback
(
    AVL_NODE   *p_Node,    /* current node */
    void        *arg        /* poolId argument */
)
{
    return OK;
}
