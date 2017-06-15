#ifndef C_BYTELISTENER_H
#define C_BYTELISTENER_H

#include "VariableLengthArray.h"
#include "utils.h"

typedef uint8_t Byte;

typedef struct ByteListener {
  void (*next) (struct ByteListener *self, Byte v);
  void (*error) (struct ByteListener *self, Byte e);
  void (*complete) (struct ByteListener *self);
} ByteListener;

#endif //C_BYTELISTENER_H
