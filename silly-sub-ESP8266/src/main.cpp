// Define stepper pins
#include <AccelStepper.h>
#include <Arduino.h>
#include <Stepper.h>

#include "stepperControl.h"
#include "wifiControl.h"
#include "brushlessControl.h"



extern int driveVal = 0;

int lastVal = 0;
void setup(){
  Serial.begin(115200);
  setupStepper();
  setupBrushless();
  setupWifi("jo-jungle","submarine-dog-banana");

  setupServer(server);


  
}

void loop(){

  server.handleClient();  // Add this line to process incoming requests
  if(lastVal != driveVal){
    lastVal = driveVal;
  }
  //Serial.printf("Drive value: %d\n",driveVal);
  
  drive(driveVal);
  //esc.writeMicroseconds(2000);
}