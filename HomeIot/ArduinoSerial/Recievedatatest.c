//25.6.2020
char receivedChar;
boolean newData = false;
const int D12 = 12;

void setup() {
    Serial.begin(9600);
    Serial.println("<Arduino is ready>");
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(D12, OUTPUT);
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
        Serial.print("Received: ");
        Serial.println(receivedChar);
          digitalWrite(LED_BUILTIN, HIGH); 
          digitalWrite(D12, HIGH);  
          delay(10);                       
          digitalWrite(LED_BUILTIN, LOW); 
          digitalWrite(D12, LOW);     
          delay(10);        
        newData = false;
    }
}

