#ifndef C_BYTELISTERNERMANAGER_H
#define C_BYTELISTERNERMANAGER_H

#include "ByteListenerInternal.h"

byte_listener_internal_next byte_listener_internal_next_get(ByteListenerInternal *listener);
byte_listener_internal_error byte_listener_internal_error_get(ByteListenerInternal *listener);
byte_listener_internal_complete byte_listener_internal_complete_get(ByteListenerInternal *listener);

#endif //C_BYTELISTERNERMANAGER_H