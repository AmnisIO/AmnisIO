#include "stream_of_byte.h"

static void _next(stream_of_byte *stream, byte v) {
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_of_byte *listener = ((stream_of_byte *)varray_get(array, i));
		listener->next(listener, v);
	}
};

static void _error(stream_of_byte *stream, byte e) {
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_of_byte *listener = ((stream_of_byte *)varray_get(array, i));
		listener->error(listener, e);
	}
};

static void _complete(stream_of_byte *stream) {
	varray *array = stream->listeners;
	int length = varray_length(array);
	for (int i = 0; i < length; i++) {
		stream_of_byte *listener = ((stream_of_byte *)varray_get(array, i));
		listener->complete(listener);
	}
};

stream_of_byte* stream_of_byte_create() {
	stream_of_byte* stream = xmalloc(sizeof(stream_of_byte));
	return stream_of_byte_init(stream);
}

stream_of_byte* stream_of_byte_init(stream_of_byte *stream) {
	varray_init(&(stream->listeners));
	stream->next = _next;
	stream->error = _error;
	stream->complete = _complete;
	return stream;
}

stream_of_byte* stream_add_listener(stream_of_byte *stream, stream_of_byte *listener) {
	varray* array = stream->listeners;
	varray_push(array, listener);
	int length = varray_length(array);
	return (stream_of_byte *)varray_get(array, length - 1);
}