#ifndef C_BYTESTREAM_H
#define C_BYTESTREAM_H

#include "ByteListener.h"
#include "ByteStreamSubscription.h"
#include "ByteProducer.h"

typedef struct ByteStream {
  void (*add_listener) (ByteListener *listener);
  void (*remove_listener) (ByteListener *listener);
  ByteStreamSubscription *(*subscribe) (ByteListener *listener);
} ByteStream;

ByteStream *byte_stream_create (ByteProducer *producer);

#endif // C_BYTESTREAM_H
