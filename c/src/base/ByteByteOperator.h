#ifndef C_BYTEBYTEOPERATOR_H
#define C_BYTEBYTEOPERATOR_H

#include "ByteProducerInternal.h"
#include "ByteStream.h"

typedef enum OperatorType {
  OPERATOR_UNKNOWN,
  OPERATOR_MAP
} OperatorType;

typedef struct ByteByteOperator {
  ByteObservableType type;
  OperatorType operation;
  byte_producer_internal_start _start;
  byte_producer_internal_stop _stop;
  byte_listener_internal_next _next;
  byte_listener_internal_error _error;
  byte_listener_internal_complete _complete;
  ByteStream *in;
  ByteStream *out;
} ByteByteOperator;

ByteByteOperator *byte_byte_operator_create ();
void byte_byte_operator_initialize (ByteByteOperator *operator);

#endif //C_BYTEBYTEOPERATOR_H
