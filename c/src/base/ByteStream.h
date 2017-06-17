#ifndef C_BYTESTREAM_H
#define C_BYTESTREAM_H

#include "ByteProducer.h"

typedef struct ByteStream {
  void (*next) (struct ByteStream *self, Byte v);
  void (*error) (struct ByteStream *self, int e);
  void (*complete) (struct ByteStream *self);
  VariableLengthArray *listeners;
} ByteStream;

ByteStream *byte_stream_create (ByteProducer *producer);

#endif // C_BYTESTREAM_H
