#ifndef C_BYTEPRODUCER_H
#define C_BYTEPRODUCER_H

#include "ByteListener.h"
#include "VariableLengthArray.h"

typedef struct ByteProducer {
  void (*next) (struct ByteProducer *self, Byte v);
  void (*error) (struct ByteProducer *self, int e);
  void (*complete) (struct ByteProducer *self);
  void (*add_listener) (struct ByteProducer *self, ByteListener *listener);
  void (*remove_listener) (struct ByteProducer *self, ByteListener *listener);
} ByteProducer;

ByteProducer *byte_producer_create ();

#endif // C_BYTEPRODUCER_H
