#ifndef STEPPER_CONTROL_H
#define STEPPER_CONTROL_H

#include <Stepper.h>


// Constants
#define STEPS_PER_REVOLUTION 200 // Steps per revolution for the motor

#define FWD_STEP_PIN 15              // Step pin
#define FWD_DIR_PIN 2               // Direction pin
// Microstepping control pins
#define AFT_STEP_PIN 23
#define AFT_DIR_PIN 22
// Variables
#define stepDelay 700 //how fast we step (big=slow)

// Function declarations
void setupStepper();
void moveFwdStepper(int steps);
void moveAftStepper(int steps);
void libraryStep(int steps);
#endif // STEPPER_CONTROL_H
