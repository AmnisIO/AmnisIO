#ifndef INCLUDE_VARRAY_H
#define INCLUDE_VARRAY_H

#include <stdio.h>

typedef struct varray_t {
	void **memory;
	size_t allocated;
	size_t used;
	int index;
} varray;

void varray_init(varray **array);
void varray_push(varray *array, void *data);
int varray_length(varray *array);
void varray_clear(varray *array);
void varray_free(varray *array);
void* varray_get(varray *array, int index);
void varray_insert(varray *array, int index, void *data);

#endif
