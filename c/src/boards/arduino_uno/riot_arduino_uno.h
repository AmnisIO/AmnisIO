/**
  Arduino/Genuino UNO
  PIN Configuration
  Refer: https://www.arduino.cc/en/uploads/Main/ArduinoUno_r2_front.jpg
  D0-D13 - 14 digital IN/OUT pins
  A0-A5 - 6 analog IN, digital OUT pins
  LED - D13 is also the on board LED
*/

#ifndef RIOT_ARDUINO_UNO_H
#define RIOT_ARDUINO_UNO_H

#include "stream_of_byte.h"
#include "utils.h"
#include "Arduino.h"
#include<stdbool.h>
#include "stream_of_byte_map.h"

typedef struct riot_arduino_uno_sinks_t {
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
  stream_of_byte *LED;
  stream_of_byte *A0;
  stream_of_byte *A1;
  stream_of_byte *A2;
  stream_of_byte *A3;
  stream_of_byte *A4;
  stream_of_byte *A5;
} riot_arduino_uno_sinks;

typedef struct riot_arduino_uno_sources_t {
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
  stream_of_byte *LED;
} riot_arduino_uno_sources;

typedef riot_arduino_uno_sinks* (*riot_arduino_uno_main)(riot_arduino_uno_sources* sources);

riot_arduino_uno_sinks* riot_arduino_uno_sinks_create();
riot_arduino_uno_sources* riot_arduino_uno_sources_create();
int riot_arduino_uno_run(riot_arduino_uno_main main);

#endif
