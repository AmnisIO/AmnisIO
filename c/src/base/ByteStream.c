#include "ByteStream.h"

static void _next (ByteStream *stream, Byte v) {
  VariableLengthArray *array = stream->listeners;
  int length = array->length (array);
  for (int i = 0; i < length; i++) {
    ByteListener *listener = ((ByteListener *) array->get (array, i));
    listener->next (listener, v);
  }
};

static void _error (ByteStream *stream, int e) {
  VariableLengthArray *listeners = stream->listeners;
  int length = listeners->length (listeners);
  for (int i = 0; i < length; i++) {
    ByteListener *listener = ((ByteListener *) listeners->get (listeners, i));
    listener->error (listener, e);
  }
  listeners->free (listeners);
  free (listeners);
};

static void _complete (ByteStream *stream) {
  VariableLengthArray *listeners = stream->listeners;
  int length = listeners->length (listeners);
  for (int i = 0; i < length; i++) {
    ByteListener *listener = ((ByteListener *) listeners->get (listeners, i));
    listener->complete (listener);
  }
  listeners->free (listeners);
  free (listeners);
};

ByteStream *byte_stream_create (ByteProducer *producer) {
  ByteStream *stream = xmalloc (sizeof (ByteStream));
  stream->next = _next;
  stream->error = _error;
  stream->complete = _complete;
  variable_length_array_initialize (&(stream->listeners));
  producer->add_listener (producer, (ByteListener *) stream);
  return stream;
}
