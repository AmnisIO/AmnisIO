#include "ByteStream.h"

void _next (ByteListener *self, Byte v) {
  printf ("%d\n", v);
}
void _error (ByteListener *self, int error) {
  printf ("%d\n", error);
}
void _complete (ByteListener *self) {
  printf ("completed\n");
}

int main () {
  VariableLengthArray *one_to_four = variable_length_array_create ();
  int a = 1, b = 2, c = 3, d = 4;
  Byte five_to_eight[4] = {5, 6, 7, 8};
  one_to_four->push (one_to_four, &a);
  one_to_four->push (one_to_four, &b);
  one_to_four->push (one_to_four, &c);
  one_to_four->push (one_to_four, &d);
  ByteStream *stream = byte_stream_from_variable_length_array (one_to_four);
  ByteStream *stream_2 = byte_stream_from_array (five_to_eight, 4);
  ByteListener *listener = byte_listener_create (_next, _error, _complete);
  stream->add_listener (stream, listener);
  stream_2->add_listener (stream_2, listener);
  return 0;
}
