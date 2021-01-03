#define CHECKCONNECTION 10000

struct serialData {
    int stringComplete;
    int stringCounter;
    char receivedString[64];
};


void receiveSerial(struct serialData * data);
void sendData(struct serialData * data);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  
}

void loop() {
    struct serialData data = {0, 0, ""};
    int error = 0;
    // Set timer to check connection ETC
    unsigned long interval, lastInterval = 0;
    while (error == 0){
        // Main
        interval = millis();
        receiveSerial(&data);
        sendData(&data);


        // error checking
        if ((interval - lastInterval) > CHECKCONNECTION){
            lastInterval = interval;
            Serial.println("Check");
        }
    }
}

void receiveSerial(struct serialData * data) {
    while (Serial.available()) {
        // get the new byte:
        char inChar = (char)Serial.read();
        data->receivedString[data->stringCounter] = inChar;
        data->stringCounter++;
        if ((inChar == '\n') || (data->stringCounter >= 63)) {
            data->receivedString[data->stringCounter] = '\0';
            data->stringComplete = 1;
        }
    }
}

void sendData(struct serialData * data){
    if (data->stringComplete == 1) {
        data->stringComplete = 0;
        data->stringCounter = 0;
        Serial.println("Received data:");
        Serial.println(data->receivedString);
    }
}

