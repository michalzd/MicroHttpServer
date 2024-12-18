/* test serwera Http 
 * płytka DOIT ESP32 DEVKIT V1
 */

#include <Arduino.h>
#include <WiFi.h>
#include "microHttpServer.h"

char ssid[] = "LocalESP32";
char password[] = "09876543";


HttpServer  httpServer;

void printWifiStatus() 
{
  Serial.print("Setting Access Point: ");
  Serial.println(ssid);

//  IPAddress ip = WiFi.localIP();
  IPAddress ip = WiFi.softAPIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

}


void setup() {

  Serial.begin(115200); 
  pinMode (LED_BUILTIN, OUTPUT); 
  
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  delay(1000);  // opóżniam, bo serial monitor nie łapie od razu
  printWifiStatus();

  httpServer.Begin();
  

}

void loop() {
  
  httpServer.Listen();
  
  // delay(500);
  // digitalWrite(LED_BUILTIN, HIGH);
  // delay(500);
  // digitalWrite(LED_BUILTIN, LOW);
  
}
