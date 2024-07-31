#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const char* ssid     = ""; // Insert here your SSID
const char* password = ""; // Insert here your Password
const int LED_1 = 3;       // LED D3 is mapped on number "1"

/*
  void handleWrongRequest() {
    server.send(404, "text/plain", "404 Not Found. Bad Request :(");
  }
*/

void greetUser() {
  server.send(200, "text/plain", "Hello from ESP8266! WebServer Started! [192.168.1.25] :)");
}

void handleLED1On() {
  lightUpLED(LED_1);
  String message = "LED_1 is now ON!\n";
  Serial.print(message);
  server.send(200, "text/plain", message);
}

void handleLED1Off() {
  turnOffLED(LED_1);
  String message = "LED_1 is now OFF!\n";
  Serial.print(message);
  server.send(200, "text/plain", message);
}

void lightUpLED(const int LED) {
  digitalWrite(LED, HIGH);
}

void turnOffLED(const int LED) {
  digitalWrite(LED, LOW);
}

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, LOW);

  WiFi.begin(ssid, password);

  int max_attempts = 20;
  int attempts = 0;

  while (WiFi.status() != WL_CONNECTED && attempts < max_attempts) {
    delay(500);
    Serial.print(".");
    attempts += 1;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("Connesso al WiFi");
    Serial.print("Indirizzo IP: ");
    Serial.println(WiFi.localIP());
    
    server.on("/", greetUser);
    server.on("/led/high/1", handleLED1On);
    server.on("/led/low/1",  handleLED1Off);
    // server.onNotFound(handleWrongRequest);

    server.begin();
    Serial.println("ESP8266 HTTP WebServer started! :)");
  } else {
    Serial.println("");
    Serial.println("Connessione al WiFi fallita. :(");
  }
}

void loop() { 
  server.handleClient();
}