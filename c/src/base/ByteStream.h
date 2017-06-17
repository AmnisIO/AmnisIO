#ifndef C_BYTESTREAM_H
#define C_BYTESTREAM_H

#include "ByteListener.h"
#include "ByteProducer.h"
#include "ByteSubscription.h"
#include "ByteListenerInternal.h"
#include "ByteProducerInternal.h"
#include "VariableLengthArray.h"

typedef uint8_t Boolean;

typedef Byte (*byte_steam_map_function) (Byte value);
typedef Boolean (*byte_steam_filter_function) (Byte value);

typedef struct ByteStream {
  void (*add_listener) (struct ByteStream *self, ByteListener *listener);
  void (*remove_listener) (struct ByteStream *self, ByteListener *listener);
  void *(*subscribe) (struct ByteStream *self, ByteListener *listener);
  ByteSubscription *(*unsubscribe) (struct ByteStream *self, ByteListener *listener);
  ByteListenerInternal *_internal_listener;
  ByteProducerInternal *_producer;
  VariableLengthArray *_internal_listeners;
  int _stop_id;
  int _error;
  void (*_teardown) (struct ByteStream *self);
  void (*_stop_now) (struct ByteStream *self);
  void (*_add) (struct ByteStream *self, ByteListenerInternal *listener);
  void (*_remove) (struct ByteStream *self, ByteListenerInternal *listener);
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
ByteStream *byte_stream_throw ();
ByteStream *byte_stream_from_array (Byte array[]);
ByteStream *byte_stream_periodic (int milliseconds);
ByteStream *byte_stream_merge (ByteStream streams[]);

#endif // C_BYTESTREAM_H
