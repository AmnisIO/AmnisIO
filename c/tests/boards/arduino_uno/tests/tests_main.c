#ifdef UNIT_TEST

#include <Arduino.h>
#include <unity.h>
#include "riot_arduino_uno.h"

void test_led_builtin_pin_number(void) {
    TEST_ASSERT_EQUAL(LED_BUILTIN, 13);
}

byte toggle(byte value) {
  return (byte) value == HIGH ? LOW : HIGH;
}

riot_arduino_uno_sinks* blink(riot_arduino_uno_sources* sources) {
  riot_arduino_uno_sinks *sinks = riot_arduino_uno_sinks_create();
  TEST_ASSERT_NOT_NULL_MESSAGE(sinks, "sinks was null");
  TEST_ASSERT_NULL_MESSAGE(sinks->D0, "sinks->D0 was not null");
  sinks->LED = stream_of_byte_map(sources->LED, toggle);
  TEST_ASSERT_NOT_NULL_MESSAGE(sinks->LED, "sinks->LED was null");
  return sinks;
}

void test_run_blink(void){
  int result = riot_arduino_uno_run(blink);
  TEST_ASSERT_NOT_EQUAL(result, -1);
  TEST_ASSERT_NOT_EQUAL(result, -2);
  TEST_ASSERT_NOT_EQUAL(result, -3);
}

void setup() {
    delay(2000);
    UNITY_BEGIN();
    RUN_TEST(test_led_builtin_pin_number);
    RUN_TEST(test_run_blink);
    UNITY_END();
}

void loop() {
}

#endif
