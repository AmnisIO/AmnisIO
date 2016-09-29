# RIoT
A reactive way to write IoT - Reactive IoT (RIoT), inspired by [Cycle.js](http://cycle.js.org/)

## The what, the why, and the how
`riot` will enable you to write IoT programs in a reactive way.

Every IoT program, from blinking LEDs to switching, is basically a program that reacts to inputs from the device, and pushes outputs to the device. Why not write it declaratively, instead of writing it imperatively? One of the main inhibitors to this approach is the need to write programs for IoT devices in C. A dynamic language like JavaScript allows you to use FRP in order to write the same programs reactively. Enabling people to write IoT programs in JavaScript, and having it transpiled into a C program that can run on the IoT device (as opposed to having a serial connection) is the goal of this project.

Towards this, we will be building a stream library in C, and we will using an existing stream library in JavaScript called [xstream](https://github.com/staltz/xstream). It is a compact library with limited functions which will enable us to map the functions to our stream library easily.

We hope to enable you to write, in TypeScript, a blinking LEDs program:
```js
// use riot
import run from '@riot/run';
// use arduino-uno
import { Sources, Sinks, HIGH, LOW } from '@riot/arduino-uno';

// toggles a LOW/HIGH value
function toggle(value: number): number {
  return number == HIGH ? LOW : HIGH;
}

// Your IoT program takes Sources and returns Sinks
// Sources are streams of inputs from the board
// Sinks are streams of outputs to the board
function main(arduino: Sources): Sinks {
  // $ is read as 'stream', so the following line declares 'in-stream'
  const in12$ = arduino.D12$; // The stream of inputs from the D12 pin
  const in13$ = arduino.D13$; // The stream of inputs from the D13 pin
  const out12$ = in12$.map(toggle);
  const out13$ = in13$.map(toggle);
  // Push outputs to the D12 and D13 pins as a stream
  return {
    D12$: out12$,
    D13$: out13$
  };
}

// runs the main function on the arduino-uno
run(main);
```
and be able to run the program in your Arduino/Genuino UNO, for example. We will transpile this into C code that is compatible with the board that you choose to write your IoT code on, and the board will run the code natively.

The *Arduino UNO* used here is an example, we will be building towards every platform that is targetable. We will be using the wonderful [platformio](https://github.com/platformio/platformio) in order to accomplish this.

## Status
### C
###### Stream Library
* Supports only streams of `byte`s (or uint8, 0-255)
* The only possible operator is MAP

###### Drivers
* Arduino UNO driver is working, with digital inputs and outputs (analog inputs to be added shortly)
* Other drivers need to be added

### JavaScript / TypeScript
###### Stream Library
* xstream is already released
* It supports 26 operators

###### Drivers
* Arduino UNO driver has been written, with digital inputs and outputs (analog inputs to be added shortly)
* Other drivers need to be added

### Transpiler
* TypeScript Compiler API is to be used
* Work not yet started

## Contributing
With such a lofty goal, we will need all the help we can get. However, at the moment, we are in a ver nascent phase and it would take us some time to set up some guidelines towards contribution, etc. Please feel free to open up issues on this repo till then.
