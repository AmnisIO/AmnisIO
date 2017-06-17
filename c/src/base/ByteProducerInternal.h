#ifndef C_BYTEPRODUCER_H
#define C_BYTEPRODUCER_H

#include "ByteListener.h"
#include "VariableLengthArray.h"

typedef struct ByteProducerInternal {
  void (*_start) (struct ByteListenerInterl *listener);
  void (*_stop) ();
} ByteProducerInternal;

#endif // C_BYTEPRODUCER_H
