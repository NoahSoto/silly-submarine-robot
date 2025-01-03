#include <Stepper.h>
#include <Arduino.h>

const int steps_per_rev = 200; //Set to 200 for NIMA 17
#define IN1 5
#define IN2 4
#define IN3 14
#define IN4 12

Stepper motor(steps_per_rev, IN1, IN2, IN3, IN4);


void setup()
{
  motor.setSpeed(60);
  Serial.begin(115200);
}

void loop() 
{
  Serial.println("Rotating Clockwise...");
  motor.step(steps_per_rev);

  Serial.println("Rotating Anti-clockwise...");
  motor.step(-steps_per_rev);
  delay(500);
}