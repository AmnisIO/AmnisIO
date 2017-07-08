import { Int, periodic } from '@amnisio/rivulet';
import { Sources, HIGH, LOW, run, createSinks } from '@amnisio/arduino-uno';

// Initialize brightness and change
let brightness = 0;
let change = 5;

const getCurrentBrightness = (event: Int) => {
  // Make the change to brightness
  brightness = brightness + change;
  // If the cycle has ended, invert the change
  if (brightness <= LOW || brightness >= HIGH) change = -change;
  // Return the current brightness
  return brightness;
}

// Sample application that will fade an LED attached to the D10 pin using PWM.
// Requires an LED to be connected at pin D10.
// Every 30ms, the brightness of the LED attached to D10 is updated.
const application = (arduino: Sources) => {
  const sinks = createSinks();
  sinks.D10$ = periodic(30).map(getCurrentBrightness);
  return sinks;
};

run(application);
