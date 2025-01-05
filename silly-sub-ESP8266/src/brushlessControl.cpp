#include "brushlessControl.h"
#include <Arduino.h>

Servo esc;


void setupBrushless(){
    esc.attach(BRUSHLESS_SIGNAL); //min pwm  = 1 ms, max = 2 ms
    // Initialize ESC to stop position
    esc.writeMicroseconds(1000); // Minimum throttle or neutral (for bidirectional)
    Serial.println("Pause for esc initalization");
    delay(2000);                 // Allow ESC to initialize
    Serial.println("Resume");

}

bool drive(int throttle){

 
    if(throttle == 0){
        esc.writeMicroseconds(1000); //stop!
        //Serial.println("Hopefully stopped...");
    }
    if(throttle > 1000 && throttle < 2000){
        esc.writeMicroseconds(throttle);
        Serial.printf("Throttling %d\n",throttle);
        return true;
    }else{
        esc.writeMicroseconds(1000);
        Serial.println("Invalid input, stopping");
        return false;
    }

}