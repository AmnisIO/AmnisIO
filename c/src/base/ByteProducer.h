#ifndef C_BYTEPRODUCER_H
#define C_BYTEPRODUCER_H

#include "ByteListener.h"

typedef struct ByteProducer {
  void (*_start) (struct ByteListener *listener);
  void (*_stop) ();
} ByteProducer;

#endif // C_BYTEPRODUCER_H
