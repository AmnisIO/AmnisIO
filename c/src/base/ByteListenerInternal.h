#ifndef C_BYTELISTENERINTERNAL_H
#define C_BYTELISTENERINTERNAL_H

#include "Byte.h"
#include "utils.h"
#include "ByteObservable.h"

typedef struct ByteListenerInternal {
  ByteObservableType type;
  void (*_next) (struct ByteListenerInternal *self, Byte v);
  void (*_error) (struct ByteListenerInternal *self, int e);
  void (*_complete) (struct ByteListenerInternal *self);
} ByteListenerInternal;

typedef void (*byte_listener_internal_next) (struct ByteListenerInternal *self, Byte v);
typedef void (*byte_listener_internal_error) (struct ByteListenerInternal *self, int e);
typedef void (*byte_listener_internal_complete) (struct ByteListenerInternal *self);

#endif //C_BYTELISTENERINTERNAL_H
