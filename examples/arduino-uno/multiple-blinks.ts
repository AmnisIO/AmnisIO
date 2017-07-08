import { Int, periodic } from '@amnisio/rivulet';
import { Sources, HIGH, LOW, run, createSinks } from '@amnisio/arduino-uno';

const invert = (value: Int) => value == LOW ? HIGH : LOW;

// Sample application that will blink multiple LEDs attached to the arduino UNO at various cycles.
// Requires an LED to be connected at pin D2.
// Requires another LED to be connected at pin D3.
// The on-board LED is used as a third LED.
// The led at pin D2 blinks every 100ms.
// The led at pin D3 blinks every 250ms.
// The on board LED blinks every 500ms.
// That's literally how easy it is to describe asynchronous actions with FRP.
const application = (arduino: Sources) => {
  const sinks = createSinks();
  sinks.D2$ = periodic(100).sample(arduino.D2$).map(invert);
  sinks.D3$ = periodic(250).sample(arduino.D3$).map(invert);
  sinks.LED$ = periodic(500).sample(arduino.LED$).map(invert);
  return sinks;
};

run(application);
