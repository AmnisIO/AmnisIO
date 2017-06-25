declare module 'rivulet' {
  export type Byte = number;

  interface Rivulet<T> {
    map: (mapper: (value: T) => T) => Rivulet<T>;
    mapTo: (value: T) => Rivulet<T>;
    filter: (predicate: (value: T) => boolean) => Rivulet<T>;
    take: (count: number) => Rivulet<T>;
    drop: (count: number) => Rivulet<T>;
    last: () => Rivulet<T>;
    sample: (input$: Rivulet<T>) => Rivulet<T>;
    delay: (delay: number) => Rivulet<T>;
  }
  
  export interface ByteStream extends Rivulet<Byte> {

  }

  export const periodic: (period: number) => ByteStream;
}
