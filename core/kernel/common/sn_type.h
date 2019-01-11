/*
* sn_type.h
*/

#ifndef SN_TYPE_H
#define SN_TYPE_H

/* general type define */
typedef signed   char       INT8;
typedef unsigned char       UINT8;

typedef signed   short      INT16;
typedef unsigned short      UINT16;

typedef signed   int        INT32;
typedef unsigned int        UINT32;

typedef long                LONG;
typedef unsigned long       ULONG;

typedef signed   long long  INT64;
typedef unsigned long long  UINT64;

#ifndef STATUS
typedef int STATUS;
#endif

#ifndef BOOL
typedef unsigned int BOOL;
#endif

#ifndef LOCAL
#define LOCAL static
#endif

#ifndef OK
#define OK 0
#endif

#ifndef ERROR
#define ERROR -1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif //SN_TYPE_H
