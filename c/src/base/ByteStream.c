#include "ByteStream.h"

static void _next(ByteStream *stream, byte v) {
	VariableLengthArray *array = stream->listeners;
	int length = array->length(array);
	for (int i = 0; i < length; i++) {
		ByteStream *listener = ((ByteStream *)array->get(array, i));
		listener->next(listener, v);
	}
};

static void _error(ByteStream *stream, byte e) {
	varray *array = stream->listeners;
	int length = array->length(array);
	for (int i = 0; i < length; i++) {
		ByteStream *listener = ((ByteStream *)array->get(array, i));
		listener->error(listener, e);
	}
};

static void _complete(ByteStream *stream) {
	varray *array = stream->listeners;
	int length = array->length(array);
	for (int i = 0; i < length; i++) {
		ByteStream *listener = ((ByteStream *)array->get(array, i));
		listener->complete(listener);
	}
};

ByteStream* byte_stream_create(ByteProducer *producer) {
	ByteStream* stream = xmalloc(sizeof(ByteStream));
	stream->next = _next;
	stream->error = _error;
	stream->complete = _complete;
	variable_length_array_initialize(&(stream->listeners));
	return stream;
}
