#ifndef WIFI_CONTROL_H
#define WIFI_CONTROL_H

#include <WiFiClient.h>
#include <WiFi.h>              // For WiFi on ESP32
#include <WebServer.h>         // For web server on ESP32
#include <Arduino.h>
#include <Stepper.h>



extern WebServer server;      // Declare the server object (updated for ESP32)
extern Stepper stepper;       // Declare the stepper motor object
extern const String postForms;
extern int driveVal;

// WiFi setup function declaration
void setupWifi(const char* ssid, const char* password);

// Server setup function declaration
void setupServer(WebServer& server);    // Updated to use WebServer for ESP32

// Handlers for different routes
void handleNotFound();
void handleRoot();
void handleThrust();
void handleForm();


#endif // STEPPER_CONTROL_H