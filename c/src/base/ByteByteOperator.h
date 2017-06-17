#ifndef C_BYTEBYTEOPERATOR_H
#define C_BYTEBYTEOPERATOR_H

#include "ByteProducerInternal.h"
#include "ByteSender.h"

typedef struct ByteByteOperator {
  ByteSender *sender;
  ByteProducerInternal *_producer;
  ByteListenerInternal *_listener;
  int type;
  ByteStream* ins;
  void (*_start) (ByteStream *out);
} ByteByteOperator;

#endif //C_BYTEBYTEOPERATOR_H
