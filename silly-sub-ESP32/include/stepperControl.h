#ifndef STEPPER_CONTROL_H
#define STEPPER_CONTROL_H

#include <Stepper.h>


// Constants
#define STEPS_PER_REVOLUTION 200 // Steps per revolution for the motor

#define FWD_DIR_PIN 18               // Direction pin
#define FWD_STEP_PIN 19              // Step pin
// Microstepping control pins
#define AFT_DIR_PIN 22
#define AFT_STEP_PIN 23

// Variables
#define stepDelay 400 //how fast we step (big=slow)

// Function declarations
void setupStepper();
void moveFwdStepper(int steps);
void moveAftStepper(int steps);
void libraryStep(int steps);
void sink();
void rise();
#endif // STEPPER_CONTROL_H
