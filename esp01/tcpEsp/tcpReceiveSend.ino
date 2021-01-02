// https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-class.html
#include <ESP8266WiFi.h>
 
#ifndef STASSID
#define STASSID ""
#define STAPSK  ""
#endif

struct serialData{
    int stringComplete;
    int stringCounter;
    char receivedString[64];
};

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "192.168.0.104";
const uint16_t port = 1112;

void receive(struct serialData * data);

void setup() {
  
    Serial.begin(115200);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    WiFiClient client;
    struct serialData data = {0, 0, ""};
    int error = 0;
    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        delay(5000);
        return;
    }

    while (error == 0){
        receive(&data);
        if (data.stringComplete == 1) {
            data.stringComplete = 0;
            data.stringCounter = 0;
            Serial.println("Received data:");
            Serial.println(data.receivedString);
            if (client.connected()){
                Serial.println("SENDING");
                client.print(data.receivedString);
            }
            else{
                Serial.println("Client not connected");
            }
        }
    }
}

void receive(struct serialData * data) {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        data->receivedString[data->stringCounter] = inChar;
        data->stringCounter++;
        if ((inChar == '\n') || (data->stringCounter == 63)) {
            data->receivedString[data->stringCounter] = '\0';
            data->stringComplete = 1;
        }
    }
}