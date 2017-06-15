#ifndef INCLUDE_BYTE_STREAM_H
#define INCLUDE_BYTE_STREAM_H

#include "VariableLengthArray.h"
#include "utils.h"
#include "ByteProducer.h"

typedef struct ByteStream {
	void (*next)(struct ByteStream *self, Byte v);
	void (*error)(struct ByteStream *self, Byte e);
	void (*complete)(struct ByteStream *self);
	VariableLengthArray *listeners;
} ByteStream;

ByteStream* byte_stream_create(ByteProducer *producer);

#endif
