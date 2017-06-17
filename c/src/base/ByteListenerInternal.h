#ifndef C_BYTELISTENERINTERNAL_H
#define C_BYTELISTENERINTERNAL_H

#include "Byte.h"
#include "utils.h"

typedef struct ByteListenerInternal {
  void (*next) (struct ByteListenerInternal *self, Byte v);
  void (*error) (struct ByteListenerInternal *self, int e);
  void (*complete) (struct ByteListenerInternal *self);
} ByteListenerInternal;

ByteListenerInternal *byte_listener_internal_create_noop ();

#endif //C_BYTELISTENERINTERNAL_H
