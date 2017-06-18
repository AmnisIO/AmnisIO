#include "ByteListernerManager.h"
#include "ByteByteOperator.h"

byte_listener_internal_next byte_listener_internal_next_get (ByteListenerInternal *listener) {
  switch (listener->type) {
    case OBSERVABLE_TYPE_LISTENER:
    case OBSERVABLE_TYPE_LISTENER_INTERNAL:
    case OBSERVABLE_TYPE_STREAM:
      return listener->_next;
    case OBSERVABLE_TYPE_OPERATOR:
      return ((ByteByteOperator *) listener)->_next;
    default:
      return NULL;
  }
}

byte_listener_internal_error byte_listener_internal_error_get (ByteListenerInternal *listener) {
  switch (listener->type) {
    case OBSERVABLE_TYPE_LISTENER:
    case OBSERVABLE_TYPE_LISTENER_INTERNAL:
    case OBSERVABLE_TYPE_STREAM:
      return listener->_error;
    case OBSERVABLE_TYPE_OPERATOR:
      return ((ByteByteOperator *) listener)->_error;
    default:
      return NULL;
  }
}

byte_listener_internal_complete byte_listener_internal_complete_get (ByteListenerInternal *listener) {
  switch (listener->type) {
    case OBSERVABLE_TYPE_LISTENER:
    case OBSERVABLE_TYPE_LISTENER_INTERNAL:
    case OBSERVABLE_TYPE_STREAM:
      return listener->_complete;
    case OBSERVABLE_TYPE_OPERATOR:
      return ((ByteByteOperator *) listener)->_complete;
    default:
      return NULL;
  }
}
