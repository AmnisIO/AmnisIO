#ifndef C_BYTEBYTEOPERATOR_H
#define C_BYTEBYTEOPERATOR_H

#include "ByteProducerInternal.h"
#include "ByteStream.h"

typedef struct ByteByteOperator {
  ByteProducerInternal *_producer;
  ByteListenerInternal *_listener;
  int type;
  ByteStream *in;
  ByteStream *out;
  void (*_start) (struct ByteByteOperator *self, ByteStream *out);
} ByteByteOperator;

#endif //C_BYTEBYTEOPERATOR_H
