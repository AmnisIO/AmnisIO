#include "stream_of_byte_map.h"

typedef struct mapped_stream_of_byte_t {
	void(*next)(stream_of_byte *self, byte v);
	void(*error)(stream_of_byte *self, byte e);
	void(*complete)(stream_of_byte *self);
	varray *listeners;
	byte(*map)(byte value);
} mapped_stream_of_byte;

static void _next(stream_of_byte *stream, byte v) {
	mapped_stream_of_byte* mapped_stream = (mapped_stream_of_byte*)stream;
	byte mapped = mapped_stream->map(v);
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_of_byte *listener = ((stream_of_byte *)varray_get(array, i));
		listener->next(listener, mapped);
	}
};

static mapped_stream_of_byte* mapped_stream_of_byte_create(map_byte_to_byte map) {
	mapped_stream_of_byte* stream = xmalloc(sizeof(mapped_stream_of_byte));
	stream_of_byte_init(stream);
	stream->map = map;
	stream->next = _next;
	return stream;
}

stream_of_byte* stream_of_byte_map(stream_of_byte *stream, map_byte_to_byte mapper) {
	mapped_stream_of_byte* mapped_stream = mapped_stream_of_byte_create(mapper);
	stream_of_byte* mapped_listener = (stream_of_byte*)mapped_stream;
	return (stream_of_byte*)stream_add_listener(stream, mapped_listener);
}

typedef struct mapped_stream_of_byte_with_index_t {
	void(*next)(stream_of_byte *self, byte v);
	void(*error)(stream_of_byte *self, byte e);
	void(*complete)(stream_of_byte *self);
	varray *listeners;
	map_byte_to_byte_with_index map;
  int index;
} mapped_stream_of_byte_with_index;

static void _index_next(stream_of_byte *stream, byte v) {
	mapped_stream_of_byte_with_index* mapped_stream = (mapped_stream_of_byte_with_index*)stream;
  mapped_stream->index = mapped_stream->index+1;
	byte mapped = mapped_stream->map(v, mapped_stream->index);
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_of_byte *listener = ((stream_of_byte *)varray_get(array, i));
		listener->next(listener, mapped);
	}
};

static mapped_stream_of_byte_with_index* mapped_stream_of_byte_with_index_create(map_byte_to_byte_with_index map) {
	mapped_stream_of_byte_with_index* stream = xmalloc(sizeof(mapped_stream_of_byte));
	stream_of_byte_init(stream);
	stream->map = map;
  stream->index = -1;
	stream->next = _index_next;
	return stream;
}

stream_of_byte* stream_of_byte_map_with_index(stream_of_byte *stream, map_byte_to_byte_with_index mapper) {
	mapped_stream_of_byte_with_index* mapped_stream = mapped_stream_of_byte_with_index_create(mapper);
	stream_of_byte* mapped_listener = (stream_of_byte*)mapped_stream;
	return (stream_of_byte*)stream_add_listener(stream, mapped_listener);
}
