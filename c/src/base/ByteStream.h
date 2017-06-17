#ifndef C_BYTESTREAM_H
#define C_BYTESTREAM_H

#include "ByteListener.h"
#include "ByteProducer.h"

typedef struct ByteStream {
  void (*add_listener) (struct ByteStream *self, ByteListener *listener);
  void (*remove_listener) (struct ByteStream *self, ByteListener *listener);
  void *(*subscribe) (struct ByteStream *self, ByteListener *listener);
  void *(*unsubscribe) (struct ByteStream *self, ByteListener *listener);
} ByteStream;

ByteStream *byte_stream_create (ByteProducer *producer);

#endif // C_BYTESTREAM_H
