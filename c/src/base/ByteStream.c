#include "ByteStream.h"
#include "ByteByteMap.h"
#include "ByteStreamTimer.h"

int STOP_ID_NONE = 0;

int ERROR_NONE = 0;

static void _next (ByteListenerInternal *self, Byte value) {
  ByteStream *stream = (ByteStream *) self;
  VariableLengthArray *internal_listeners = stream->_internal_listeners;
  int length = internal_listeners->length (internal_listeners);
  if (length == 0) return;
  for (int i = 0; i < length; i++) {
    ByteListenerInternal *listener = internal_listeners->get (internal_listeners, i);
    byte_listener_internal_next_get (listener) (listener, value);
  }
}

static void _error (ByteListenerInternal *self, int error) {
  ByteStream *stream = (ByteStream *) self;
  if (stream->_error_code != ERROR_NONE) return;
  stream->_error_code = error;
  VariableLengthArray *internal_listeners = stream->_internal_listeners;
  int length = internal_listeners->length (internal_listeners);
  if (length == 0) return;
  for (int i = 0; i < length; i++) {
    ByteListenerInternal *listener = internal_listeners->get (internal_listeners, i);
    byte_listener_internal_error_get (listener) (listener, error);
  }
  stream->_teardown (stream);
}

static void _complete (ByteListenerInternal *self) {
  ByteStream *stream = (ByteStream *) self;
  VariableLengthArray *internal_listeners = stream->_internal_listeners;
  int length = internal_listeners->length (internal_listeners);
  if (length == 0) return;
  for (int i = 0; i < length; i++) {
    ByteListenerInternal *listener = internal_listeners->get (internal_listeners, i);
    byte_listener_internal_complete_get (listener) (listener);
  }
  stream->_teardown (stream);
}

static void _teardown (ByteStream *self) {
  if (self->_internal_listeners->length (self->_internal_listeners) == 0) return;
  if (self->_producer != NULL) self->_producer->_stop (self->_producer);
  self->_error_code = ERROR_NONE;
  self->_internal_listeners->clear (self->_internal_listeners);
}

static void _stop_now (ByteStream *self) {
  if (self->_producer != NULL) self->_producer->_stop (self->_producer);
  self->_error_code = ERROR_NONE;
  self->_stop_id = STOP_ID_NONE;
}

static void _add (ByteStream *stream, ByteListenerInternal *listener) {
  VariableLengthArray *internal_listeners = stream->_internal_listeners;
  int length = internal_listeners->push (internal_listeners, listener);
  if (length > 1) return;
  if (stream->_stop_id != STOP_ID_NONE) {
    byte_stream_timer_clear_timeout (stream->_stop_id);
    stream->_stop_id = STOP_ID_NONE;
  } else {
    ByteProducerInternal *producer = stream->_producer;
    if (producer != NULL) producer->_start (producer, (ByteListenerInternal *) stream);
  }
}

static void *_stop_stream (void *any) {
  ByteStream *stream = (ByteStream *)any;
  stream->_stop_now(stream);
  return NULL;
}

static void _remove (ByteStream *stream, ByteListenerInternal *listener) {
  VariableLengthArray *internal_listeners = stream->_internal_listeners;
  int index = internal_listeners->index_of (internal_listeners, listener);
  if (index > -1) {
    int length = internal_listeners->remove (internal_listeners, index);
    if (stream->_producer != NULL && length == 0) {
      stream->_error_code = ERROR_NONE;
      stream->_stop_id = byte_stream_timer_set_timeout (_stop_stream, stream, 0);
    }
  }
}

static void _add_listener (ByteStream *stream, ByteListener *listener) {
  stream->_add (stream, (ByteListenerInternal *) listener);
}

static void _remove_listener (ByteStream *stream, ByteListener *listener) {
  stream->_remove (stream, (ByteListenerInternal *) listener);
}

typedef struct ByteSubscriptionImplementation {
  void (*unsubscribe) (struct ByteSubscription *self);
  ByteStream *stream;
  ByteListener *listener;
} ByteSubscriptionImplementation;

static void _unsubscribe (ByteStream *stream, ByteListener *listener) {
  stream->remove_listener (stream, listener);
}

static void _unsubscribe_with_subscription (ByteSubscription *subscription) {
  ByteSubscriptionImplementation *implementation = (ByteSubscriptionImplementation *) subscription;
  _unsubscribe (implementation->stream, implementation->listener);
}

static ByteSubscription *_subscribe (ByteStream *stream, ByteListener *listener) {
  stream->add_listener (stream, listener);
  ByteSubscriptionImplementation *subscription = xmalloc (sizeof (ByteSubscriptionImplementation));
  subscription->stream = stream;
  subscription->listener = listener;
  subscription->unsubscribe = _unsubscribe_with_subscription;
  return (ByteSubscription *) subscription;
}
static ByteStream *_map (ByteStream *self, byte_byte_map_function map);

static ByteStream *_create (ByteProducerInternal *producer) {
  ByteStream *stream = xmalloc (sizeof (ByteStream));
  stream->type = OBSERVABLE_TYPE_STREAM;
  stream->_producer = producer;
  stream->_next = _next;
  stream->_error = _error;
  stream->_complete = _complete;
  stream->_teardown = _teardown;
  stream->_stop_now = _stop_now;
  stream->_add = _add;
  stream->_remove = _remove;
  variable_length_array_initialize (&(stream->_internal_listeners));
  stream->_stop_id = STOP_ID_NONE;
  stream->_error_code = ERROR_NONE;
  stream->add_listener = _add_listener;
  stream->remove_listener = _remove_listener;
  stream->subscribe = _subscribe;
  stream->map = _map;
  return stream;
}

static ByteStream *_map (ByteStream *self, byte_byte_map_function map) {
  return _create ((ByteProducerInternal *) byte_byte_map_create (self, map));
}

ByteStream *byte_stream_create (ByteProducer *producer) {
  return _create ((ByteProducerInternal *) producer);
}

static void _never_start (struct ByteProducer *self, struct ByteListenerInternal *listener) {

}

static void _never_stop (struct ByteProducer *self) {

}

static void _complete_immediately (struct ByteProducer *self, struct ByteListenerInternal *listener) {
  listener->_complete (listener);
}

ByteStream *byte_stream_never () {
  return byte_stream_create (byte_producer_create (_never_start, _never_stop));
}

ByteStream *byte_stream_empty () {
  return byte_stream_create (byte_producer_create (_complete_immediately, _never_stop));
}

ByteStream *byte_stream_from_variable_length_array (VariableLengthArray *array) {
  return byte_stream_create (byte_producer_from_variable_length_array (array));
}

ByteStream *byte_stream_from_array (Byte array[], int size) {
  return byte_stream_create (byte_producer_from_array (array, size));
}

