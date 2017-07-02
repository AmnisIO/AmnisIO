import { periodic } from '@amnisio/rivulet';
import { Sources, createSinks, LOW, HIGH, run } from '@amnisio/arduino-uno';

// Sample application that uses INPUT_PULLUP like logic.
// The switch is on the D2 pin of the UNO.
// Whenever the D2 pin value is LOW, the on board LED is ON.
// Whenever it is HIGH, the on board LED is OFF.
// To do this, we invert the value of the input pin.
// We check the value of the D2 pin every 20ms.
const application = (arduino: Sources) => {
  const sinks = createSinks();
  sinks.LED$ =
    periodic(20)
      .sample(arduino.D2$)
      .map(value => value == LOW ? HIGH : LOW);
  return sinks;
};

run(application);
