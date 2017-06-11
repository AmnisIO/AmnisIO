import { Stream } from 'xstream';

export type byte = number;
export const HIGH: byte = 255;
export const LOW: byte = 0;
export const createSinks = (): Sinks => ({});

export interface Sinks {
  D0$?: Stream<byte>;
  D1$?: Stream<byte>;
  D2$?: Stream<byte>;
  D3$?: Stream<byte>;
  D4$?: Stream<byte>;
  D5$?: Stream<byte>;
  D6$?: Stream<byte>;
  D7$?: Stream<byte>;
  D8$?: Stream<byte>;
  D9$?: Stream<byte>;
  D10$?: Stream<byte>;
  D11$?: Stream<byte>;
  D12$?: Stream<byte>;
  D13$?: Stream<byte>;
  LED$?: Stream<byte>;
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
  LED$: Stream<number>;
}

export function run(main: (sources: Sources) => Sinks) {

}
