#ifndef SN_COMMON_H
#define SN_COMMON_H
/*
 * this file contain that some common macro
 */

#define MAX(a, b)        ((a) > (b)? (a):(b))
#define MIN(a, b)        ((a) < (b)? (a):(b))

#define ROUND_UP_UL(x, align)   (((unsigned long) (x) + ((unsigned long) align - 1)) & \
                                 ~((unsigned long) align - 1))
#define ROUND_DOWN_UL(x, align) ((unsigned long) (x) & ~((unsigned long) align - 1))
#define ALIGNED_UL(x, align)    (((unsigned long) (x) & ((unsigned long) align - 1)) == 0)

#define ROUND_UP    ROUND_UP_UL
#define ROUND_DOWN  ROUND_DOWN_UL
#define ALIGNED     ALIGNED_UL

#ifdef _BIG_ENDIAN
#undef _BIG_ENDIAN
#endif /* _BIG_ENDIAN */

#define _BIG_ENDIAN 1234

#ifdef _LITTLE_ENDIAN
#undef _LITTLE_ENDIAN
#endif /* _LITTLE_ENDIAN */

#define _LITTLE_ENDIAN  4321

#define _BYTE_ORDER _BIG_ENDIAN

#endif //SN_COMMON_H