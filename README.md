# AmnisIO
Write reactive programs for various platforms using [TypeScript](https://www.typescriptlang.org/).

Inspired by [Cycle.js](http://cycle.js.org/) and powered by [PlatformIO](http://platformio.org/)

## The what, the why, and the how
`AmnisIO` will enable you to write IoT programs in a reactive way.

Every IoT program, from blinking LEDs to switching, is basically a program that reacts to inputs from the device, and pushes outputs to the device. Why not write it declaratively, instead of writing it imperatively? One of the main inhibitors to this approach is the need to write programs for IoT devices in C. A dynamic language like JavaScript allows you to use FRP in order to write the same programs reactively. Enabling people to write IoT programs in JavaScript, and having it transpiled into a C program that can run on the IoT device (as opposed to having a serial connection) is the goal of this project.

Towards this, we have built a small stream library in C called [rivulet](https://github.com/AmnisIO/rivulet), and we expose it via TypeScript. It is a compact library with limited but useful functions which will enable us to get started with reactive programming quickly. Initially, we will be limited to the use of only this library, but we hope to expand our horizons in future.

We hope to enable you to write, in TypeScript, a blinking LEDs program:
```ts
import { periodic } from 'rivulet';
import { Sources, Sinks, HIGH, LOW, run } from '@amnisio/arduino-uno';

// Read the LED pin value every 500 ms and toggle it
const blink = (arduino: Sources): Sinks => ({
  LED$:
    periodic(500)
      .sample(arduino.LED$)
      .map(x => x == LOW ? HIGH : LOW)
});

run(blink);

```
and be able to run the program in your Arduino/Genuino UNO, for example. We use a transpiler called [typewriter](https://github.com/AmnisIO/typewriter) and convert this into C code that is compatible with the embedded platform that you choose to work on, and the platform runs the code natively.

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

### Transpiler (typewriter)
* TypeScript Compiler API is used.
* We are able to transpile some basic structures involving `Byte`s into C.
* We are able to run the transpiled code on the Arduino Uno.
* Type inference has to be worked upon.
* Anonymous functions should be helpful.

### AmnisIO
* A node-based cross-platform CLI is in progress.

## Getting Started
We are working on getting a CLI for bootstrapping. For now, we can work with the Arduino Uno.

Please install platformio. Instructions [here](http://docs.platformio.org/en/latest/installation.html).
The platformio executable should be added to the PATH.

```bash
mkdir amnisio_test
cd amnisio_test
npm init
npm install amnisio --save-dev
```

Add a configuration file
```bash
touch .amnisio.config.json
```
with the following contents
```json
{
    "source": "app.ts",
    "output": "app.c",
    "board": "uno"
}
```

Add a source file
```bash
touch app.ts
```
with the following contents
```ts
import { ByteStream, Byte, periodic } from 'rivulet';
import { Sources, Sinks, HIGH, LOW, run, createSinks } from '@amnisio/arduino-uno';

function toggle(value: Byte): Byte {
  return value == HIGH ? LOW : HIGH;
}

function blink(arduino: Sources): Sinks {
  const sinks: Sinks = createSinks();
  const sample$: ByteStream = periodic(500);
  const sampledLED$: ByteStream = sample$.sample(arduino.LED$);
  sinks.LED$ = sampledLED$.map(toggle);
  return sinks;
}

run(blink);
```
*__NOTE:__ For now the TypeScript code may not compile, we are still working on the type definitions. Also, the TypeScript code shown above may look type-verbose. We are working on a type inference solution that should improve our present situation.*

Add the following scripts to your `package.json`:
```json
{
  "initialize": "amnisio init",
  "build": "amnisio build",
  "deploy": "amnisio deploy"
}
```

Now, time to initialize the project.
```bash
npm run initialize
```
The arduino uno board configuration (which is the one available at the moment, and entered in the config file) is initialized. The necessary files are downloaded, so please be patient while the initialization happens. Once the initialization is complete, connect your arduino to the computer and get ready (Windows users make sure the required USB drivers are installed).
```bash
npm run deploy
```

You have your first AmnisIO project running on your Arduino UNO!

We will expand to more platforms and examples soon.

## Contributing
With such a lofty goal, we will need all the help we can get. However, at the moment, we are in a very nascent stage and it would take us some time to set up some guidelines towards contribution, etc. Please feel free to open up issues on this repo till then.
