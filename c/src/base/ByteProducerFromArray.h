#ifndef C_BYTEPRODUCERFROMARRAY_H
#define C_BYTEPRODUCERFROMARRAY_H


#include "ByteProducer.h"
#include "VariableLengthArray.h"

typedef struct ByteProducerFromArray {
  byte_producer_internal_start _start;
  byte_producer_internal_stop _stop;
  byte_producer_start start;
  byte_producer_stop stop;
  VariableLengthArray *array;
} ByteProducerFromArray;

ByteProducer *byte_producer_from_array(VariableLengthArray *array);
#endif //C_BYTEPRODUCERFROMARRAY_H
