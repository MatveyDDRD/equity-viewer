#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynArray.h"

// make dynamic array
dynArray* dynArrayMake()
{
	dynArray *self = (dynArray*)malloc(sizeof(dynArray));
	self->array = NULL;
	self->elementsNum = 0;
	return self;
}

// add element
// use macro dynArrayAddelement
void dynArrayAddElement_private(dynArray *self, void* element, size_t size)
{
	self->array = realloc(self->array, (self->elementsNum + 1) * sizeof(void*));
	self->array[self->elementsNum] = malloc(size);
	memcpy(self->array[self->elementsNum], element, size);
	self->elementsNum++;
}


void* dynArrayGetElement(dynArray *self, int index)
{
	return self->array[index];
}

// remove element
void dynArrayRemoveElement(dynArray *self, int index)
{
	free(self->array[index]);

	for (int i = index; i < self->elementsNum - 1; ++i)
	{
		self->array[i] = self->array[i + 1];
	}

	self->elementsNum--;
	self->array = realloc(self->array, self->elementsNum * sizeof(void*));
}


// remove array
void dynArrayRemove(dynArray* self)
{
	for (int i = 0; i < self->elementsNum; ++i)
	{
		free(self->array[i]);
	}
	free(self->array);
	free(self);
}