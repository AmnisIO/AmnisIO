import { periodic } from '@amnisio/rivulet';
import { Sources, HIGH, LOW, run, createSinks } from '@amnisio/arduino-uno';

// Sample application that will fade an LED attached to the D10 pin using PWM.
// Requires an LED to be connected at pin D10.
// Every 30ms, the brightness of the LED attached to D10 is updated.
const application = (arduino: Sources) => {
  const sinks = createSinks();
  // We do some maths in order to get a stream of brightnesses that allows fading
  sinks.D10$ =
    // Create a stream that emits an event every 30 ms
    periodic(30)
      // fold it onto a stream that repeats 0 to 101 forever
      // 0-1-2-3-...-100-101-0-1-2-3-4-...->
      .fold((brightness, event) => brightness == 101 ? 0 : ++brightness, 0)
      // map it to a triangular stream that rises and falls, peaking at 51, forever
      // 0-1-2-3-...-50-51-50-...-3-2-1-0-1-2-3-...->
      .map(brightness => {
        const x = brightness % 51;
        return brightness > x ? 51 - x : x;
      })
      // map it to a stream that multiplies the value by 5, to get increments of 5, peaking at 255
      // 0-5-10-15-...-250-255-250-...-15-10-5-0-5-10-15-...->
      .map(brightness => 5 * brightness);
  return sinks;
};

run(application);
