bool stringComplete = false;
char test[15];
int b = 0;
void setup() {
  // initialize serial:
  Serial.begin(9600);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
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

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    test[b] = inChar;
    b++;
    if (inChar == '\n') {
      test[b] = '\0';
      stringComplete = true;
    }
  }
}
