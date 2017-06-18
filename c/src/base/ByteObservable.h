#ifndef C_BYTEOBSERVABLE_H
#define C_BYTEOBSERVABLE_H

typedef enum ByteObservableType {
  OBSERVABLE_TYPE_UNKNOWN,
  OBSERVABLE_TYPE_PRODUCER,
  OBSERVABLE_TYPE_LISTENER,
  OBSERVABLE_TYPE_LISTENER_INTERNAL,
  OBSERVABLE_TYPE_STREAM,
  OBSERVABLE_TYPE_OPERATOR
} ByteObservableType;

typedef struct ByteObservable {
  enum ByteObservableType type;
} ByteObservable;

#endif //C_BYTEOBSERVABLE_H
