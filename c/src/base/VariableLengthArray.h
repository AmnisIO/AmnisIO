#ifndef C_VARIABLELENGTHARRAY_H
#define C_VARIABLELENGTHARRAY_H

#include "utils.h"

typedef struct VariableLengthArray {
  void **memory;
  Size allocated;
  Size used;
  int index;
  void (*push) (struct VariableLengthArray *array, void *data);
  int (*length) (struct VariableLengthArray *array);
  void (*clear) (struct VariableLengthArray *array);
  void (*free) (struct VariableLengthArray *array);
  void *(*get) (struct VariableLengthArray *array, int index);
  void (*insert) (struct VariableLengthArray *array, int index, void *data);
  void (*remove) (struct VariableLengthArray *array, int index);
  int (*index_of) (struct VariableLengthArray *array, void *data);
} VariableLengthArray;

void variable_length_array_initialize (VariableLengthArray **array);

#endif // C_VARIABLELENGTHARRAY_H
