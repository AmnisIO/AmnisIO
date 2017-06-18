#include <printf.h>
#include "ByteStreamTimer.h"

ByteStreamTimerTaskIdentifier byte_stream_timer_set_timeout(byte_stream_timer_task task, void *argument, int milliseconds) {
  printf("task was run");
  return 0;
}

void byte_stream_timer_clear_timeout(ByteStreamTimerTaskIdentifier task_id) {
  printf("task was cleared");
}