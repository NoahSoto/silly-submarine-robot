#ifndef STEPPER_CONTROL_H
#define STEPPER_CONTROL_H

#include <Stepper.h>

// Function declarations
void setupStepper();
void moveStepper(int steps);
void libraryStep(int steps);
#endif // STEPPER_CONTROL_H
