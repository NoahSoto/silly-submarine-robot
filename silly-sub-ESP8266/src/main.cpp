#include <Arduino.h>

// put function declarations here:
int myFunction(int, int);
#define PIN 0
void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  pinMode(PIN,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Testing....\n");
  delay(500);
  digitalWrite(PIN,HIGH);
  delay(500);
  digitalWrite(PIN,LOW);
  delay(100);
  digitalWrite(PIN,HIGH);
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}