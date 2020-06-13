#define SWITCH 11

void setup() {
pinMode(SWITCH, OUTPUT);
Serial.begin(9600);
}
void loop() {

}

void serialEvent(){
    if (Serial.available() > 0){          
        int incomingByte= Serial.parseInt();
        Serial.print("I received: ");
        Serial.print(incomingByte);
        if (incomingByte == 1 ){
            digitalWrite(SWITCH, HIGH);
            delay(500);
            digitalWrite(SWITCH, LOW);
        }
    }
}
