#include <Arduino.h>
#include "stepperControl.h"

// Constants
#define STEPS_PER_REVOLUTION 200 // Steps per revolution for the motor
#define STEP_PIN 5              // Step pin
#define DIR_PIN 4               // Direction pin
// Microstepping control pins
#define MS1_PIN 2
#define MS2_PIN 16
// Variables
int stepLimit = 1000;
bool movingForward = true;

// Create a Stepper instance
Stepper stepper(STEPS_PER_REVOLUTION, STEP_PIN, DIR_PIN);

void setupStepper() {
    // Set the speed of the stepper motor (in RPM)
    stepper.setSpeed(120); // Set desired speed in RPM
}

void moveStepper(int steps) {

    int stepCount = abs(steps);  // Get the absolute value of steps to use in the loop
    if(steps == 0){
        return;
    }else if (steps > 0) {
        digitalWrite(DIR_PIN, HIGH);  // Set direction to HIGH for forward motion
    }else{
        digitalWrite(DIR_PIN, LOW);   // Set direction to LOW for reverse motion
    }


    unsigned long lastStepTime = 0;  // Variable to track time for each step
    int stepDelay = 700;  // Microseconds delay between steps, can be adjusted


    // Iterate over the absolute value of steps
    for (int x = 0; x < stepCount; x++) {
            digitalWrite(STEP_PIN, HIGH); 
            delayMicroseconds(700);
            digitalWrite(STEP_PIN, LOW); 
            delayMicroseconds(700);
            // Feed the watchdog periodically
            yield(); // This allows the ESP to perform background tasks and prevent a reset
        }
}



void libraryStep(int steps){
while (steps > 0) {
    int stepsToMove = (steps > 1000) ? 500 : steps;
    Serial.println(stepsToMove);
    stepper.step(stepsToMove);
    steps -= stepsToMove;
    delay(100);  // Optional: Add delay to allow the motor to run smoothly
}

}