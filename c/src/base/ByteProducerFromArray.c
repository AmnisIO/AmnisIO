#include "ByteProducerFromArray.h"
#include "ByteListernerManager.h"

static void _from_array_start (ByteProducer *self, ByteListenerInternal *listener) {
  ByteProducerFromArray *producer = (ByteProducerFromArray *) self;
  VariableLengthArray *array = producer->array;
  int length = array->length (array);
  for (int i = 0; i < length; i++) {
    Byte *value = array->get (array, i);
    byte_listener_internal_next_get (listener) (listener, *value);
  }
  byte_listener_internal_complete_get (listener) (listener);
}

static void _from_array_stop (ByteProducer *self) {

}

ByteProducer *byte_producer_from_variable_length_array (VariableLengthArray *array) {
  ByteProducerFromArray *producer = xmalloc (sizeof (ByteProducerFromArray));
  producer->array = array;
  byte_producer_initialize ((ByteProducer *) producer, _from_array_start, _from_array_stop);
  return (ByteProducer *) producer;
}

ByteProducer *byte_producer_from_array (Byte array[], int size) {
  ByteProducerFromArray *producer = xmalloc (sizeof (ByteProducerFromArray));
  variable_length_array_initialize (&(producer->array));
  VariableLengthArray *varray = producer->array;
  for (int i = 0; i < size; i++) {
    varray->push (varray, array + i);
  }
  byte_producer_initialize ((ByteProducer *) producer, _from_array_start, _from_array_stop);
  return (ByteProducer *) producer;
}