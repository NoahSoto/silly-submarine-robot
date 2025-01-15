#ifndef BRUSHLESS_CONTROL_H
#define BRUSHLESS_CONTROL_H

#include <ESP32Servo.h>
#include "esp32-hal-ledc.h"

#define BRUSHLESS_SIGNAL_PORT 21
#define BRUSHLESS_SIGNAL_STARBOARD 19

extern Servo escPort;
extern Servo escStarboard;

 #define TIMER_WIDTH 16

void setupBrushless();
void analogDrive(int speed);
bool drive(int throttle);
void dualMotorDriveSingleJoystick(int throttleX,int throttleY);
bool drivePort(int throttle);
bool driveStarboard(int throttle);


#endif