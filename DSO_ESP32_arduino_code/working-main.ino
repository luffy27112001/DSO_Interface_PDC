#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#define DSO_PROBE_pin 34
#define WIFI_MODE_control_pin 32

const char* ssid = "SPIT-PDC"; 
const char* password = "pdc2020@spit"; 
const char* APssid = "ESP32"; 
const char* APpassword = "123456789"; 
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");
void setup() {
  Serial.begin(115200);
  pinMode(WIFI_MODE_control_pin, INPUT);
  bool wifion = true; 
  int control = digitalRead(WIFI_MODE_control_pin);
  // Serial.println(control);
    
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
     Serial.println("Connecting to WiFi..");
    }
    Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());    
  delay(2000);
  initWebSocket();
  server.begin();
  }
void loop() {
  String potValue;
  for(int i = 1; i < 2500; i++){
    potValue += String(analogRead(DSO_PROBE_pin)) + " ";
  }
  ws.textAll(potValue);
  potValue = "";
}

void initWebSocket() {
  server.addHandler(&ws);
}
