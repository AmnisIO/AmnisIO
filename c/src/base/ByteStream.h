#ifndef C_BYTESTREAM_H
#define C_BYTESTREAM_H

#include "ByteListener.h"
#include "ByteProducer.h"
#include "ByteSubscription.h"
#include "VariableLengthArray.h"
#include "Boolean.h"
#include "ByteProducerFromArray.h"
#include "ByteListernerManager.h"

typedef Byte (*byte_steam_map_function) (Byte value);
typedef Boolean (*byte_steam_filter_function) (Byte value);

typedef struct ByteStream {
  ByteObservableType type;
  byte_listener_internal_next _next;
  byte_listener_internal_error _error;
  byte_listener_internal_complete _complete;
  ByteProducerInternal *_producer;
  VariableLengthArray *_internal_listeners;
  int _stop_id;
  int _error_code;
  void (*_teardown) (struct ByteStream *self);
  void (*_stop_now) (struct ByteStream *self);
  void (*_add) (struct ByteStream *self, ByteListenerInternal *listener);
  void (*_remove) (struct ByteStream *self, ByteListenerInternal *listener);
  void (*add_listener) (struct ByteStream *self, ByteListener *listener);
  void (*remove_listener) (struct ByteStream *self, ByteListener *listener);
  ByteSubscription *(*subscribe) (struct ByteStream *self, ByteListener *listener);
  struct ByteStream *(*map) (struct ByteStream *self, byte_steam_map_function map);
  struct ByteStream *(*mapTo) (struct ByteStream *self, Byte value);
  struct ByteStream *(*filter) (struct ByteStream *self, byte_steam_filter_function filter);
  struct ByteStream *(*take) (struct ByteStream *self, int count);
  struct ByteStream *(*drop) (struct ByteStream *self, int count);
  struct ByteStream *(*last) (struct ByteStream *self);
} ByteStream;

ByteStream *byte_stream_create (ByteProducer *producer);
ByteStream *byte_stream_never ();
ByteStream *byte_stream_empty ();
ByteStream *byte_stream_from_variable_length_array (VariableLengthArray *array);
ByteStream *byte_stream_from_array (Byte array[], int size);

#endif // C_BYTESTREAM_H
