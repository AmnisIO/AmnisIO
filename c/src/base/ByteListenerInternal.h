#ifndef C_BYTELISTENERINTERNAL_H
#define C_BYTELISTENERINTERNAL_H

#include "ByteListenerGeneric.h"

typedef struct ByteListenerInternal {
  byte_listener_next _next;
  byte_listener_error _error;
  byte_listener_complete _complete;
} ByteListenerInternal;

#endif //C_BYTELISTENERINTERNAL_H
