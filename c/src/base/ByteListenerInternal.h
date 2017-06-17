#ifndef C_BYTELISTENERINTERNAL_H
#define C_BYTELISTENERINTERNAL_H

#include "Byte.h"
#include "utils.h"

typedef struct ByteListenerInternal {
  void (*_next) (struct ByteListenerInternal *self, Byte v);
  void (*_error) (struct ByteListenerInternal *self, int e);
  void (*_complete) (struct ByteListenerInternal *self);
} ByteListenerInternal;

ByteListenerInternal *byte_listener_internal_create ();

#endif //C_BYTELISTENERINTERNAL_H
