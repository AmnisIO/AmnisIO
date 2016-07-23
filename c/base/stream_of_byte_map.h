#ifndef INCLUDE_STREAM_OF_BYTE_MAP
#define INCLUDE_STREAM_OF_BYTE_MAP

#include "stream_of_byte.h"

typedef byte(*mapper_function_from_byte_to_byte)(byte value);
stream_of_byte* stream_of_byte_map(stream_of_byte *stream, mapper_function_from_byte_to_byte mapper);

#endif
