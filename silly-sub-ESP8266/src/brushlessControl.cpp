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
        Serial.printf("Throttling %d\n",throttle);
        return true;
    }else{
        escPort.writeMicroseconds(1000);
        Serial.println("Invalid input, stopping");
        return false;
    }

}