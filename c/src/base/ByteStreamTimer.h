#ifndef C_BYTESTREAMTIMER_H
#define C_BYTESTREAMTIMER_H

typedef void *(*byte_stream_timer_task)(void *argument);
typedef int ByteStreamTimerTaskIdentifier;

ByteStreamTimerTaskIdentifier byte_stream_timer_set_timeout(byte_stream_timer_task task, void *argument, int milliseconds);
void byte_stream_timer_clear_timeout(ByteStreamTimerTaskIdentifier task_id);
ByteStreamTimerTaskIdentifier byte_stream_timer_set_interval(byte_stream_timer_task task, void *argument, int milliseconds);

#endif //C_BYTESTREAMTIMER_H
