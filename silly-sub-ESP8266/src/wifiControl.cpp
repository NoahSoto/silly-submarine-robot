#include "wifiControl.h"
#include "stepperControl.h"


ESP8266WebServer server(80);  // Create a web server that listens on port 80

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
void setupServer(ESP8266WebServer& server){
    server.on("/", HTTP_GET, handleRoot);  // Handle root URL
    server.on("/postplain", HTTP_POST, handlePlain); // Handle POST to /postplain
    server.on("/postform", HTTP_POST, handleForm);  // Handle POST to /postform
    server.onNotFound(handleNotFound);   // Handle 404 errors
    server.begin();
    Serial.println("HTTP server started");
}


const String postForms = "<html>\
  <head>\
    <title>Silly-Submarine: Powered by an ESP8266 Web Server POST handling page</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>POST submarine syringe step amount /postform</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/postform\">\
      <input type=\"text\" name=\"steps\" value=\"world\"><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
  </body>\
</html>";

void handleRoot() {
  server.send(200, "text/html", postForms);
}

void handlePlain() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    server.send(200, "text/plain", "STEPPING SYRINGES OUT TO:\n" + server.arg("plain"));
    int steps = server.arg("plain").toInt();
    Serial.print("Stepping ");
    Serial.println(steps);
    stepper.step(steps);

  }
}

void handleForm() {
  if (server.method() != HTTP_POST) {
    server.send(405, "text/plain", "Method Not Allowed");
  } else {
    String message = "";
    for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
    server.send(200, "text/plain", message);
    long steps = server.arg(0).toInt();
    Serial.print("Stepping ");
    Serial.println(steps);
    moveStepper(steps);
  }
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
  server.send(404, "text/plain", message);
}