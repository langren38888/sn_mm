#include <sn_type.h>
#include <sn_common.h>
#include "ffs_lib.h"

UINT8 ffs_msb_tbl[256] = /* lookup table for ffsMsb() */
{
    0, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
    7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
};

UINT8 ffs_lsb_tbl[256] = /* lookup table for ffsLsb() */
{
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,
};

/*
* - find most significant bit set
* i is the value in which to find first set bit
*/
int ffs_msb32(UINT32 i)
{
    union{
        UINT32 dword;
        UINT16 word[2];
        UINT8 byte[4];
    }i_u;

    i_u.dword = i;

#if (_BYTE_ORDER == _BIG_ENDIAN)

    if (i_u.word[0]){    /* Most significant 16-bit */
        if (i_u.byte[0])
            return (ffs_msb_tbl[i_u.byte[0]] + 24 + 1);
        else
            return (ffs_msb_tbl[i_u.byte[1]] + 16 + 1);
    }
    else{    /* Least significant 16-bit */
        if (i_u.byte[2])
            return (ffs_msb_tbl[i_u.byte[2]] + 8 + 1);
        else
            return (ffs_msb_tbl[i_u.byte[3]] + (i ? 1 : 0));
    }

#else /* _BYTE_ORDER == _LITTLE_ENDIAN */

    if (i_u.word[1]){    /* Most significant 16-bit */
        if (i_u.byte[3])
            return (ffs_msb_tbl[i_u.byte[3]] + 24 + 1);
        else
            return (ffs_msb_tbl[i_u.byte[2]] + 16 + 1);
    }
    else{    /* Least significant 16-bit */
        if (i_u.byte[1])
            return (ffs_msb_tbl[i_u.byte[1]] + 8 +1);
        else
            return (ffs_msb_tbl[i_u.byte[0]] + (i ? 1 : 0));
    }

#endif /* _BYTE_ORDER */
}

/*
* - find least significant bit set
* i is the value in which to find first set bit
*/

int ffs_lsb32(UINT32 i)
{
    union{
        UINT32 dword;
        UINT16 word[2];
        UINT8 byte[4];
    }i_u;

    i_u.dword = i;

#if (_BYTE_ORDER == _BIG_ENDIAN)

    if (i_u.word[1]){   /* Least significant 16-bit */
        if (i_u.byte[3])
            return (ffs_lsb_tbl[i_u.byte[3]] + 1);
        else
            return (ffs_lsb_tbl[i_u.byte[2]] + 8 + 1);
    }
    else{   /* Most significant 16-bit */
        if (i_u.byte[1])
            return (ffs_lsb_tbl[i_u.byte[1]] + 16 + 1);
        else
            return (ffs_lsb_tbl[i_u.byte[0]] + (i ? 24+1 : 0));
    }

#else /* _BYTE_ORDER == _LITTLE_ENDIAN */

    if (i_u.word[0]){   /* Least significant 16-bit */
        if (i_u.byte[0])
            return (ffs_lsb_tbl[i_u.byte[0]] + 1);
        else
            return (ffs_lsb_tbl[i_u.byte[1]] + 8 + 1);
    }
    else{    /* Most significant 16-bit */
        if (i_u.byte[2])
            return (ffs_lsb_tbl[i_u.byte[2]] + 16 + 1);
        else
            return (ffs_lsb_tbl[i_u.byte[3]] + (i ? 24+1 : 0));
    }

#endif /* _BYTE_ORDER */
}

/*
* - find most significant bit set
* i is the value in which to find first set bit
*/

int ffs_msb64(UINT64 i)
{
    union{
        UINT64 qword;
        UINT32 dwords[2];
    }i_u;

    i_u.qword = i;

#if _BYTE_ORDER == _BIG_ENDIAN

    if(i_u.dwords[0]){  /* Most significant 32-bit */
        return ffs_msb32(i_u.dwords[0]) + 32;
    }
    else{    /* Least significant 32-bit */
        return ffs_msb32(i_u.dwords[1]);
    }

#else /* _BYTE_ORDER == _LITTLE_ENDIAN */

    if(i_u.dwords[1]){  /* Most significant 32-bit */
        return ffs_msb32(i_u.dwords[1]) + 32;
    }
    else{    /* Least significant 32-bit */
        return ffs_msb32(i_u.dwords[0]);
    }

#endif /* _BYTE_ORDER */
}

/*
* - find least significant bit set
* i is the value in which to find first set bit
*/

int ffs_lsb64(UINT64 i)
{
    union{
        UINT64 qword;
        UINT32 dwords[2];
    }i_u;

    i_u.qword = i;

#if _BYTE_ORDER == _BIG_ENDIAN

    if (i_u.dwords[1]){  /* Least significant 32-bit */
        return ffs_lsb32(i_u.dwords[1]);
    }
    else{    /* Most significant 32-bit */
        return ffs_lsb32(i_u.dwords[0]) + (i ? 32 : 0);
    }

#else /* _BYTE_ORDER == _LITTLE_ENDIAN */

    if (i_u.dwords[0]){  /* Least significant 32-bit */
        return ffs_lsb32(i_u.dwords[0]);
    }
    else{    /* Most significant 32-bit */
        return ffs_lsb32(i_u.dwords[1]) + (i ? 32 : 0);
    }

#endif /* _BYTE_ORDER */
}
