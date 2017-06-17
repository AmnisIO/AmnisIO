#include "ByteProducer.h"

static void _start (struct ByteProducerInternal *self, struct ByteListenerInternal *listener) {
  ByteProducer *producer = (ByteProducer *) self;
  producer->start (producer, listener);
}
static void _stop (struct ByteProducerInternal *self) {
  ByteProducer *producer = (ByteProducer *) self;
  producer->stop (producer);
};

void byte_producer_initialize(ByteProducer *producer, byte_producer_start start, byte_producer_stop stop) {
  producer->start = start;
  producer->stop = stop;
  producer->_start = _start;
  producer->_stop = _stop;
}

ByteProducer *byte_producer_create (byte_producer_start start, byte_producer_stop stop) {
  ByteProducer *producer = xmalloc (sizeof (ByteProducer));
  byte_producer_initialize (producer, start, stop);
  return producer;
}