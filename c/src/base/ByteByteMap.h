#ifndef C_BYTEBYTEMAP_H
#define C_BYTEBYTEMAP_H

#include "ByteByteOperator.h"
typedef Byte (*byte_byte_map_function)(Byte value);

typedef struct ByteByteMap {
  ByteObservableType type;
  byte_producer_internal_start _start;
  byte_producer_internal_stop _stop;
  byte_listener_internal_next _next;
  byte_listener_internal_error _error;
  byte_listener_internal_complete _complete;
  ByteStream *in;
  ByteStream *out;
  OperatorType operation;
  byte_byte_map_function map;
} ByteByteMap;

ByteByteMap *byte_byte_map_create(ByteStream *in, byte_byte_map_function map);

#endif //C_BYTEBYTEMAP_H
