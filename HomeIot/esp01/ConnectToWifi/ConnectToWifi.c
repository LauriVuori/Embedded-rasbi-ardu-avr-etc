#include "ESP8266WiFi.h"

const char* ssid = "ssid"; //Enter SSID
const char* password = "password"; //Enter Password

void setup(void)
{ 
  Serial.begin(115200);
  // Connect to WiFi
  WiFi.begin("SSID", "PASSWORD");
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
  Serial.printf("Connection status: %d\n", WiFi.status());
}

void loop() 
{
  // EMPTY
}