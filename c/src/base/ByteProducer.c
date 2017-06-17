#include "ByteProducer.h"

static void _start (struct ByteProducerInternal *self, struct ByteListenerInternal *listener) {
  ByteProducer *producer = (ByteProducer *) self;
  producer->start (producer, (ByteListener *) listener);
}
static void _stop (struct ByteProducerInternal *self) {
  ByteProducer *producer = (ByteProducer *) self;
  producer->stop (producer);
};

ByteProducer *byte_producer_create (byte_producer_start start, byte_producer_stop stop) {
  ByteProducer *producer = xmalloc (sizeof (ByteProducer));
  producer->start = start;
  producer->stop = stop;
  producer->_start = _start;
  producer->_stop = _stop;
  return producer;
}