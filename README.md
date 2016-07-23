# RIoT
A reactive way to write IoT - Reactive IoT (RIoT), inspired by [Cycle.js](http://cycle.js.org/)

## The what, the why, and the how
`riot` will enable you to write IoT programs in a reactive way.

Every IoT program, from blinking LEDs to switching, is basically a program that reacts to inputs from the device, and pushes outputs to the device. Why not write it declaratively, instead of writing it imperatively? One of the main inhibitors to this approach is the need to write programs for IoT devices in C. A dynamic language like JavaScript allows you to use FRP in order to write the same programs reactively. Enabling people to write IoT programs in JavaScript, and having it transpiled into a C program that can run on the IoT device (as opposed to having a serial connection) is the goal of this project.

Towards this, we will be building a stream library in C, and we will using an existing stream library in JavaScript called [xstream](https://github.com/staltz/xstream). It is a compact library with limited functions which will enable us to map the functions to our stream library easily.

We hope to enable you to write, in TypeScript, a blinking LEDs program:
```js
// use arduino-uno driver
import { run, Sources, Sinks, HIGH, LOW } from './drivers/arduino-uno';

// toggles a LOW/HIGH value
function toggle(value: number): number {
  return number == HIGH ? LOW : HIGH;
}

// takes Sources and returns Sinks
function main(arduino: Sources): Sinks {
  const in12$ = arduino.D12$;
  const in13$ = arduino.D13$;
  const out12$ = in12$.map(toggle);
  const out13$ = in13$.map(toggle);
  return {
    D12$: out12$,
    D13$: out13$
  };
}

// runs the main function on the arduino-uno
run(main);
```
and be able to run the program in your Arduino/Genuino UNO, for example.

The arduino shown here is an example, we will be building towards every platform that is targetable. We will be using the wonderful [platformio](https://github.com/platformio/platformio) in order to accomplish this.

## Status
### C
###### Stream Library
* Supports only streams of `byte`s (or uint8, 0-255)
* The only possible operator is MAP

###### Drivers
* Arduino UNO driver is working
* Other drivers need to be added

### JavaScript / TypeScript
###### Stream Library
* xstream is already released
* It supports 26 operators

###### Drivers
* Arduino UNO driver is to be added

### Transpiler
* TypeScript Compiler API is to be used
* Work not yet started

## Contributing
With such a lofty goal, we will need all the help we can get. However, at the moment, we are in a ver nascent phase and it would take us some time to set up some guidelines towards contribution, etc. Please feel free to open up issues on this repo till then.
