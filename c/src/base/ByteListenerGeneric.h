#ifndef C_BYTELISTENERGENERIC_H
#define C_BYTELISTENERGENERIC_H

#include "Byte.h"

typedef void (*byte_listener_next) (void *self, Byte value);
typedef void (*byte_listener_error) (void *self, int error);
typedef void (*byte_listener_complete) (void *self);

#endif //C_BYTELISTENERGENERIC_H
