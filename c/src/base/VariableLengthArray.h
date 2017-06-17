#ifndef C_VARIABLELENGTHARRAY_H
#define C_VARIABLELENGTHARRAY_H

#include "utils.h"
#include "Boolean.h"

typedef Boolean (*variable_length_array_is_equal) (void* data, void* to_find);

typedef struct VariableLengthArray {
  void **memory;
  Size allocated;
  Size used;
  int index;
  int (*push) (struct VariableLengthArray *array, void *data);
  int (*length) (struct VariableLengthArray *array);
  void (*clear) (struct VariableLengthArray *array);
  void (*free) (struct VariableLengthArray *array);
  void *(*get) (struct VariableLengthArray *array, int index);
  void (*insert) (struct VariableLengthArray *array, int index, void *data);
  int (*remove) (struct VariableLengthArray *array, int index);
  int (*index_of) (struct VariableLengthArray *array, void *data);
  int (*find_index) (struct VariableLengthArray *array, void *data, variable_length_array_is_equal is_equal);
} VariableLengthArray;

void variable_length_array_initialize (VariableLengthArray **array);
VariableLengthArray *variable_length_array_create ();

#endif // C_VARIABLELENGTHARRAY_H
