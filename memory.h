#ifndef MEMORY_H
#define MEMORY_H

/* memset */
#include <memory.h>
#include "basetypes.h"

void *alloc(sizet size);
void dealloc(void *ptr);
void *resize(void *ptr, sizet size);
void initmem(void *ptr, sizet size);

#ifdef GX_COUNT_MEM_USED
sizet getMemUsed();
sizet getBlockSize(void *ptr);
#endif
ulong getBlocksAllocated();

#endif
