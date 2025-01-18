#include <Arduino.h>

void setup() {
  // Initialize the USB serial monitor for debugging
  Serial.begin(115200);

  // Initialize Serial1 for GPIO 16 (RX) and GPIO 17 (TX)
  Serial1.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("ESP32 is ready to send and receive on Serial1.");
}

void loop() {
  // Check if data is available from the Serial Monitor
  if (Serial.available() > 0) {
    String inputData = Serial.readString();  // Read the incoming data from Serial Monitor

    // Send the received data via Serial1
    Serial1.println(inputData);

    // Print the sent data to Serial Monitor for debugging
    Serial.print("Sent to Serial1: ");
    Serial.println(inputData);
  }

  // Check if data is available from Serial1
  if (Serial1.available() > 0) {
    String receivedData = Serial1.readStringUntil('\n'); // Read the incoming data from Serial1

    // Print the received data to Serial Monitor
    Serial.print("Received on Serial1: ");
    Serial.println(receivedData);
  }
}
