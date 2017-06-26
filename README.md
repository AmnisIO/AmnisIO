# AmnisIO
Write reactive programs for various platforms using [TypeScript](https://www.typescriptlang.org/).

Inspired by [Cycle.js](http://cycle.js.org/) and powered by [PlatformIO](http://platformio.org/)

## The what, the why, and the how
`AmnisIO` will enable you to write IoT programs in a reactive way.

Every IoT program, from blinking LEDs to switching, is basically a program that reacts to inputs from the device, and pushes outputs to the device. Why not write it declaratively, instead of writing it imperatively? One of the main inhibitors to this approach is the need to write programs for IoT devices in C. A dynamic language like JavaScript allows you to use FRP in order to write the same programs reactively. Enabling people to write IoT programs in JavaScript, and having it transpiled into a C program that can run on the IoT device (as opposed to having a serial connection) is the goal of this project.

Towards this, we have built a small stream library in C called [rivulet](https://github.com/AmnisIO/rivulet), and we will be exposing it via TypeScript. It is a compact library with limited but useful functions which will enable us to get started with reactive programming quickly. Initially, we will be limited to the use of only this library, but we hope to expand our horizons in future.

We hope to enable you to write, in TypeScript, a blinking LEDs program:
```js
// Import from our stream library
import { ByteStream, Byte, periodic } from 'rivulet';
// Use the arduino-uno configuration of AmnisIO
import { Sources, Sinks, HIGH, LOW, run, createSinks } from '@amnisio/arduino-uno';

// Toggle a digital value
function toggle(value: Byte): Byte {
  return value == HIGH ? LOW : HIGH;
}
// Our embedded platform runs a pure function that
// takes Sources and returns Sinks.
// Sources are streams of inputs from the embedded platform.
// Sinks are streams of outputs to the embedded platform.
// Notice how we are defining reactions and not running any code
// at this time.
function blink(arduino: Sources): Sinks {
  // We need to create sinks, we will not be needing to do this in the future.
  // Also note the use of the library-provided method, and the specification of type.
  // We will be compiling to C, so we need type information.
  // In the future, we should be creating an intelligent type inference engine to
  // avoid 'typing' (pun intended)
  const sinks: Sinks = createSinks();
  // We read $ as a 'stream'. So here we create a 'sample-stream'
  // which enables sampling a stream.
  // Specifically, here we create a stream that emits events periodically
  // at 1000ms (1s) intervals.
  const sample$: ByteStream = periodic(1000);
  // We create a sampled stream of LED pin values on the Arduino Uno.
  // The LED pin is the digital 13 pin on the Uno. Notice we do not specify
  // how to read values, that is taken care of by the framework.
  // We are just dealing with streams of inputs from the pin here.
  // We use the 'sample-stream' to sample our inputs, and create a sampled
  // LED stream.
  const sampledLED$: ByteStream = sample$.sample(arduino.LED$);
  // We specify that our sinks' (output's) LED stream should be
  // another stream, which the result of applying a map operator on
  // the sampled LED stream. This operator returns a new stream
  // which will emit the toggled value of the input stream.
  // In effect, if the sampledLED$ emits HIGH, this resulting stream will
  // emit LOW, and vice versa.
  sinks.LED$ = sampledLED$.map(toggle);
  // Now that we have declared what will happen, we return the sinks.
  // Remember that this part of the code does nothing other than specify
  // what should happen. No execution occurs on the embedded platform yet.
  return sinks;
}

// We run the blink application that we just defined above, on the embedded
// platform. In effect, we read the LED pin's value at 1s intervals, and we write
// to the same pin the toggled value. This causes a blink of 2s duration, where the
// LED stays ON for 1s and then OFF for 1s.
// This is when the application is actually run.
run(blink);

// Did you notice that we never used any synchronous code? Reactive applications
// are naturally asynchronous, so we didn't have to worry about writing a synchronous
// delay in the code. Streaming of the inputs/outputs is taken care of by the framework,
// so you can remain blissfully ignorant of what goes on inside the platform, while writing
// intuitive, functional reactive code. Happy coding!

```
and be able to run the program in your Arduino/Genuino UNO, for example. We transpile this into C code that is compatible with the embedded platform that you choose to work on, and the platform runs the code natively.

The *Arduino UNO* used here is an example, we will be building towards every platform that is targetable. We will be using the wonderful [PlatformIO](https://github.com/platformio/platformio) in order to accomplish this.

## Status
### C
###### Stream Library (rivulet)
* Supports only streams of `Byte`s (or uint8, 0-255).
* We have operators like map, mapTo, filter, delay, sample, take, drop, and last.
* We are building more useful operators as and when possible.

###### Drivers (Platform-specific frameworks)
* Arduino UNO driver is working, with digital inputs and outputs (analog inputs to be added shortly).
* Drivers targeting other platforms need to be added.

### TypeScript
###### Stream Library
* Type definitions for [rivulet](https://github.com/AmnisIO/rivulet) have been crafted.
* It is fully usable to write TypeScript code targeting any platform.
* It is testable by means of Arduino Uno framework for now.

###### Drivers (Platform-specific frameworks)
* Arduino UNO driver has been written, with digital inputs and outputs (analog inputs to be added shortly).
* We are able to get a basic blink application working.
* Drivers targeting other platforms need to be added.

### Transpiler
* TypeScript Compiler API is used.
* We are able to transpile some basic structures involving `Byte`s into C.
* We are able to run the transpiled code on the Arduino Uno.
* Type inference has to be worked upon.
* Anonymous functions should be helpful.

### AmnisIO
* The current repository gives us a start of testing with Arduino Uno.
* If platformio is installed, the npm scripts will get us started with testing blink and similar programs on the Arduino Uno.
* Some refinement is required in order to flesh out a good CLI to work with.
* Work towards this is underway, watch this space.
* Releases yet to be made, as node package/cli.

## Contributing
With such a lofty goal, we will need all the help we can get. However, at the moment, we are in a very nascent stage and it would take us some time to set up some guidelines towards contribution, etc. Please feel free to open up issues on this repo till then.
