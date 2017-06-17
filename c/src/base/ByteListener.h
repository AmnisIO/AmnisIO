#ifndef C_BYTELISTENER_H
#define C_BYTELISTENER_H

#include "ByteListenerInternal.h"

typedef struct ByteListener {
  byte_listener_internal_next _next;
  byte_listener_internal_error _error;
  byte_listener_internal_complete _complete;
  void (*next) (struct ByteListener *self, Byte v);
  void (*error) (struct ByteListener *self, int e);
  void (*complete) (struct ByteListener *self);
} ByteListener;

typedef void (*byte_listener_next) (struct ByteListener *self, Byte v);
typedef void (*byte_listener_error) (struct ByteListener *self, int e);
typedef void (*byte_listener_complete) (struct ByteListener *self);

ByteListener *
byte_listener_create (byte_listener_next next, byte_listener_error error, byte_listener_complete complete);

#endif //C_BYTELISTENER_H
