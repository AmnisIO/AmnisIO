#include "ByteListener.h"
#include "ByteStream.h"

#ifndef C_BYTESTREAMSUBSCRIPTION_H
#define C_BYTESTREAMSUBSCRIPTION_H

typedef struct ByteStreamSubscription {
  void (*unsubscribe)();
} ByteStreamSubscription;

ByteStreamSubscription *byte_stream_subscription_create(ByteStream *stream, ByteListener *listener);

#endif //C_BYTESTREAMSUBSCRIPTION_H
