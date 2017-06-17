#ifndef C_BYTEOBSERVABLE_H
#define C_BYTEOBSERVABLE_H

typedef enum ByteObservableType {
  UNKNOWN,
  PRODUCER,
  PRODUCER_INTERNAL,
  LISTENER,
  LISTENER_INTERNAL,
  STREAM,
  OPERATOR
} ByteObservableType;

typedef struct ByteObservable {
  enum ByteObservableType type;
} ByteObservable;

#endif //C_BYTEOBSERVABLE_H
