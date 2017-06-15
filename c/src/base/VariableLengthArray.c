#include "VariableLengthArray.h"

static void _push(VariableLengthArray *array, void *data) {
	size_t toallocate;
	size_t size = sizeof(void*);
	if ((array->allocated - array->used) < size) {
		toallocate = array->allocated == 0 ? size : (array->allocated * 2);
		array->memory = realloc(array->memory, toallocate);
		array->allocated = toallocate;
	}
	array->memory[++array->index] = data;
	array->used = array->used + size;
}

static int _length(VariableLengthArray *array) {
	return array->index + 1;
}

static void _clear(VariableLengthArray *array) {
	int i;
	for (i = 0; i < _length(array); i++)
	{
		array->memory[i] = NULL;
	}
	array->used = 0;
	array->index = -1;
}

static void _free(VariableLengthArray *array) {
	free(array->memory);
}

static void* _get(VariableLengthArray *array, int index) {
	if (index < 0 || index > array->index)
		return NULL;
	return array->memory[index];
}

static void _insert(VariableLengthArray *array, int index, void *data) {
	if (index < 0 || index > array->index)
		return;
	array->memory[index] = data;
}

void variable_length_array_initialize(VariableLengthArray **array) {
	*array = (VariableLengthArray*)malloc(sizeof(VariableLengthArray));
	(*array)->memory = NULL;
	(*array)->allocated = 0;
	(*array)->used = 0;
	(*array)->index = -1;
  (*array)->push = _push;
  (*array)->length = _length;
  (*array)->clear = _clear;
  (*array)->free = _free;
  (*array)->get = _get;
  (*array)->insert = _insert;
}


