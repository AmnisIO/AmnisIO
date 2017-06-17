#ifndef C_BYTEPRODUCERINTERNAL_H
#define C_BYTEPRODUCERINTERNAL_H

#include "ByteListenerInternal.h"

typedef struct ByteProducerInternal {
  void (*_start) (struct ByteListenerInternal *listener);
  void (*_stop) ();
} ByteProducerInternal;

#endif // C_BYTEPRODUCERINTERNAL_H
