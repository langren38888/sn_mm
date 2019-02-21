#include <stdlib.h>
#include "mm_cmm_api_provide.h"

/* ---------- tmp */
char *mem_part_alloc(PART_ID part_id, UINT32 size)
{
    return (char *)malloc(size);
}
void mem_part_free(PART_ID part_id, char *ptr)
{
    free(ptr);
}
/* ++++++++++ tmp */

