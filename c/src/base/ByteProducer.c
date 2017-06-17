#include "ByteProducer.h"

static typedef struct ByteProducerImplementation {
  void (*next) (ByteProducer *self, Byte v);
  void (*error) (ByteProducer *self, Byte e);
  void (*complete) (ByteProducer *self);
  void (*add_listener) (ByteProducer *self, ByteListener *listener);
  void (*remove_listener) (ByteProducer *self, ByteListener *listener);
  VariableLengthArray *listeners;
  void (*start) (struct ByteProducerImplementation *self);
  void (*stop) (struct ByteProducerImplementation *self);
  Byte started;
} ByteProducerImplementation;

static void _next (ByteProducer *self, Byte v) {
  ByteProducerImplementation *producer = (ByteProducerImplementation *) self;
  VariableLengthArray *listeners = producer->listeners;
  int length = listeners->length (listeners);
  for (int i = 0; i < length; i++) {
    ByteListener *listener = ((ByteListener *) listeners->get (listeners, i));
    listener->next (listener, v);
  }
}

static void _error (ByteProducer *self, int e) {
  ByteProducerImplementation *producer = (ByteProducerImplementation *) self;
  VariableLengthArray *listeners = producer->listeners;
  int length = listeners->length (listeners);
  for (int i = 0; i < length; i++) {
    ByteListener *listener = ((ByteListener *) listeners->get (listeners, i));
    listener->error (listener, e);
  }
  listeners->free (listeners);
  free (listeners);
}

static void _complete (ByteProducer *self) {
  ByteProducerImplementation *producer = (ByteProducerImplementation *) self;
  VariableLengthArray *listeners = producer->listeners;
  int length = listeners->length (listeners);
  for (int i = 0; i < length; i++) {
    ByteListener *listener = ((ByteListener *) listeners->get (listeners, i));
    listener->complete (listener);
  }
  listeners->free (listeners);
  free (listeners);
}

static void _add_listener (ByteProducer *self, ByteListener *listener) {
  ByteProducerImplementation *producer = (ByteProducerImplementation *) self;
  VariableLengthArray *listeners = producer->listeners;
  listeners->push (listeners, listener);
  if (listeners->length (listeners) > 0 && producer->started == 0) {
    producer->started = 1;
    if (producer->start != NULL) producer->start (producer);
  }
}

static void _remove_listener (ByteProducer *self, ByteListener *listener) {
  ByteProducerImplementation *producer = (ByteProducerImplementation *) self;
  VariableLengthArray *listeners = producer->listeners;
  int length = listeners->length (listeners);
  for (int i = 0; i < length; i++) {
    if (listeners->get (listeners, i) == listeners) {
      listeners->remove (listeners, i);
      break;
    }
  }
  if (listeners->length (listeners) == 0 && producer->started == 1) {
    producer->started == 0;
    if (producer->stop != NULL) producer->stop (producer);
  }
}

ByteProducer *byte_producer_create () {
  ByteProducerImplementation *producer = xmalloc (sizeof (ByteProducerImplementation));
  producer->next = _next;
  producer->error = _error;
  producer->complete = _complete;
  producer->add_listener = _add_listener;
  producer->remove_listener = _remove_listener;
  producer->started = 0;
  variable_length_array_initialize (&(producer->listeners));
  return (ByteProducer *) producer;
}