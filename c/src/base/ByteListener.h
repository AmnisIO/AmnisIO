#ifndef C_BYTELISTENER_H
#define C_BYTELISTENER_H

#include "ByteListenerGeneric.h"

typedef struct ByteListener {
  byte_listener_next next;
  byte_listener_error error;
  byte_listener_complete complete;
} ByteListener;

#endif //C_BYTELISTENER_H
