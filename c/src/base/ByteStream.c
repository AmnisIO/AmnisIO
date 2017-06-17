#include "ByteStream.h"

int STOP_ID_NONE = 0;

int ERROR_NONE = 0;

static void _next (void *self, Byte value) {
  ByteStream *stream = (ByteStream *) self;
  VariableLengthArray *internal_listeners = stream->_internal_listeners;
  int length = internal_listeners->length (internal_listeners);
  if (length == 0) return;
  for (int i = 0; i < length; i++) {
    ByteListenerInternal *listener = internal_listeners->get (internal_listeners, i);
    listener->_next (listener, value);
  }
}

static void _error (void *self, int error) {
  ByteStream *stream = (ByteStream *) self;
  if (stream->_error_code != ERROR_NONE) return;
  stream->_error_code = error;
  VariableLengthArray *internal_listeners = stream->_internal_listeners;
  int length = internal_listeners->length (internal_listeners);
  if (length == 0) return;
  for (int i = 0; i < length; i++) {
    ByteListenerInternal *listener = internal_listeners->get (internal_listeners, i);
    listener->_error (listener, error);
  }
  stream->_teardown (stream);
}

static void _complete (void *self) {
  ByteStream *stream = (ByteStream *) self;
  VariableLengthArray *internal_listeners = stream->_internal_listeners;
  int length = internal_listeners->length (internal_listeners);
  if (length == 0) return;
  for (int i = 0; i < length; i++) {
    ByteListenerInternal *listener = internal_listeners->get (internal_listeners, i);
    listener->_complete (listener);
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
    // TODO: clear the stop task
    // _clear_timeout(stream->_stop_id);
    stream->_stop_id = STOP_ID_NONE;
  } else {
    ByteProducerInternal *producer = stream->_producer;
    if (producer != NULL) producer->_start (producer, (ByteListenerInternal *) stream);
  }
}

static Boolean _if_id_equal (void *data, void *to_find) {
  ByteListenerInternal *actual = (ByteListenerInternal *) to_find;
  ByteListenerInternal *current = (ByteListenerInternal *) data;
  return current->_id == actual->_id;
}

static void _remove (ByteStream *stream, ByteListenerInternal *listener) {
  VariableLengthArray *internal_listeners = stream->_internal_listeners;
  int index = internal_listeners->find_index (internal_listeners, listener, _if_id_equal);
  if (index > -1) {
    int length = internal_listeners->remove (internal_listeners, index);
    if (stream->_producer != NULL && length == 0) {
      stream->_error_code = ERROR_NONE;
      // TODO: schedule a stop
      // stream->_stop_id = _set_timeout (stream->_stop_now, 0);
      stream->_stop_now (stream);
    }
  }
}

static ByteListenerInternal *_to_internal_listener (ByteListener *listener) {
  ByteListenerInternal *internal_listener = xmalloc (sizeof (ByteListenerInternal));
  internal_listener->_id = listener->_id;
  internal_listener->_next = listener->next;
  internal_listener->_error = listener->error;
  internal_listener->_complete = listener->complete;
  return internal_listener;
}

static void _add_listener (ByteStream *stream, ByteListener *listener) {
  stream->_add (stream, _to_internal_listener (listener));
}

static void _remove_listener (ByteStream *stream, ByteListener *listener) {
  ByteListenerInternal *internal_listener = xmalloc (sizeof (ByteListenerInternal));
  internal_listener->_id = listener->_id;
  stream->_remove (stream, internal_listener);
}

static ByteStream *_create (ByteProducerInternal *producer) {
  ByteStream *stream = xmalloc (sizeof (ByteStream));
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
  return stream;
}