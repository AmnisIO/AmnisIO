#include <ByteListernerManager.h>
#include "ArduinoUnoInputPinByteProducer.h"

static void _from_array_start (ByteProducer *self, ByteListenerInternal *listener) {
  ArduinoUnoInputPinByteProducer *producer = (ArduinoUnoInputPinByteProducer *) self;

  byte_listener_internal_next_get (listener) (listener, );
  byte_listener_internal_complete_get (listener) (listener);
}

static void _from_array_stop (ByteProducer *self) {

}

ArduinoUnoInputPinByteProducer *arduino_uno_input_pin_byte_pruoducer_create(int pin) {
  ArduinoUnoInputPinByteProducer *producer = xmalloc (sizeof(ArduinoUnoInputPinByteProducer));
  byte_producer_initialize (producer, )
  return producer;
}
