#include "ByteProducer.h"

static void _next (ByteProducer *self, Byte v) {
  VariableLengthArray *listeners = self->listeners;
  int length = listeners->length (listeners);
  for (int i = 0; i < length; i++) {
    ByteListener *listener = ((ByteListener *) listeners->get (listeners, i));
    listener->next (listener, v);
  }
}

static void _error (ByteProducer *self, Byte v) {
  VariableLengthArray *listeners = self->listeners;
  int length = listeners->length (listeners);
  for (int i = 0; i < length; i++) {
    ByteListener *listener = ((ByteListener *) listeners->get (listeners, i));
    listener->error (listener, v);
  }
  listeners->free(listeners);
  free(listeners);
}

static void _complete (ByteProducer *self) {
  VariableLengthArray *listeners = self->listeners;
  int length = listeners->length (listeners);
  for (int i = 0; i < length; i++) {
    ByteListener *listener = ((ByteListener *) listeners->get (listeners, i));
    listener->complete (listener);
  }
  listeners->free(listeners);
  free(listeners);
}

ByteProducer *byte_producer_create () {
  ByteProducer *producer = xmalloc (sizeof (ByteProducer));
  producer->next = _next;
  producer->error = _error;
  producer->complete = _complete;
  variable_length_array_initialize (&(producer->listeners));
  return producer;
}