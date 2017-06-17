#include "ByteByteMap.h"

static void _start (ByteProducerInternal *self, ByteListenerInternal *out) {
  ByteByteMap *operator = (ByteByteMap *) self;
  ByteStream *stream = (ByteStream *) out;
  operator->out = stream;
  operator->in->_add (operator->in, (ByteListenerInternal *) operator);
}

static void _stop (ByteProducerInternal *self) {
  ByteByteMap *operator = (ByteByteMap *) self;
  operator->in->_remove (operator->in, (ByteListenerInternal *) operator);
  operator->out = NULL;
}

static void _next (ByteListenerInternal *self, Byte value) {
  ByteByteMap *operator = (ByteByteMap *) self;
  Byte mapped = operator->map (value);
  operator->out->_next ((ByteListenerInternal *) operator->out, mapped);
}

static void _error (ByteListenerInternal *self, int error) {
  ByteByteMap *operator = (ByteByteMap *) self;
  operator->out->_error ((ByteListenerInternal *) operator->out, error);

}

static void _complete (ByteListenerInternal *self) {
  ByteByteMap *operator = (ByteByteMap *) self;
  operator->out->_complete ((ByteListenerInternal *) operator->out);
}

ByteByteMap *byte_byte_map_create (ByteStream *in, byte_byte_map_function map) {
  ByteByteMap *operator = xmalloc (sizeof (ByteByteMap));
  byte_byte_operator_initialize ((ByteByteOperator *) operator);
  operator->operation = OPERATOR_MAP;
  operator->in = in;
  operator->map = map;
  operator->_start = _start;
  operator->_stop = _stop;
  operator->_next = _next;
  operator->_error = _error;
  operator->_complete = _complete;
  return operator;
}
