#ifndef C_BYTELISTENER_H
#define C_BYTELISTENER_H

#include "Byte.h"

typedef struct ByteListener {
  int _id;
  void (*next) (struct ByteListener *self, Byte v);
  void (*error) (struct ByteListener *self, int e);
  void (*complete) (struct ByteListener *self);
} ByteListener;

#endif //C_BYTELISTENER_H
