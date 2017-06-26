import { ByteStream, Byte, periodic } from 'rivulet';
import { Sources, Sinks, HIGH, LOW, run, createSinks } from '@amnisio/arduino-uno';

function toggle(value: Byte): Byte {
  return value == HIGH ? LOW : HIGH;
}

function blink(arduino: Sources): Sinks {
  const sinks: Sinks = createSinks();
  const sample$: ByteStream = periodic(1000);
  const sampledLED$: ByteStream = sample$.sample(arduino.LED$);
  sinks.LED$ = sampledLED$.map(toggle);
  return sinks;
}

run(blink);
