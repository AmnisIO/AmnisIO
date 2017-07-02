import { periodic } from '@amnisio/rivulet';
import { Sources, createSinks, run } from '@amnisio/arduino-uno';

// Sample application that has the on board LED react to a user-provided switch.
// The switch is on the D2 pin of the UNO.
// Whenever the D2 pin value is HIGH, the on board LED is ON.
// Whenever it is not, the on board LED is OFF.
// We check the value of the D2 pin every 20ms.
const application = (arduino: Sources) => {
  const sinks = createSinks();
  sinks.LED$ = periodic(20).sample(arduino.D2$);
  return sinks;
};

run(application);
