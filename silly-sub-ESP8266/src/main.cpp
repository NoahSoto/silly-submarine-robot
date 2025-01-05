// Define stepper pins
#include <AccelStepper.h>
#include <Arduino.h>
#include <Stepper.h>

#include "stepperControl.h"
#include "wifiControl.h"
// Define stepper pins

#define STEPS_PER_REVOLUTION 200 // Steps per revolution for the motor

#define STEP_PIN 5      // Step pin
#define DIR_PIN 4       // Direction pin




void setup(){
  Serial.begin(115200);
  setupStepper();
  
  setupWifi("jo-jungle","submarine-dog-banana");

  setupServer(server);
  
}

void loop(){

  server.handleClient();  // Add this line to process incoming requests
}