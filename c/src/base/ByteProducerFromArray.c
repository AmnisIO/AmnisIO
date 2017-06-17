#include "ByteProducerFromArray.h"

static void _from_array_start (ByteProducer *self, ByteListenerInternal *listener) {
  ByteProducerFromArray *producer = (ByteProducerFromArray *) self;
  VariableLengthArray *array = producer->array;
  int length = array->length (array);
  for (int i = 0; i < length; i++) {
    // TODO: Check if this is correct
    Byte *value = array->get (array, i);
    listener->_next (listener, *value);
  }
  listener->_complete (listener);
}

static void _from_array_stop (ByteProducer *self) {

}

ByteProducer *byte_producer_from_array (VariableLengthArray *array) {
  ByteProducerFromArray *producer = xmalloc (sizeof (ByteProducerFromArray));
  producer->array = array;
  byte_producer_initialize ((ByteProducer *) producer, _from_array_start, _from_array_stop);
  return (ByteProducer *) producer;
}