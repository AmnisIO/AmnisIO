# riot
A reactive way to write IoT - Reactive IoT (RIOT)

## The what, the why, and the how
`riot` will enable you to write IoT programs in a reactive way.

Every IoT program, from blinking LEDs to switching, is basically a program that reacts to inputs from the device, and pushes outputs to the device. Why not write it declaratively, instead of writing it imperatively? One of the main inhibitors to this approach is the need to write programs for IoT devices in C. A dynamic language like JavaScript allows you to use FRP in order to write the same programs reactively. Enabling people to write IoT programs in JavaScript, and having it transpiled into a C program that can run on the IoT device (as opposed to having a serial connection) is the goal of this project.

Towards this, we will be building a stream library in C, and we will using an existing stream library in JavaScript called [xstream](https://github.com/staltz/xstream). It is a compact library with limited functions which will enable us to map the functions to our stream library easily.

We hope to enable you to write, in TypeScript, a blinking LEDs program:
```js
import { ISources, ISinks } from './definitions';
import { HIGH, LOW } from './drivers/arduino';

function main(sources: ISources): ISinks {
  const in12$ = sources.arduino.pin12$;
  const in13$ = sources.arduino.pin13$;
  const out12$ = in12$
    .map(value =>
      value == HIGH ? LOW : HIGH);
  const out13$ =
    in13$
      .map(value =>
        value == HIGH ? LOW : HIGH);
  return {
    arduino: {
      pin12$: out12$,
      pin13$: out13$
    }
  }
}

export default main;
```
and be able to run the program in your Arduino/Genuino UNO, for example.

The arduino shown here is an example, we will be building towards every platform that is targetable.

## Contributing
With such a lofty goal, we will need all the help we can get. However, at the moment, we are in a ver nascent phase and it would take us some time to set up some guidelines towards contribution, etc. Please feel free to open up issues on this repo till then.
