#ifndef C_BYTELISTENERINTERNAL_H
#define C_BYTELISTENERINTERNAL_H

#include "Byte.h"
#include "utils.h"

typedef struct ByteListenerInternal {
  int _id;
  void (*_next) (void *self, Byte v);
  void (*_error) (void *self, int e);
  void (*_complete) (void *self);
} ByteListenerInternal;

#endif //C_BYTELISTENERINTERNAL_H
