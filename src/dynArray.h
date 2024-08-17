#ifndef DYNARRAY_H
#define DYNARRAY_H

typedef struct
{
	void** array;
	int elementsNum;
} dynArray;

// make dynamic array
dynArray* dynArrayMake();

// add element
void dynArrayAddElement_private(dynArray *self, void* element, size_t size);

#define dynArrayAddElement(self, element, type)     	\
{														\
	type temp = element;								\
	dynArrayAddElement_private(self, &temp, sizeof(type));		\
}

// get element
void* dynArrayGetElement(dynArray *self, int index);

// remove element
void dynArrayRemoveElement(dynArray *self, int index);

// remove array
void dynArrayRemove(dynArray* self);

#endif