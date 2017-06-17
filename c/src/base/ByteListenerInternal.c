#include "ByteListenerInternal.h"

static void _next (struct ByteListenerInternal *self, Byte v) {

}
static void _error (struct ByteListenerInternal *self, int e) {

}
static void _complete (struct ByteListenerInternal *self) {

}

ByteListenerInternal *byte_listener_internal_create () {
  ByteListenerInternal *il = xmalloc (sizeof (ByteListenerInternal));
  il->_next = _next;
  il->_error = _error;
  il->_complete = _complete;
  return il;
}