#ifndef BASETYPES_H
#define BASETYPES_H

/* size_t, offsetof */
#include <stddef.h>
/* ULONG_MAX */
#include <limits.h>

/* convenience typedefs */
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef size_t sizet;

/* boolean */
typedef uchar bool;

/* constants */
#define false 0
#define true 1
#define ulongMax ULONG_MAX

#endif
