#include "riot_arduino_uno.h"
#include "utils.h"
#include "Arduino.h"
#include<stdbool.h>

riot_arduino_uno_sinks* riot_arduino_uno_sinks_create() {
  riot_arduino_uno_sinks *sinks = xmalloc(sizeof(riot_arduino_uno_sinks));
  return sinks;
}

riot_arduino_uno_sources* riot_arduino_uno_sources_create() {
  riot_arduino_uno_sources *sources = xmalloc(sizeof(riot_arduino_uno_sources));
  return sources;
};

/**
  On the Arduino board, digital pins are also used
  for the analog output (software PWM).  Analog input
  pins are a separate set. We use these pin numbers when
  referring to input/output pins. We can later try to make
  use of arduino.h here

  ATMEL ATMEGA8 & 168 / ARDUINO

                    +-\/-+
              PC6  1|    |28  PC5 (AI 5)
        (D 0) PD0  2|    |27  PC4 (AI 4)
        (D 1) PD1  3|    |26  PC3 (AI 3)
        (D 2) PD2  4|    |25  PC2 (AI 2)
    PWM+ (D 3) PD3 5|    |24  PC1 (AI 1)
        (D 4) PD4  6|    |23  PC0 (AI 0)
              VCC  7|    |22  GND
              GND  8|    |21  AREF
              PB6  9|    |20  AVCC
              PB7 10|    |19  PB5 (D 13)
  PWM+ (D 5) PD5  11|    |18  PB4 (D 12)
  PWM+ (D 6) PD6  12|    |17  PB3 (D 11) PWM
        (D 7) PD7 13|    |16  PB2 (D 10) PWM
        (D 8) PB0 14|    |15  PB1 (D 9) PWM
                    +----+

  (PWM+ indicates the additional PWM pins on the ATmega168.)
*/

/**
  We map the output streams in the sinks struct to the board's
  outputs here. For simplicity, we write all outputs as bytes for
  now, later we can use bool for digital and 0-255 for analog/pwm.
*/
void riot_arduino_uno_map_sinks_to_write_outputs(riot_arduino_uno_sinks *sinks) {
  // TODO: Map sinks to write outputs
}

/**
  We read the pins and manually push a next value to the individual
  streams in the sources struct.
*/
void riot_arduino_uno_read_inputs(riot_arduino_uno_sources *sources) {
  // TODO: Read all inputs and map to sources
}

/**
  Returns true if the sinks is empty, i.e., all the streams in the
  sinks struct point to null. 
*/
bool riot_arduino_uno_is_sinks_empty(riot_arduino_uno_sinks *sinks) {
  // TODO: Return true if no streams are present in sink, ie no output is required.
}

int riot_arduino_uno_run(riot_arduino_uno_main main) {
  if(main == NULL) {
    return -1;
  }
  riot_arduino_uno_sources *sources = riot_arduino_uno_sources_create();
  if(sources == NULL) {
    return -2;
  }
  riot_arduino_uno_sinks *sinks = main(sources);
  if(sinks == NULL) {
    return -3;
  }
  riot_arduino_uno_map_sinks_to_write_outputs(sinks);
  while (true) {
    riot_arduino_uno_read_inputs(sources);
    if(riot_arduino_uno_is_sinks_empty(sinks))
      break;
  }
  return 0;
}
