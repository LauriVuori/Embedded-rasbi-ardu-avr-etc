struct serialData{
    int stringComplete;
    int stringCounter;
    char receivedString[64];
};

void receive(struct serialData * data);

void setup() {
  // initialize serial:
  Serial.begin(9600);
  
}

void loop() {
    struct serialData data = {0, 0, ""};
    int error = 0;
    while (error == 0){
      receive(&data);
        if (data.stringComplete == 1) {
            data.stringComplete = 0;
            data.stringCounter = 0;
            Serial.println("Received data:");
            Serial.println(data.receivedString);
        }
    }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/

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