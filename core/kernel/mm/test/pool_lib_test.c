#include <stdio.h>
#include <stdlib.h>
#include <pool_lib.h>

struct mem_part part_id_t = {0};

static POOL_ID g_pool_id = NULL;

void pool_id_show(POOL_ID pool_id)
{
    printf("\n-------------------------------------------\n");
    printf("pool_id_show:\n");
    printf("pool_id->pool_node      %p\n",  &pool_id->pool_node);
    printf("pool_id->pool_name      %s\n",  pool_id->pool_name);
    printf("pool_id->mutex          %p\n",  &pool_id->mutex);
    printf("pool_id->siz_item       %ld\n", pool_id->siz_item);
    printf("pool_id->siz_itm_real   %ld\n", pool_id->siz_itm_real);
    printf("pool_id->alignment      %ld\n", pool_id->alignment);
    printf("pool_id->num_incr       %ld\n", pool_id->num_incr);
    printf("pool_id->num_totl       %ld\n", pool_id->num_totl);
    printf("pool_id->part_id        %p\n",  pool_id->part_id);
    printf("pool_id->options        0x%lx\n", pool_id->options);
    printf("pool_id->block_list     %p\n",  &pool_id->block_list);
    printf("pool_id->block_list     %d blocks\n", dll_count(&pool_id->block_list));
    printf("pool_id->free_items     %p\n",  &pool_id->free_items);
    printf("pool_id->free_items     %d free items\n", dll_count(&pool_id->free_items));
    printf("pool_id->free_count     %ld\n", pool_id->free_count);
    printf("+++++++++++++++++++++++++++++++++++++++++++\n");
}

void pool_create_test_00(void)
{
    printf("\n---start pool_create_test_00 \n");

    g_pool_id = pool_create("pool_test",
                            32,
                            8,

                            20,
                            10,

                            &part_id_t,
                            POOL_THREAD_SAFE | POOL_CHECK_ITEM
    );

    printf("+++end pool_create_test_00 \n");
}

void pool_delete_test_00(void)
{
    printf("\n--- start pool_delete_test_00\n");

    pool_delete(g_pool_id, TRUE);

    printf("+++ end pool_delete_test_00\n");
}

void pool_block_add_test_00(void)
{
    ULONG size = g_pool_id->siz_itm_real * g_pool_id->num_incr;
    void *p_block = (void *)malloc(size);

    printf("\n ---start pool_block_add_test_00\n");
    printf(" p_block %p, size %ld\n", p_block, size);

    pool_block_add(g_pool_id, p_block, size);

    printf("+++end pool_block_add_test_00 \n");
}

void pool_unused_blocks_free_test_00(void)
{
    printf("\n ---start pool_block_is_free_00 \n");

    pool_unused_blocks_free(g_pool_id);

    printf("+++end pool_block_is_free_00 \n");
}

void pool_item_get_test_00(void)
{
    void *p_item = NULL;

    printf("\n ---start pool_item_get_test_00 \n");

    p_item = pool_item_get(g_pool_id);

    printf("get and return item is %p\n", p_item);

    pool_item_return(g_pool_id, p_item);

    printf(" ---end pool_item_get_test_00 \n");
}

void pool_id_list_get_test_00(void)
{
    int count, idx;
    POOL_ID list[5] = {NULL};

    printf("\n ---start pool_id_list_get_test_00 \n");

    printf(" g_pool_id %p\n", g_pool_id);

    count = pool_id_list_get(list, 5);

    for(idx = 0; idx < count; idx ++){
        printf(" list pool id %d is %p\n", idx, list[idx]);
    }

    printf(" count %d\n", count);

    printf(" ---end pool_id_list_get_test_00 \n");
}

void main(void)
{
    printf("\nstart pool_lib_test !!!\r\n");

    pool_create_test_00();
    pool_id_show(g_pool_id);

    pool_block_add_test_00();
    pool_id_show(g_pool_id);

    pool_unused_blocks_free_test_00();
    pool_id_show(g_pool_id);

    pool_item_get_test_00();
    pool_id_show(g_pool_id);

    pool_id_list_get_test_00();

//final delete the global pool id.
    pool_delete_test_00();
    pool_id_show(g_pool_id);

    printf("\n end !!!\r\n");
}
