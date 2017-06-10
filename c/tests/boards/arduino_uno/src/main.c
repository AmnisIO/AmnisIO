#ifndef UNIT_TEST

#include "riot_arduino_uno.h"

byte toggle(byte value) {
  return (byte) value == HIGH ? LOW : HIGH;
}

riot_arduino_uno_sinks* blink(riot_arduino_uno_sources* sources) {
  riot_arduino_uno_sinks *sinks = riot_arduino_uno_sinks_create();
  sinks->LED = stream_of_byte_map(sources->LED, toggle);
  return sinks;
}

void setup() {
  riot_arduino_uno_run(blink);
}

void loop() {

}

#endif
