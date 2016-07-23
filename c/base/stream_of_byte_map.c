#include "stream_of_byte_map.h"

struct mapped_byte_stream {
	void(*next)(stream_of_byte *self, byte v);
	void(*error)(stream_of_byte *self, byte e);
	void(*complete)(stream_of_byte *self);
	varray *listeners;
	byte(*map)(byte value);
};

typedef struct mapped_byte_stream mapped_stream_of_byte;

void mapped_stream_of_byte_next(stream_of_byte *stream, byte v) {
	mapped_stream_of_byte* mapped_stream = (mapped_stream_of_byte*)stream;
	byte mapped = mapped_stream->map(v);
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_of_byte *listener = ((stream_of_byte *)varray_get(array, i));
		listener->next(listener, mapped);
	}
};

mapped_stream_of_byte* mapped_stream_of_byte_create(mapper_function_from_byte_to_byte map) {
	mapped_stream_of_byte* stream = xmalloc(sizeof(mapped_stream_of_byte));
	stream_of_byte_init(stream);
	stream->map = map;
	stream->next = mapped_stream_of_byte_next;
	return stream;
}

stream_of_byte* stream_of_byte_map(stream_of_byte *stream, mapper_function_from_byte_to_byte mapper) {
	mapped_stream_of_byte* mapped_stream = mapped_stream_of_byte_create(mapper);
	stream_of_byte* mapped_listener = (stream_of_byte*)mapped_stream;
	return (stream_of_byte*)stream_add_listener(stream, mapped_listener);
}
