#include <ESP8266WiFi.h>

const char* ssid     = "";
const char* password = "";

void WiFiEvent(WiFiEvent_t event) {
  Serial.printf("[WiFi-event] event: %d\n", event);  
}

void setup() {
  Serial.begin(115200);
  WiFi.disconnect(true);
  delay(1000);
  WiFi.onEvent(WiFiEvent);
  WiFi.begin(ssid, password);
}

void sendData(WiFiClient*);
void clientConnect(WiFiClient*);

void loop() {
    const uint16_t port = 1112;
    const char * host = "192.168.0.101";
    client.connect(host, port);

    sendData(&client);
    

  // client.flush();
  // client.stop();
  // delay(5000);   
}
void clientConnect(WiFiClient * client){
    const uint16_t port = 1112;
    const char * host = "192.168.0.101";
    client->connect(host, port);
}

void sendData(WiFiClient * client){
    client->print(char(0x71));
    delay(1000);
    client->print(char(0x72));
    delay(1000);
    client->print(char(0x73));
    delay(1000);
    client->print(char(0x74));
    delay(1000);
    client->print(char(0x75));
    delay(1000);
    client->flush();
    // client->stop();
}

