/* PERSONAL LIBRARIES [CUSTOM] */
// #include "MyAnimationLib.h"
// #include "ArduinoSecrets.h"

/* PROJECT LIBRARIES */
#include <WiFiS3.h>
// #include <LiquidCrystal_I2C.h>

/* OBJECTS */
WiFiServer server(80);
// MyAnimationLib myAnimLib;
// LiquidCrystal_I2C lcd(0x27, 16, 2);

const char* WIFI_SSID = ""; /* Here insert your SSID */
const char* WIFI_PASS = ""; /* Here insert your PASSWORD */

int status = WL_IDLE_STATUS;
const int LED_PINS[] = {3, 4, 5, 6};
const int NUM_LED_PINS = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

void setup() {
  Serial.begin(9600);
  // myAnimLib.init();
  // lcd.init();
  // lcd.backlight();

  for (int i = 0; i < NUM_LED_PINS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true); // Do not continue
  }

  if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware!");
  }

  while (status != WL_CONNECTED) {
    Serial.println("Attempting to connect to Network ");
    status = WiFi.begin(WIFI_SSID, WIFI_PASS);
    delay(3000);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    long rssi = WiFi.RSSI();
    Serial.print("To see this page in action, open a browser to http://");
    Serial.println(ip);

    server.begin(); // Start the WebServer on port 80
  }
}

void loop() {
  delay(1000);
  // myAnimLib.play();
  // lcd.setCursor(0, 0);
  // lcd.print("Welcome!");

  WiFiClient client = server.available(); // Listen for incoming client connections
  if (client) {
    String currentLine = "", request = "";
    boolean currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        request += c;

        if (c == '\n' && currentLineIsBlank) {
          Serial.print("Request: ");
          Serial.println(request);

          // Send HTTP Response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: keep-alive");
          client.println("Keep-Alive: timeout=5, max=100");
          client.println();

          bool handled = handleRequest(request, client);
          if (!handled) client.println("<h3><center><p>ARDUINO UNO R4 WIFI WEB SERVER ON 192.168.1.21:80</p></center></h3>");
          client.println();
          break;
        }

        if (c == '\n') {
          currentLineIsBlank = true;
        } else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    Serial.println("Ready for next request...");
  }
  client.stop();
}

void turnOnLED(const int LED) {
  digitalWrite(LED, HIGH);
  // TODO: NOTIFY ON LCD SCREEN
}

void turnOffLED(const int LED) {
  digitalWrite(LED, LOW);
  // TODO: NOTIFY ON LCD SCREEN
}

bool handleRequest(String request, WiFiClient& client) {
  for (int i = 0; i < NUM_LED_PINS; i++) {
    String ledOnPath = "GET /led/HIGH/" + String(i + 1);
    String ledOffPath = "GET /led/LOW/" + String(i + 1);      
    if (request.indexOf(ledOnPath) != -1) {
      turnOnLED(LED_PINS[i]);
      client.println("LED_" + String(i + 1) + " is now ON!");
      Serial.println("LED_" + String(i + 1) + " is now ON!");
      return true;
    } else if (request.indexOf(ledOffPath) != -1) {
      turnOffLED(LED_PINS[i]);
      client.println("LED_" + String(i + 1) + " is now OFF!");
      Serial.println("LED_" + String(i + 1) + " is now OFF!");
      return true;
    }
  }
  return false;
}