#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// Hardcode WiFi parameters as this isn't going to be moving around.
const char* ssid = "";
const char* password = "";

// Start a TCP Server on port 5045
WiFiServer server(5045);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);
  Serial.println("testi");
  //Wait for connection
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected to "); Serial.println(ssid);
  Serial.print("IP Address: "); Serial.println(WiFi.localIP());
 
  // Start the TCP server
  server.begin();
}
WiFiClient client = server.available();
void loop() {
  // listen for incoming clients
  if (client){
    Serial.println("Client connected");
    while (client.connected()){
        // Read the incoming TCP command
        //String command = ReadTCPCommand(&client);
        // Debugging display command
        //command.trim();
        // Serial.println(command);
        // Phrase the command
        // PhraseTCPCommand(&client, &command);
        Serial.println("Connected");
        delay(1000);
    }
  }
 } 