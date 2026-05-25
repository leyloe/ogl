#ifndef FRAME_TIME_H
#define FRAME_TIME_H

typedef struct {
    double last;
    double now;
    float dt;
} frame_time;

frame_time frame_time_init();
void frame_time_get(frame_time *f);

#endif
