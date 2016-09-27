#ifndef INCLUDE_STREAM_OF_BYTE_H
#define INCLUDE_STREAM_OF_BYTE_H

#include "varray.h"
#include "utils.h"

typedef uint8_t byte;

typedef struct stream_of_byte_t {
	void(*next)(struct stream_of_byte_t *self, byte v);
	void(*error)(struct stream_of_byte_t *self, byte e);
	void(*complete)(struct stream_of_byte_t *self);
	varray *listeners;
} stream_of_byte;

stream_of_byte* stream_of_byte_create();
stream_of_byte* stream_of_byte_init();
stream_of_byte* stream_add_listener(stream_of_byte *stream, stream_of_byte *listener);

#endif
