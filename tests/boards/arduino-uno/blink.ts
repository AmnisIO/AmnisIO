import { Sources, Sinks, HIGH, LOW, run, byte, createSinks } from '../../../src/boards/arduino-uno';

function toggle(value: byte): byte {
  return value == HIGH ? LOW : HIGH;
}

function blink(arduino: Sources): Sinks {
  const sinks: Sinks = createSinks();
  sinks.LED$ = arduino.LED$.map(toggle);
  return sinks;
}

run(blink);
