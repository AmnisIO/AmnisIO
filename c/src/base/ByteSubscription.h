#ifndef C_BYTESUBSCRIPTION_H
#define C_BYTESUBSCRIPTION_H

typedef struct ByteSubscription {
  void (*unsubscribe) (struct ByteSubscription *self);
} ByteSubscription;

#endif //C_BYTESUBSCRIPTION_H
