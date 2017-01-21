#include "array.h"
#include "memory.h"

static resizeconfig arc = {
	0,   /*	min capacity */
	2,3, /* min usage */
	1,1, /* max usage */
	3,2  /* growth factor */ 
};

array *aCreate(sizet elmsize)
{
	array *self;
	
	self = alloc(sizeof(array));
	aInit(self, elmsize);
}

void aInit(array *self, sizet elmsize)
{
	self->capacity = 0;
	self->usage = 0;
	self->elmsize = elmsize;
	self->data = 0;
	aResize(self, self->usage);
}

void aDelete(array* self)
{
	aDestroy(self);
	dealloc(self);
}

void aDestroy(array* self)
{
	aResize(self, 0);
}

void aResize(array *self, ulong usage)
{
	ulong newCapacity;
	uchar *data;
	
	newCapacity = getNeededCapacity(usage, self->capacity, &arc);
	
	if(newCapacity != self->capacity) {
		data = self->data = resize(self->data, newCapacity * self->elmsize);
		
		if(newCapacity > self->capacity) {
			initmem(data + self->capacity * self->elmsize, (newCapacity - self->capacity) * self->elmsize);
		}
		
		self->capacity = newCapacity;
		self->usage = usage;
	}
}

aiter aIter(array *self, aiter i)
{
	if(i == 0) {
		return self->data;
	}
	else {
		i += self->elmsize;
		
		if(i < self->usage * self->elmsize) {
			return i;
		}
		else {
			return 0;
		}
	}
}

void *aData(aiter i)
{
	return i;
}

ulong getNeededCapacity(ulong usage, ulong capacity, resizeconfig* rc)
{
	while(usage < capacity * rc->minUsageN / rc->minUsageD && capacity > rc->minCapacity) {
		capacity = max(rc->minCapacity, capacity * rc->growthFactorD / rc->growthFactorN);
	}
	
	while(usage > capacity * rc->maxUsageN / rc->maxUsageD) {
		capacity = max(capacity + 1, capacity * rc->growthFactorN / rc->growthFactorD);
	}
	
	return capacity;
}
