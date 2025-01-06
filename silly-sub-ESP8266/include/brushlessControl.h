#ifndef BRUSHLESS_CONTROL_H
#define BRUSHLESS_CONTROL_H

#include <Servo.h>

#define BRUSHLESS_SIGNAL_PORT 0
#define BRUSHLESS_SIGNAL_STARBOARD 15

extern Servo escPort;
extern Servo escpStarboard;


void setupBrushless();
bool drive(int throttle);

#endif