//25.6.2020
char receivedChar;
boolean newData = false;

void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    delay(250);
    recvOneChar();
    showNewData();
}

void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        newData = true;
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in ... ");
        Serial.println(receivedChar);
          digitalWrite(LED_BUILTIN, HIGH);  
          delay(1000);                       
          digitalWrite(LED_BUILTIN, LOW);    
          delay(1000);        
        newData = false;
    }
}

