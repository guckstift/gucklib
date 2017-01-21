#include <stdlib.h>
#include <string.h>
#include "memory.h"

#ifdef GX_COUNT_MEM_USED
struct _BlockHead {
	sizet size;
};

static sizet _memUsed = 0;
#endif

static ulong _blocksAllocated = 0;

void *alloc(sizet size)
{
	if(size == 0) {
		return 0;
	}
	
#ifdef GX_COUNT_MEM_USED
	struct _BlockHead *blockHead;
	struct _BlockHead *blockData;

	blockHead = malloc(sizeof(struct _BlockHead) + size);
	blockData = blockHead + 1;
	blockHead->size = size;
	_memUsed += size;
#else
	void *blockData;
	
	blockData = malloc(size);
#endif
	
	_blocksAllocated ++;
	
	return blockData;
}

void dealloc(void *ptr)
{
	if(ptr == 0) {
		return;
	}
	
#ifdef GX_COUNT_MEM_USED
	struct _BlockHead *blockData;
	struct _BlockHead *blockHead;

	blockData = ptr;
	blockHead = blockData - 1;
	_memUsed -= blockHead->size;
	free(blockHead);
#else
	free(ptr);
#endif
	
	_blocksAllocated --;
}

void *resize(void *ptr, sizet size)
{
	if(ptr == 0)  {
		return alloc(size);
	}
	
	if(size == 0) {
		dealloc(ptr);
		
		return 0;
	}
	
#ifdef GX_COUNT_MEM_USED
	struct _BlockHead *blockData;
	struct _BlockHead *blockHead;

	blockData = ptr;
	blockHead = blockData - 1;
	_memUsed -= blockHead->size;
	blockHead = realloc(blockHead, sizeof(struct _BlockHead) + size);
	blockHead->size = size;
	_memUsed += size;

	return blockData;
#else
	return realloc(ptr, size);
#endif
}

void initmem(void *ptr, sizet size)
{
	if(ptr != 0) {
		memset(ptr, 0, size);
	}
}

#ifdef GX_COUNT_MEM_USED
sizet getMemUsed()
{
	return _memUsed;
}

sizet getBlockSize(void *ptr)
{
	struct _BlockHead *blockData;
	struct _BlockHead *blockHead;
	
	blockData = ptr;
	blockHead = blockData - 1;
	
	return blockHead->size;
}
#endif

ulong getBlocksAllocated()
{
	return _blocksAllocated;
}
