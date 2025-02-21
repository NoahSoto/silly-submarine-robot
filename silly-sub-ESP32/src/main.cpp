// Define stepper pins
#include <AccelStepper.h>
#include <Arduino.h>
#include <HardwareSerial.h>

#include "stepperControl.h"
#include "wifiControl.h"
#include "brushlessControl.h"
//#include "SoftwareSerial.h" 



int driveVal = 0;
int lastVal = 0;




void setup(){
  Serial.begin(115200);
  
    // Initialize Serial1 for GPIO 16 (RX) and GPIO 17 (TX)
  Serial1.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("ESP32 is ready to send and receive on Serial1.");
  //setupStepper(); //not actually needed?
  setupBrushless();
  //setupWifi("jo-jungle","submarine-dog-banana");

  //setupServer(server);

  //pinMode(2,OUTPUT);

  delay(3000);
}

void dataParser(String data, String* controllerInput) {  
 
 int buttonsIndex = data.indexOf("buttons: ");
  if (buttonsIndex != -1) {
    int startIndex = buttonsIndex + 9; // Skip "buttons: "
    int endIndex = data.indexOf(",", startIndex);
    controllerInput[0] = data.substring(startIndex, endIndex); // Store button value
    String button = controllerInput[0];

    
    if (button.equals("0x0010")) {
      sink();
    } else if (button.equals("0x0020")) {
      rise();
    } else if (button.equals("0x0008")) {
      moveFwdStepper(50);
    } else if (button.equals("0x0001")) {
      moveFwdStepper(-50);
    }    

  }
  // Parse axis L values
  int axisIndex = data.indexOf("axis L: ");
  if (axisIndex != -1) {
    int startIndex = axisIndex + 8; // Skip "axis L: "
    int commaIndex = data.indexOf(",", startIndex);
    if (commaIndex != -1) {
      controllerInput[1] = data.substring(startIndex, commaIndex);          // X value
      controllerInput[2] = data.substring(commaIndex + 1);           // Y value
      int intX = controllerInput[1].toInt();
      int intY = controllerInput[2].toInt() * -1;

      dualMotorDriveSingleJoystick(intX, intY);
      Serial.printf("X: %d\n", intX);
      Serial.printf("Y: %d\n", intY);
    }
  }
}


void processData(String* controllerInput){
  for(int i=0;i<controllerInput->length();i++){
     //axis L (x -> turning), axis L (y -> forward/back), left bumper (sink), right bumper (rise), button 1 (foward stepper), button 2 (back stepper) 
    if(i==0){
      //drive(controllerInput[0].toInt());
    }
  }  
}

bool ledState = true;

void readData(){

    String controllerInput[6] = {"","","","","",""};
    String data = Serial1.readStringUntil('\n');

    Serial.println(data.c_str());

    //digitalWrite(2,ledState);
    //ledState = !ledState;
    Serial.printf("Recieved on Hardware Serial Line #2: %s\n",data);
    //Serial.println("Processing data now....");
    dataParser(data,controllerInput);
    // for (int i = 0; i < 6; i++) {
    //     if (controllerInput[i].length() > 0) { // Skip empty entries
    //         Serial.printf("Controller Input[%d]: %s\n", i, controllerInput[i].c_str());
    //         //processData(controllerInput);
    //     }
    // }

}

void loop(){
  //Serial.println("Test");

  //server.handleClient();  // Add this line to process incoming requests
  

  if(Serial1.available() > 0){
    readData();
  }

}