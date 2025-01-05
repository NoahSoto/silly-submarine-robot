#ifndef WIFI_CONTROL_H
#define WIFI_CONTROL_H

#include <ESP8266WebServer.h> // or <WebServer.h> for ESP32
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Arduino.h>
#include <Stepper.h>



extern ESP8266WebServer server; // Declare the server object
extern Stepper stepper;
extern const String postForms;
extern int driveVal;

void setupWifi(const char* ssid, const char* password);
void setupServer(ESP8266WebServer& server);
void handleNotFound();
void handleRoot();
void handleThrust();
void handleForm();

#endif // STEPPER_CONTROL_H