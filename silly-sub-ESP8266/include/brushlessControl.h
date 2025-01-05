#ifndef BRUSHLESS_CONTROL_H
#define BRUSHLESS_CONTROL_H

#include <Servo.h>

#define BRUSHLESS_SIGNAL 0

extern Servo esc;


void setupBrushless();
bool drive(int throttle);

#endif