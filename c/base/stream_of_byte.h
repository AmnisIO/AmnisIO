#ifndef INCLUDE_STREAM_OF_BYTE_H
#define INCLUDE_STREAM_OF_BYTE_H

#include "varray.h"
#include "utils.h"

typedef uint8_t byte;

struct byte_stream {
	void(*next)(struct byte_stream *self, byte v);
	void(*error)(struct byte_stream *self, byte e);
	void(*complete)(struct byte_stream *self);
	varray *listeners;
};

typedef struct byte_stream stream_of_byte;

stream_of_byte* stream_of_byte_create();
stream_of_byte* stream_of_byte_init();
stream_of_byte* stream_add_listener(stream_of_byte *stream, stream_of_byte *listener);

#endif