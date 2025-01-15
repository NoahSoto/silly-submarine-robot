#include "brushlessControl.h"
#include <Arduino.h>

Servo escPort;
Servo escpStarboard;


void setupBrushless(){
    escPort.attach(BRUSHLESS_SIGNAL_PORT); //min pwm  = 1 ms, max = 2 ms
    // Initialize escPort to stop position
    escPort.writeMicroseconds(1000); // Minimum throttle or neutral (for bidirectional)
    Serial.println("Pause for escPort initalization");
    delay(2000);                 // Allow escPort to initialize
    Serial.println("Resume");

/*
    escStarboard.attach(BRUSHLESS_SIGNAL_STARBOARD); //min pwm  = 1 ms, max = 2 ms
    // Initialize escStarboard to stop position
    escStarboard.writeMicroseconds(1000); // Minimum throttle or neutral (for bidirectional)
    Serial.println("Pause for escStarboard initalization");
    delay(2000);                 // Allow escPort to initialize
    Serial.println("Resume");
*/


}

bool drive(int throttle){

 
    if(throttle == 0){
        escPort.writeMicroseconds(1000); //stop!
        //Serial.println("Hopefully stopped...");
    }
    if(throttle > 1000 && throttle < 2000){
        escPort.writeMicroseconds(throttle);
        return true;
    }else{
        escPort.writeMicroseconds(1000);
        return false;
    }

}

bool drivePort(int throttle){

 
    if(throttle == 0){
        escPort.writeMicroseconds(1000); //stop!
        //Serial.println("Hopefully stopped...");
    }
    if(throttle > 1000 && throttle < 2000){
        escPort.writeMicroseconds(throttle);
        return true;
    }else{
        escPort.writeMicroseconds(1000);
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
   }else{

    int forward = map(throttleY,-500,500,minThrottle,maxThrottle);
    int turn = map(throttleX,-500,500,minThrottle,maxThrottle);

    adjustedThrottleP = forward + turn;
    adjustedThrottleS = forward - turn;

    adjustedThrottleP = constrain(adjustedThrottleP,minThrottle,maxThrottle);
    adjustedThrottleS = constrain(adjustedThrottleS,minThrottle,maxThrottle);

    drivePort(adjustedThrottleP);
    driveStarboard(adjustedThrottleS);

   }
}