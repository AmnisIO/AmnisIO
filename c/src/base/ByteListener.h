#ifndef C_BYTELISTENER_H
#define C_BYTELISTENER_H

#include "Byte.h"

typedef struct ByteListener {
  int _id;
  void (*next) (void *self, Byte v);
  void (*error) (void *self, int e);
  void (*complete) (void *self);
} ByteListener;

#endif //C_BYTELISTENER_H
