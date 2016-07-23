/**
  Arduino/Genuino UNO
  PIN Configuration
  D0-D13 - 14 digital IN/OUT pins
  A0-A5 - 6 analog IN, digital OUT pins
  LED - D13 is also the on board LED
*/

/**
  The outputs to the board. The outputs are written internally.
*/

#include "stream_of_byte.h"

struct riot_arduino_uno_sinks_t {
  stream_of_byte *D0;
  stream_of_byte *D1;
  stream_of_byte *D2;
  stream_of_byte *D3;
  stream_of_byte *D4;
  stream_of_byte *D5;
  stream_of_byte *D6;
  stream_of_byte *D7;
  stream_of_byte *D8;
  stream_of_byte *D9;
  stream_of_byte *D10;
  stream_of_byte *D11;
  stream_of_byte *D12;
  stream_of_byte *D13;
  stream_of_byte *A0;
  stream_of_byte *A1;
  stream_of_byte *A2;
  stream_of_byte *A3;
  stream_of_byte *A4;
  stream_of_byte *A5;
  stream_of_byte *LED;
};

typedef struct riot_arduino_uno_sinks_t riot_arduino_uno_sinks;


