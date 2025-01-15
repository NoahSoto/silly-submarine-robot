// Define stepper pins
#include <AccelStepper.h>
#include <Arduino.h>

#include "stepperControl.h"
#include "wifiControl.h"
#include "brushlessControl.h"
//#include "SoftwareSerial.h" 



int driveVal = 0;
int lastVal = 0;

void setup(){
  Serial.begin(115200);
  //Serial1.begin(9600);
  //setupStepper(); //not actually needed?
  setupBrushless();
  setupWifi("jo-jungle","submarine-dog-banana");

  setupServer(server);

  pinMode(2,OUTPUT);

  
}


void dataParser(String data, String* controllerInput){
    // Split the data on c ommas first
  //axis L (x -> turning), axis L (y -> forward/back), left bumper (sink), right bumper (rise), button 1 (foward stepper), button 2 (back stepper) 
    while (data.length() > 0) {
      int commaIndex = data.indexOf(','); // Find the next comma
      String chunk;

      if (commaIndex == -1) { // No more commas
        chunk = data;
        data = "";
      } else {
        chunk = data.substring(0, commaIndex); // Extract chunk before comma
        data = data.substring(commaIndex + 1); // Update remaining data
      }

      // Split each chunk on the colon ':'
      int colonIndex = chunk.indexOf(':');
      if (colonIndex != -1) {
        String field = chunk.substring(0, colonIndex); // Extract the field
        String value = chunk.substring(colonIndex + 1); // Extract the value

        field.trim(); // Remove leading/trailing spaces
        value.trim();

        Serial.print("Field: ");
        Serial.print(field);

        Serial.print(", Value: ");
        Serial.println(value);
        
        if(field.equals("axis L")){
          String x,y;
          int commaIndex2 = value.indexOf(",");

          x = value.substring(0,commaIndex2); // x axis of L joystick (string)
          y = value.substring(commaIndex2 + 1); // y axxis of L joystick (string)

          controllerInput[0] = "X-TURN:" + x;
          controllerInput[1] = "Y-DRIVE:" + y;
        }if (field.equals("buttons")) {
          if (value.equals("0x0010")) {
            controllerInput[2] = "LB-SINK:" + value;
          } else if (value.equals("0x0020")) {
            controllerInput[3] = "RB-RISE:" + value;
          } else if (value.equals("0x0008")) {
            controllerInput[4] = "F-STEPIN:" + value;
          } else if (value.equals("0x0001")) {
            controllerInput[5] += "F-STEPO:" + value + "; ";  // Append instead of overwrite
          }
        }
  // Handle additional cases similarly
        }
      }
   }



void processData(String* controllerInput){
  for(int i=0;i<controllerInput->length();i++){
     //axis L (x -> turning), axis L (y -> forward/back), left bumper (sink), right bumper (rise), button 1 (foward stepper), button 2 (back stepper) 
    if(i=0){
      drive(controllerInput[0].toInt());
    }
  }  
}

bool ledState = true;

void loop(){
  //Serial.println("Test");

  server.handleClient();  // Add this line to process incoming requests

  analogDrive(driveVal);
}