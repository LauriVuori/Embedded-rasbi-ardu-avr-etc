//25.6.2020

void setup() {
    Serial.begin(9600);
    pinMode(2, OUTPUT);
    Serial.write("Ready");
}


void loop() {
    Serial.write("a");
    digitalWrite(2, HIGH);
    delay(1000);
    digitalWrite(2, LOW);
    delay(1000);
}