char test[15];
int b = 0;
bool stringComplete = false;
struct serialData{
	int stringComplete;
};

void receive(struct serialData * data);

void setup() {
	// initialize serial:
	Serial.begin(9600);
	
}

void loop() {
	struct serialData data = {0};
	int q = 0;
	receive(&data);
	if (stringComplete == true) {
		// data.stringComplete = 0;
		stringComplete = false;
		Serial.println("STRING::");
		Serial.println(test);
		b = 0;
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
		test[b] = inChar;
		b++;
		if (inChar == '\n') {
			test[b] = '\0';
			// data->stringComplete = 0;
			stringComplete = true;
		}
	}
}


