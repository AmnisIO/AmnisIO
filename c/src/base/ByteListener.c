#include "ByteListener.h"

static void _next (struct ByteListenerInternal *self, Byte v) {
  ByteListener *listener = (ByteListener *) self;
  listener->next (listener, v);
}
static void _error (struct ByteListenerInternal *self, int e) {
  ByteListener *listener = (ByteListener *) self;
  listener->error (listener, e);
}
static void _complete (struct ByteListenerInternal *self) {
  ByteListener *listener = (ByteListener *) self;
  listener->complete (listener);
}

ByteListener *
byte_listener_create (byte_listener_next next, byte_listener_error error, byte_listener_complete complete) {
  ByteListener *listener = xmalloc (sizeof (ByteListener));
  listener->_next = _next;
  listener->_error = _error;
  listener->_complete = _complete;
  listener->next = next;
  listener->error = error;
  listener->complete = complete;
  return listener;
}