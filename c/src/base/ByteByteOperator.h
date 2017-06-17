#ifndef C_BYTEBYTEOPERATOR_H
#define C_BYTEBYTEOPERATOR_H

#include "ByteProducerInternal.h"
#include "ByteSender.h"

typedef struct ByteByteOperator {
  ByteSender *_sender;
  ByteProducerInternal *_producer;
  ByteListenerInternal *_listener;
  int type;
  ByteStream* in;
  void (*_start) (struct ByteByteOperator *self, ByteStream *out);
} ByteByteOperator;

#endif //C_BYTEBYTEOPERATOR_H
