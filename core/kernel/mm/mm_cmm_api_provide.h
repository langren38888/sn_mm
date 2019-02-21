#ifndef MM_CMM_API_PROVIDE_H
#define MM_CMM_API_PROVIDE_H

#include <sn_type.h>

/* ----------temperory */
struct mem_part{
    ULONG  tmp;
};
typedef struct mem_part *PART_ID;

typedef struct semaphore{ /* SEMAPHORE */
    ULONG  tmp;
}SEMAPHORE;
/* ++++++++++temperory */

extern char *mem_part_alloc(PART_ID part_id, UINT32 size);
extern void mem_part_free(PART_ID part_id, char *ptr);

#endif
