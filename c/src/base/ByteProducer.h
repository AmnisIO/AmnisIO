#ifndef C_BYTEPRODUCER_H
#define C_BYTEPRODUCER_H

#include "ByteListener.h"

typedef struct ByteProducer {
  void (*next) (struct ByteProducer *self, Byte v);
  void (*error) (struct ByteProducer *self, Byte e);
  void (*complete) (struct ByteProducer *self);
  VariableLengthArray *listeners;
  void (*init) (struct ByteProducer *self);
} ByteProducer;

ByteProducer *byte_producer_create ();

#endif // C_BYTEPRODUCER_H
