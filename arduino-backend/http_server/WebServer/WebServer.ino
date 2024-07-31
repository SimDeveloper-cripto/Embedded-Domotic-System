/* PERSONAL LIBRARY [CUSTOM] */
#include "MyAnimationLib.h"
#include "ArduinoSecrets.h"

/* PROJECT LIBRARIES */
#include <WiFiS3.h>
#include <LiquidCrystal_I2C.h>

/* OBJECTS */
WiFiServer server(80);
MyAnimationLib myAnimLib;
// LiquidCrystal_I2C lcd(0x27, 16, 2);

int status = WL_IDLE_STATUS;
const int LED_1 = 3;

void setup() {
  Serial.begin(9600);
  myAnimLib.init();
  // lcd.init();
  // lcd.backlight();

  pinMode(LED_1, OUTPUT);
  digitalWrite(LED_1, LOW);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    while (true); // Do not continue
  }

  if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware!");
  }

  while (status != WL_CONNECTED) {
    Serial.println("Attempting to connect to Network ");
    status = WiFi.begin(SSID, PASS);
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
  myAnimLib.play();

  // lcd.setCursor(0, 0);
  // lcd.print("Welcome!");

  WiFiClient client = server.available(); // Listen for incoming client connections

  if (client) {
    String currentLine = "";
    String request = "";
    boolean currentLineIsBlank = true;

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        request += c;

        if (c == '\n' && currentLineIsBlank) {
          Serial.print("Request: ");
          Serial.println(request);

          // Send HTTP response
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println();

          if (request.indexOf("GET /") != -1) {
            client.println("<h3><center><p>ARDUINO UNO R4 WIFI WEB SERVER ON 192.168.1.25:80</p></center></h3>");
          } else if (request.indexOf("GET /led/HIGH/1") != -1) {
            // TODO: THIS CODE BLOCK DOES NOT GET EXECUTED
            lightUpLED(LED_1);
            client.println("LED_1 is now ON!");
            Serial.println("LED_1 is now ON!");
          } else if (request.indexOf("GET /led/LOW/1") != -1) {
            // TODO: THIS CODE BLOCK DOES NOT GET EXECUTED
            turnOffLED(LED_1);
            client.println("LED_1 is now OFF!");
            Serial.println("LED_1 is now OFF!");
          }

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

    client.stop();
    Serial.println("Client Disconnected.");
  }
}

void lightUpLED(const int LED) {
  digitalWrite(LED, HIGH);
  // TODO: NOTIFY ON LCD SCREEN
}

void turnOffLED(const int LED) {
  digitalWrite(LED, LOW);
  // TODO: NOTIFY ON LCD SCREEN
}