#ifndef C_BYTEPRODUCER_H
#define C_BYTEPRODUCER_H

#include "ByteListener.h"

typedef struct ByteProducer {
  void (*_start) (struct ByteProducer *self, struct ByteListener *listener);
  void (*_stop) (struct ByteProducer *self);
} ByteProducer;

#endif // C_BYTEPRODUCER_H
