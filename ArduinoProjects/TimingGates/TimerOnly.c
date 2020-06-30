// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define start_line_sensor 8
#define goal_line_sensor 9

#define green_led_on digitalWrite(10,HIGH)
#define green_led_off digitalWrite(10,LOW)

unsigned long starttime;
unsigned long elapsedtime;


void setup()
{
  Serial.begin(9600); 
  pinMode(8,INPUT);   //Start line ir sensor
  pinMode(10,OUTPUT); //green led
  pinMode(9,INPUT);   //goal line ir sensor 
  green_led_off;

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
}

void loop()
{
  int StartLineState = digitalRead(start_line_sensor);
  int EndLineState = digitalRead(goal_line_sensor);
  int green_led_state= 0;
  
  starttime = millis();           //millis time to start time
  
    while(StartLineState == 0){ //While start line is 0, blink green led 200ms intervals
    StartLineState = digitalRead(start_line_sensor);
            if(millis()-starttime>=200){
                green_led_state=!green_led_state; //switch green_led_state not
                digitalWrite(10,green_led_state);
          starttime=millis();     //Give starttime new millis value
        }
    }
    green_led_off;
    
    starttime=millis(); //Give new value for starttime, this is where real timer starts
    elapsedtime = millis();
    lcd.clear();
    lcd.setCursor(0, 0);
    while(EndLineState == 0){ // until endline brakes
        EndLineState = digitalRead(goal_line_sensor);
        
        green_led_on;         //hold green light on while on

        if(millis()-starttime>=1){
            Serial.println((millis()-elapsedtime)/1000.0);
            starttime=millis();
            
            lcd.setCursor(0, 0); 
            lcd.print((millis()-elapsedtime)/1000.0); //print running speed on lcd
        
        }
    }
    Serial.println("End time is:");                   //just to see it works
    Serial.print((millis()-elapsedtime)/1000.0);
    Serial.print(" seconds");
    
    lcd.setCursor(0, 0);                              //print elapsed time on lcd
    lcd.print((millis()-elapsedtime)/1000.0);
    lcd.setCursor(0, 1);
    lcd.print("seconds");
    

    starttime=0;
    green_led_state=0;
}
