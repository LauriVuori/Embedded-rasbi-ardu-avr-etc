
#include <Servo.h>
String readString, servo1, servo2, servo3;
Servo myservo1, myservo2, myservo3;


void setup() {
  Serial.begin(9600);
  myservo1.attach(6);
  myservo2.attach(7);
  myservo3.attach(8);
  myservo1.write(20);
  myservo2.write(20);
  myservo3.write(20);

}

void loop() {
Serial.flush();
}

void serialEvent(){
        if (Serial.available()){
            readString = Serial.readString();
            Serial.print("String: ");
            Serial.print(readString); //see what was received
            
            // 050 050 050 == 050050050
            servo1 = readString.substring(0, 3); //get the first 3four characters
            servo2 = readString.substring(3, 6); 
            servo3 = readString.substring(6, 9);
            int s1 = servo1.toInt(); 
            int s2 = servo2.toInt();
            int s3 = servo3.toInt();
            if (s1 >= 175 || s1 <= 25){
                s1 = 25;
            }

            if (s2 >= 175 || s2 <= 25){
                s2 = 25;
            }

            if (s3 >= 175 || s3 <= 25){
                s3 = 25;
            }

            Serial.println("");
            Serial.print("Servo1: ");
            Serial.print(s1);
            Serial.println("");
            Serial.print("Servo2: ");
            Serial.print(s2);
            Serial.println("");
            Serial.print("Servo3: ");
            Serial.print(s3);
            Serial.println("");
            myservo1.write(s1);
            myservo2.write(s2);
            myservo3.write(s3);
            delay(1000);
        }

}