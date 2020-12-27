

// Import required libraries
#if defined ARDUINO_ARCH_ESP32 || ESP32 || ARDUINO_ESP32_DEV
  #include <WiFi.h>
  #include <AsyncTCP.h>
  #include <Update.h>
  #include <ESPmDNS.h>
#elif defined ARDUINO_ARCH_ESP8266 || ESP8266 || ARDUINO_ESP8266_WEMOS_D1MINI
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
  #include <Updater.h>
  #include <ESP8266mDNS.h>  
#endif
#include <ESPAsyncWebServer.h>
#include <ArduinoOTA.h>
#include <JeVe_EasyOTA.h> v
EasyOTA OTA;

// Replace with your network credentials
const char* ssid = "iot";
const char* password = "qwertyui1234567890";
#define WIFI_SSID        "iot"
#define WIFI_PASSWORD    "qwertyui1234567890"
#define ARDUINO_HOSTNAME "ota-flash-demo"

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  Serial.print("Local IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      request->send(200, "text/plain", "Hello, world");
  });
  
  server.onNotFound(notFound);
  
  // Start server
  server.begin();

  OTA.onMessage([](char *message, int line) {
    Serial.println(message);
  });
  OTA.setup(WIFI_SSID, WIFI_PASSWORD, ARDUINO_HOSTNAME);
}

void loop() {
  OTA.loop();
}
