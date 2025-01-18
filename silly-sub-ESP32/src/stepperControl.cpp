#include <Arduino.h>
#include "stepperControl.h"





// Create a Stepper instance
Stepper fwd_stepper(STEPS_PER_REVOLUTION, FWD_STEP_PIN, FWD_DIR_PIN); //forward
Stepper aft_stepper(STEPS_PER_REVOLUTION, AFT_STEP_PIN, AFT_DIR_PIN); //aft

void setupStepper() {
    // Set the speed of the stepper motor (in RPM)
    fwd_stepper.setSpeed(120); // Set desired speed in RPM
}

void moveFwdStepper(int steps) {

    int stepCount = abs(steps);  // Get the absolute value of steps to use in the loop
    if(steps == 0){
        return;
    }else if (steps > 0) {
        digitalWrite(FWD_DIR_PIN, HIGH);  // Set direction to HIGH for forward motion
    }else{
        digitalWrite(FWD_DIR_PIN, LOW);   // Set direction to LOW for reverse motion
    }

    unsigned long lastStepTime = 0;  // Variable to track time for each step


    // Iterate over the absolute value of steps
    for (int x = 0; x < stepCount; x++) {
            digitalWrite(FWD_STEP_PIN, HIGH); 
            delayMicroseconds(stepDelay);
            digitalWrite(FWD_STEP_PIN, LOW); 
            delayMicroseconds(stepDelay);
            // Feed the watchdog periodically
            yield(); // This allows the ESP to perform background tasks and prevent a reset
        }
}


void moveAftStepper(int steps) {

    int stepCount = abs(steps);  // Get the absolute value of steps to use in the loop
    if(steps == 0){
        return;
    }else if (steps > 0) {
        digitalWrite(AFT_DIR_PIN, HIGH);  // Set direction to HIGH for forward motion
    }else{
        digitalWrite(AFT_DIR_PIN, LOW);   // Set direction to LOW for reverse motion
    }


    unsigned long lastStepTime = 0;  // Variable to track time for each step


    // Iterate over the absolute value of steps
    for (int x = 0; x < stepCount; x++) {
            digitalWrite(AFT_STEP_PIN, HIGH); 
            delayMicroseconds(stepDelay);
            digitalWrite(AFT_STEP_PIN, LOW); 
            delayMicroseconds(stepDelay);
            // Feed the watchdog periodically
            yield(); // This allows the ESP to perform background tasks and prevent a reset
        }
}


void sink(){

    //int stepCount = abs(steps);  // Get the absolute value of steps to use in the loop

    digitalWrite(FWD_DIR_PIN, HIGH);  //  drive both steppers.
    digitalWrite(AFT_DIR_PIN, HIGH);  // drive both steppers but they have diff directions.

    unsigned long lastStepTime = 0;  // Variable to track time for each step

    int stepCount = 650; // minimum amount of steps, should get us to the next clock cycle and check again

    // Iterate over the absolute value of steps
    for (int x = 0; x < stepCount; x++) {
            digitalWrite(AFT_STEP_PIN, HIGH); 
            digitalWrite(FWD_STEP_PIN,HIGH);
            delayMicroseconds(stepDelay);
            digitalWrite(AFT_STEP_PIN, LOW); 
            digitalWrite(FWD_STEP_PIN,LOW);
            delayMicroseconds(stepDelay);
            // Feed the watchdog periodically
            yield(); // This allows the ESP to perform background tasks and prevent a reset
        }

}
void rise(){
    //int stepCount = abs(steps);  // Get the absolute value of steps to use in the loop

    digitalWrite(FWD_DIR_PIN, LOW);  //  drive both steppers.
    digitalWrite(AFT_DIR_PIN, LOW);  // drive both steppers but they have diff directions.

    unsigned long lastStepTime = 0;  // Variable to track time for each step

    int stepCount = 650; // minimum amount of steps, should get us to the next clock cycle and check again

    // Iterate over the absolute value of steps
    for (int x = 0; x < stepCount; x++) {
            digitalWrite(AFT_STEP_PIN, HIGH); 
            digitalWrite(FWD_STEP_PIN,HIGH);
            delayMicroseconds(stepDelay);
            digitalWrite(AFT_STEP_PIN, LOW); 
            digitalWrite(FWD_STEP_PIN,LOW);
            delayMicroseconds(stepDelay);
            // Feed the watchdog periodically
            yield(); // This allows the ESP to perform background tasks and prevent a reset
        }


}

void libraryStep(int steps){
while (steps > 0) {
    int stepsToMove = (steps > 1000) ? 500 : steps;
    Serial.println(stepsToMove);
    fwd_stepper.step(stepsToMove);
    steps -= stepsToMove;
    delay(100);  // Optional: Add delay to allow the motor to run smoothly
}

}