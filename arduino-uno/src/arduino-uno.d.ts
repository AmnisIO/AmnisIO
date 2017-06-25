declare module '@amnisio/arduino-uno' {
  import { ByteStream, Byte } from 'rivulet';

  export const HIGH: Byte;
  export const LOW: Byte;
  export const createSinks: () => Sinks;

  export interface Sinks {
    D0$?: ByteStream;
    D1$?: ByteStream;
    D2$?: ByteStream;
    D3$?: ByteStream;
    D4$?: ByteStream;
    D5$?: ByteStream;
    D6$?: ByteStream;
    D7$?: ByteStream;
    D8$?: ByteStream;
    D9$?: ByteStream;
    D10$?: ByteStream;
    D11$?: ByteStream;
    D12$?: ByteStream;
    D13$?: ByteStream;
    LED$?: ByteStream;
  }

  export interface Sources {
    D0$: ByteStream;
    D1$: ByteStream;
    D2$: ByteStream;
    D3$: ByteStream;
    D4$: ByteStream;
    D5$: ByteStream;
    D6$: ByteStream;
    D7$: ByteStream;
    D8$: ByteStream;
    D9$: ByteStream;
    D10$: ByteStream;
    D11$: ByteStream;
    D12$: ByteStream;
    D13$: ByteStream;
    LED$: ByteStream;
  }

  export const run: (main: (sources: Sources) => Sinks) => void;
}
