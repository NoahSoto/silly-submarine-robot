#include "brushlessControl.h"
#include <Arduino.h>

Servo escPort;
Servo escStarboard;



void setupBrushless(){
 


    escPort.attach(BRUSHLESS_SIGNAL_PORT, minPWM, maxPWM); //min pwm  = 1 ms, max = 2 ms
    escStarboard.attach(BRUSHLESS_SIGNAL_STARBOARD,minPWM,maxPWM);
    
    // Initialize escPort to stop position
    
    
    escPort.writeMicroseconds(1000); // 1000 µs pulse width (stopped)
    escStarboard.writeMicroseconds(1000);
     //Minimum throttle or neutral (for bidirectional)
    Serial.println("Pause for escPort / escStarboard initalization");
    delay(2000);                 // Allow escPort to initialize
    Serial.println("Resume");



}

void analogDrive(int speed){
   //for (int speed = 26; speed <= 52; speed += 2) {  // 26 (~1000 µs) to 52 (~2000 µs)

    analogWrite(BRUSHLESS_SIGNAL_PORT, speed);

}

bool drive(int throttle){

 
    if(throttle == 0){
        escPort.write(0); //stop!
        //Serial.println("Hopefully stopped...");
    }
    if(throttle > 0 && throttle < 180){
        escPort.write(throttle);
        return true;
    }else{
        escPort.write(1000);
        return false;
    }

}
bool driveStarboard(int throttle){

 
    if(throttle == 0){
        escStarboard.writeMicroseconds(1000); //stop!
        //Serial.println("Hopefully stopped...");
    }
    if(throttle > 1000 && throttle < 2000){
        escStarboard.writeMicroseconds(throttle);
        return true;
    }else{
        escStarboard.writeMicroseconds(1000);
        return false;
    }

}
bool drivePort(int throttle){

 
    if(throttle == 0){
        escPort.write(1000); //stop!
    }
    if(throttle > 1000 && throttle < 2000){
        escPort.write(throttle);
        return true;
    }else{
        escPort.write(1000);
        return false;
    }

}



void dualMotorDriveSingleJoystick(int throttleX, int throttleY){

    const int stop = 1000; // Motor stop value
    const int maxThrottle = 2000; // Maximum motor throttle
    const int minThrottle = 1001; // Minimum motor throttle
    const int deadband = 100; // Joystick deadband range

    int adjustedThrottleP,adjustedThrottleS;

   if (abs(throttleX) < deadband && abs(throttleY) < deadband) {
        // Both motors are stopped
        adjustedThrottleP = stop;
        adjustedThrottleS = stop;
   }else if(abs(throttleX) < deadband && throttleY >450){
        adjustedThrottleP = stop;
        adjustedThrottleS = stop;
   }else{

    int yAxis = map(throttleY,-500,500,minThrottle,maxThrottle);
    int xAxis = map(throttleX,-500,500,minThrottle,maxThrottle);
    
    if(xAxis < 0){
        adjustedThrottleP = stop;
        adjustedThrottleS = xAxis;
    }
    if(xAxis > 0){
        adjustedThrottleP = xAxis;
        adjustedThrottleS = stop;
    }

    if(yAxis < 0){
        adjustedThrottleP = stop;
        adjustedThrottleS = stop;
    }
    if (yAxis > 0){
        adjustedThrottleP = yAxis;
        adjustedThrottleS = yAxis;
    }

    drivePort(adjustedThrottleP);
    driveStarboard(adjustedThrottleS);
   }
}