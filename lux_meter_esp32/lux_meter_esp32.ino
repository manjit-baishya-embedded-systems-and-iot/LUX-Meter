#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// setting IP Address
IPAddress local_IP(192, 168, 1, 22); // Set your desired IP address
IPAddress gateway(192, 168, 1, 1);    // Set your gateway
IPAddress subnet(255, 255, 255, 0);   // Set your subnet mask

const int ldrPin = 36; // ADC1 channel 0 (GPIO36) for ESP32
WebServer server(80);  // create a web server object that listens for HTTP requests on port 80

const char* ssid = "HOME";  // replace with your WiFi SSID
const char* password = "BSNL_wifi@2569";  // replace with your WiFi password

void setup() {
  Serial.begin(9600); // initialize serial communication at 9600 bps
  pinMode(ldrPin, INPUT);

  // attempt to configure WiFi with static IP
  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("STA Failed to configure");
  }

  // connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");

  // print IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // start the server
  server.on("/data", handleData);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();  // handle client requests

  // read the analog value from the LDR and calculate lux
  int analogValue = analogRead(ldrPin) / 4;
  float lux = calculateLux(analogValue);

  // print the values to serial
  Serial.print("Analog Value: ");
  Serial.print(analogValue);
  Serial.print(" | Light Intensity: ");
  Serial.print(lux, 4);
  Serial.println(" lux");

  delay(1000); // wait for a second before taking another reading
}

void handleData() {
  // read the analog value from the LDR and calculate lux
  int analogValue = analogRead(ldrPin) / 4;
  float lux = calculateLux(analogValue);

  // create JSON object
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["analogValue"] = analogValue;
  jsonDoc["lux"] = lux;

  // serialize JSON object to string
  String jsonResponse;
  serializeJson(jsonDoc, jsonResponse);

  // set CORS headers
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", jsonResponse);
}

float calculateLux(int x) {
  // polynomial equation coefficients for a 4th-degree polynomial
  if (x < 800) {
    // coefficients for LUX < 800
    return 3.17382282e-09 * pow(x, 4) + -1.70265352e-06 * pow(x, 3) + 
           -1.43694567e-03 * pow(x, 2) + 1.02943685 * x + -132.143469;
  } else {
    // coefficients for LUX > 800
    return 1.49971935e-04 * pow(x, 4) + -5.45547466e-01 * pow(x, 3) + 
           7.43741376e+02 * pow(x, 2) + -4.50342742e+05 * x + 1.02186631e+08;
  }
}
