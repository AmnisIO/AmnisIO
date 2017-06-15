#ifndef INCLUDE_BYTE_PRODUCER_H
#define INCLUDE_BYTE_PRODUCER_H

#include "VariableLengthArray.h"
#include "utils.h"

typedef uint8_t Byte;

typedef struct ByteProducer {
	void (*next)(struct ByteProducer *self, Byte v);
	void (*error)(struct ByteProducer *self, Byte e);
	void (*complete)(struct ByteProducer *self);
	VariableLengthArray *listeners;
  void (*init)();
} ByteProducer;

#endif
