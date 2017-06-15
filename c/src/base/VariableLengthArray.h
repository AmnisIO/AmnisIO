#ifndef INCLUDE_VARIABLE_LENGTH_ARRAY_H
#define INCLUDE_VARIABLE_LENGTH_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct VariableLengthArray {
	void **memory;
	Size allocated;
	Size used;
	int index;
  void (*push)(VariableLengthArray *array, void *data);
  int (*length)(VariableLengthArray *array);
  void (*clear)(VariableLengthArray *array);
  void (*free)(VariableLengthArray *array);
  void* (*get)(VariableLengthArray *array, int index);
  void (*insert)(VariableLengthArray *array, int index, void *data);
} VariableLengthArray;

void variable_length_array_initialize(VariableLengthArray **array);

#endif
