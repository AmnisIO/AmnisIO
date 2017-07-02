import { periodic } from '@amnisio/rivulet';
import { Sources, HIGH, LOW, run, createSinks } from '@amnisio/arduino-uno';

// Sample application that will blink the on-board LED of the arduino uno every 500 ms.
const blink = (arduino: Sources) => {
  const sinks = createSinks();
  sinks.LED$ =
    periodic(500)
      .sample(arduino.LED$)
      .map(led => led == LOW ? HIGH : LOW);
  return sinks;
};

run(blink);
