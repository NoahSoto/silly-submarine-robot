#include <WiFi.h>
#include <WebServer.h>

// Include your custom headers
#include "wifiControl.h"
#include "stepperControl.h"
#include "brushlessControl.h"

// Web server instance
WebServer server(80);

// Global variables
int driveVal;

// HTML Form
const String postForms = "<html>\
  <head>\
    <title>ESP32 Web Server</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>ESP32 Control Page</h1><br>\
    <form method=\"post\" action=\"/postform\">\
      <label for=\"steps\">Steps:</label>\
      <input type=\"text\" id=\"steps\" name=\"steps\" placeholder=\"Enter steps\"><br><br>\
      <button type=\"submit\">Submit Steps</button>\
    </form>\
    <form method=\"post\" action=\"/postthrust\">\
      <label for=\"thrust\">Thrust:</label>\
      <input type=\"text\" id=\"thrust\" name=\"thrust\" placeholder=\"Enter thrust\"><br><br>\
      <button type=\"submit\">Submit Thrust</button>\
    </form>\
  </body>\
</html>";

// WiFi Setup
void setupWifi(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);
    Serial.println("Connecting to WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nConnected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}

// Web Server Setup
void setupServer(WebServer& server) {
    server.on("/", HTTP_GET, handleRoot);
    server.on("/postthrust", HTTP_POST, handleThrust);
    server.on("/postform", HTTP_POST, handleForm);
    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("HTTP server started");
}

// Route Handlers
void handleRoot() {
    server.send(200, "text/html", postForms);
}


void handleThrust() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    String message = "";
    for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
    server.send(200, "text/plain", message);
    int thrust = server.arg(0).toInt();
    driveVal = thrust;
    Serial.println("Drive val set");
  }
}


void handleForm() {
    if (server.method() != HTTP_POST) {
        server.send(405, "text/plain", "Method Not Allowed");
        return;
    }
    if (server.hasArg("steps")) {
        long steps = server.arg("steps").toInt();
        Serial.printf("Stepping: %ld\n", steps);
        moveStepper(steps);
        server.send(200, "text/plain", "Stepper moved");
    } else {
        server.send(400, "text/plain", "Missing steps value");
    }
}

void handleNotFound() {
    String message = "File Not Found\n\n";
 
    server.send(404, "text/plain", message);
}
