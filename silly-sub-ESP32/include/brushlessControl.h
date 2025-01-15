#ifndef BRUSHLESS_CONTROL_H
#define BRUSHLESS_CONTROL_H

#include <ESP32Servo.h>

#define BRUSHLESS_SIGNAL_PORT 0
#define BRUSHLESS_SIGNAL_STARBOARD 15

extern Servo escPort;
extern Servo escStarboard;

void setupBrushless();
bool drive(int throttle);
void dualMotorDriveSingleJoystick(int throttleX,int throttleY);
bool drivePort(int throttle);
bool driveStarboard(int throttle);


#endif