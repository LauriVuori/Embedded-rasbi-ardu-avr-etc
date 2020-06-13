#include <Servo.h>

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;

int potpin1 = A0;
int potpin2 = A1;
int potpin3 = A2;
int potpin4 = A3;

int newval1, oldval1 = 0;
int newval2, oldval2 = 0;
int newval3, oldval3 = 0;
int newval4, oldval4 = 0;
int newval5, oldval5 = 0;

void setup()
{
	Serial.begin(9600); 
	myservo1.attach(2); 
	myservo2.attach(3);
	myservo3.attach(4);
	myservo4.attach(5);
}

void loop()
{
	newval1 = analogRead(potpin1);           
	newval1 = map(newval1, 0, 1023, 0, 179);
	if (newval1 < (oldval1-2) || newval1 > (oldval1+2)){
		myservo1.write(newval1);
		oldval1=newval1;
	}
	
	newval2 = analogRead(potpin2);
	newval2 = map(newval2, 0, 1023, 0, 179);
	if (newval2 < (oldval2-2) || newval2 > (oldval2+2)){ 
		myservo2.write(newval2);
		Serial.print(newval2);
		Serial.print("b,");
		oldval2=newval2;
	}
	
	newval3 = analogRead(potpin3);           
	newval3 = map(newval3, 0, 1023, 0, 179);
	if (newval1 < (oldval1-2) || newval3 > (oldval3+2)){ 
		myservo1.write(newval3);
		oldval3=newval3;
	}
	
	newval4 = analogRead(potpin4);           
	newval4 = map(newval4, 0, 1023, 0, 179);
	if (newval1 < (oldval1-2) || newval4 > (oldval4+2)){ 
		myservo1.write(newval4);
		oldval4=newval4;
	}
	
	
	delay(50);
}
