#include "ByteByteOperator.h"

ByteByteOperator *byte_byte_operator_create () {
  ByteByteOperator *operator = xmalloc (sizeof(ByteByteOperator));
  byte_byte_operator_initialize (operator);
  return operator;
}

void byte_byte_operator_initialize (ByteByteOperator *operator) {
  operator->type = OBSERVABLE_TYPE_OPERATOR;
}