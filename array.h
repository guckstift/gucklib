#ifndef ARRAY_H
#define ARRAY_H

#include "basetypes.h"
#include "utils.h"

STRUCT(array) {
	ulong capacity;
	ulong usage;
	sizet elmsize;
	void *data;
};

typedef uchar *aiter;

STRUCT(resizeconfig) {
	ulong minCapacity;
	ulong minUsageN;
	ulong minUsageD;
	ulong maxUsageN;
	ulong maxUsageD;
	ulong growthFactorN;
	ulong growthFactorD;
};

array *aCreate(sizet elmsize);
void aInit(array *self, sizet elmsize);
void aDelete(array *self);
void aDestroy(array *self);

aiter aIter(array *self, aiter i);
void *aData(aiter i);

void aResize(array *self, ulong usage);

ulong getNeededCapacity(ulong usage, ulong capacity, resizeconfig* rc);

#endif
