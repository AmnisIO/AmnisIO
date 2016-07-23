/**
  Arduino/Genuino UNO
  PIN Configuration
  Refer: https://www.arduino.cc/en/uploads/Main/ArduinoUno_r2_front.jpg
  D0-D13 - 14 digital IN/OUT pins
  A0-A5 - 6 analog IN, digital OUT pins
  LED - D13 is also the on board LED
*/

/**
  The outputs to the board. The outputs are written internally.
*/

#ifndef RIOT_ARDUINO_UNO_H
#define RIOT_ARDUINO_UNO_H

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

/**
  The inputs that we can read from the arduino uno. Reading of
  the inputs is written internally, we just have to use these streams.
*/
struct riot_arduino_uno_sources_t {
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
  /**
    The following are diabled, because stream_of_unit16_t is not
    available in the base stream library yet. Hence we are not able
    to use the 10-bit resolution analog inputs as of now.
  */
  // stream_of_uint16_t *A0;
  // stream_of_uint16_t *A1;
  // stream_of_uint16_t *A2;
  // stream_of_uint16_t *A3;
  // stream_of_uint16_t *A4;
  // stream_of_uint16_t *A5;
  // stream_of_uint16_t *LED;
};

typedef struct riot_arduino_uno_sources_t riot_arduino_uno_sources;

riot_arduino_uno_sinks* riot_arduino_uno_sinks_create();
riot_arduino_uno_sources* riot_arduino_uno_sources_create();

#endif
