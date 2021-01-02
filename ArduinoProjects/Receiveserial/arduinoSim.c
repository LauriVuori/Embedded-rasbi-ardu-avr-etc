char test[15];
int b = 0;
bool stringComplete = false;
struct serialData{
	int stringComplete;
    int stringCounter;
};

void receive(struct serialData * data);

void setup() {
	// initialize serial:
	Serial.begin(9600);
	
}

void loop() {
	struct serialData data = {0, 0};
    while (true){
	    receive(&data);
        if (data.stringComplete == 1) {
            data.stringComplete = 0;
            data.stringCounter = 0;
            stringComplete = false;
            Serial.println("STRING::");
            Serial.println(test);
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
		test[data->stringCounter] = inChar;
		data->stringCounter++;
		if (inChar == '\n') {
			test[data->stringCounter] = '\0';
			data->stringComplete = 1;
			// stringComplete = true;
		}
	}
}


