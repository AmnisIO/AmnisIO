#ifndef C_BYTELISTENERINTERNAL_H
#define C_BYTELISTENERINTERNAL_H

#include "Byte.h"
#include "utils.h"

typedef struct ByteListenerInternal {
  int _id;
  void (*_next) (struct ByteListenerInternal *self, Byte v);
  void (*_error) (struct ByteListenerInternal *self, int e);
  void (*_complete) (struct ByteListenerInternal *self);
} ByteListenerInternal;

#endif //C_BYTELISTENERINTERNAL_H
