#ifndef C_BYTEPRODUCERINTERNAL_H
#define C_BYTEPRODUCERINTERNAL_H

#include "ByteListenerInternal.h"

typedef struct ByteProducerInternal {
  void (*_start) (struct ByteProducerInternal *self, struct ByteListenerInternal *listener);
  void (*_stop) (struct ByteProducerInternal *self);
} ByteProducerInternal;

#endif // C_BYTEPRODUCERINTERNAL_H
