#ifndef C_ARDUINOUNOINPUTPINBYTEPRODUCER_H
#define C_ARDUINOUNOINPUTPINBYTEPRODUCER_H

#include <ByteProducer.h>

typedef struct ArduinoUnoInputPinByteProducer {
  ByteObservableType type;
  byte_producer_internal_start _start;
  byte_producer_internal_stop _stop;
  byte_producer_start start;
  byte_producer_stop stop;
  int pin;
} ArduinoUnoInputPinByteProducer;

ArduinoUnoInputPinByteProducer *arduino_uno_input_pin_byte_pruoducer_create(int pin);

#endif //C_ARDUINOUNOINPUTPINBYTEPRODUCER_H
