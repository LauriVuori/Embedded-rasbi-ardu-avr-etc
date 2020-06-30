//include low power libary
#include <avr/sleep.h>

void wakeUpNow()        // here the interrupt is handled after wakeup
{
}

// include the library code:
#include <LiquidCrystal.h>
//https://www.arduino.cc/en/Tutorial/HelloWorld


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 6);

#define start_line_sensor 8
#define goal_line_sensor 9

#define green_led_on digitalWrite(10,HIGH)
#define green_led_off digitalWrite(10,LOW)

#define lcd_backlight_on digitalWrite(7,HIGH)
#define lcd_backlight_off digitalWrite(7,LOW)
unsigned long starttime;
unsigned long elapsedtime;




void setup()
{
  Serial.begin(9600); 
  pinMode(8,INPUT);   //Start line ir sensor
  pinMode(10,OUTPUT); //green led
  pinMode(7,OUTPUT); // lcd backlight pin +v5, to turn it on and off
  pinMode(9,INPUT);   //goal line ir sensor 
  green_led_off;

    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.

        //pinMode(wakePin, INPUT_PULLUP);
        attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
                                            // wakeUpNow when pin 2 gets LOW
    

}

void sleepNow()              // Function to turn arduino to sleep
{
    digitalWrite(7, LOW);    //turn lcd-backlight off
    
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // sleep mode is set here
    sleep_enable();                        // enables the sleep bit in the mcucr register
    attachInterrupt(0,wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
    sleep_mode();            // Device goes to sleep                     
                             
    sleep_disable();         // DOES NOT DO ANYTHING??? first thing after waking from sleep:disable sleep...        

    detachInterrupt(0);      // disables interrupt 0 on pin 2 so the
}

void loop()
{
  int StartLineState = digitalRead(start_line_sensor);  //startline variable to determine state
  int EndLineState = digitalRead(goal_line_sensor);     // goalline variable to determine state
  int green_led_state= 0;
  
  starttime = millis();           //millis time to start time
  
    //////////////////////////////////////////////////////////////////////////////////////
    while(StartLineState == 1){ //While start line is 0, blink green led 200ms intervals
    StartLineState = digitalRead(start_line_sensor);
            if(millis()-starttime>=200){
                green_led_state=!green_led_state; //switch green_led_state not
                digitalWrite(10,green_led_state);     
          starttime=millis();     //Give starttime new millis value
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////// Might be useless atm, with sleep function, does not stay in loop. Just on start up
    
    
    digitalWrite(7, HIGH);        //turn lcd-backlight on, in sleepNow function we will turn it off
   
    starttime=millis(); //Give new value for starttime, this is where real timer starts
    elapsedtime = millis();
    
    lcd.clear();            //Clear everything on lcd screen
    lcd.setCursor(0, 0);    //Set lcd cursor on first block
    
    while(EndLineState == 0){ // until endline brakes
        EndLineState = digitalRead(goal_line_sensor);
        
        green_led_on;         //hold green light on while on
        /////////////////////////////////////////////////////////////////////////
        if(millis()-starttime>=1){
            Serial.println((millis()-elapsedtime)/1000.0);
            starttime=millis();
            
            lcd.setCursor(0, 0); 
            lcd.print((millis()-elapsedtime)/1000.0); //print running speed on lcd
        
        }
        ////////////////////////////////////////////////////////////////// Might be useless, better to turn lcd on just for showing numbers
    }
    Serial.println("End time is:");                   //TEST,DELETE
    Serial.print((millis()-elapsedtime)/1000.0);      //TEST,DELETE
    Serial.print(" seconds");                         //TEST,DELETE
    
    lcd.setCursor(0, 0);                              //print elapsed time on lcd
    lcd.print((millis()-elapsedtime)/1000.0);
    lcd.setCursor(0, 1);
    lcd.print("seconds");

    starttime=0;
    green_led_state=0;
    green_led_off;
    
    delay(2000);                //set time before ardu goes to sleep, 2-10sec??
    Serial.print("Sleeping");   //TEST,DELETE
    delay(250);
    sleepNow();              // go to sleepNow function-> sleep untill interrupt
}