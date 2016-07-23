#ifndef INCLUDE_STREAM_OF_BYTE_MAP
#define INCLUDE_STREAM_OF_BYTE_MAP

#include "stream_of_byte.h"

byte(*map_byte_to_byte)(byte value);
byte(*map_byte_to_byte_with_index)(byte value, int index);
stream_of_byte* stream_of_byte_map(stream_of_byte *stream, map_byte_to_byte mapper);
stream_of_byte* stream_of_byte_map(stream_of_byte *stream, map_byte_to_byte_with_index mapper);

#endif
