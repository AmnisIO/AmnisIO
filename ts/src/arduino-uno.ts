import { Stream } from 'xstream';

export const HIGH = 255;
export const LOW = 0;

export interface Sinks {
  D0$: Stream<number>;
  D1$: Stream<number>;
  D2$: Stream<number>;
  D3$: Stream<number>;
  D4$: Stream<number>;
  D5$: Stream<number>;
  D6$: Stream<number>;
  D7$: Stream<number>;
  D8$: Stream<number>;
  D9$: Stream<number>;
  D10$: Stream<number>;
  D11$: Stream<number>;
  D12$: Stream<number>;
  D13$: Stream<number>;
  LED$: Stream<number>;
  A0$: Stream<number>;
  A1$: Stream<number>;
  A2$: Stream<number>;
  A3$: Stream<number>;
  A4$: Stream<number>;
  A5$: Stream<number>;
}

export interface Sources {
  D0$: Stream<number>;
  D1$: Stream<number>;
  D2$: Stream<number>;
  D3$: Stream<number>;
  D4$: Stream<number>;
  D5$: Stream<number>;
  D6$: Stream<number>;
  D7$: Stream<number>;
  D8$: Stream<number>;
  D9$: Stream<number>;
  D10$: Stream<number>;
  D11$: Stream<number>;
  D12$: Stream<number>;
  D13$: Stream<number>;
  // The following are disabled because analog inputs are
  // not yet supported by the driver
  // A0$: Stream<number>;
  // A1$: Stream<number>;
  // A2$: Stream<number>;
  // A3$: Stream<number>;
  // A4$: Stream<number>;
  // A5$: Stream<number>;
}

export function run(main:(sources: Sources) => Sinks) {
  
}
