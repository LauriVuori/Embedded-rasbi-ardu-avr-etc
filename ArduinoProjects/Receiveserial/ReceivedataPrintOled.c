#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// arduino nano A4 (SDA), A5 (SCL)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char receivedChar;
bool  newData = false;
const int D12 = 12;
struct Commands {
    char command[256];
};

void setup() {
    
    Serial.begin(9600);

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }
    Serial.println("<Arduino is ready>");
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(D12, OUTPUT);
}

void loop() {
    // struct Commands command = {" "} 
    // char command[32];
    // receiveArray(command);
    // test();
    // recvOneChar();
    // showNewData();
    // testdrawchar(command);
    // newData = false;
}

void serialEvent() {
  Serial.println("Test");
}

// void test(){
//      if (Serial.available() > 0) {
//          Serial.available()
//         receivedChar = Serial.read();
//         newData = true;
//     }
// }
/**
 * @brief receive text arrays from serialcoms.
 * 
 */
// void receiveArray(char* command){
//     while (!Serial.available()) {
//         delay (10);
//         int i = 0;
//         int k = Serial.available(); 
//         while (k  > 0){     
//             char inchar = Serial.read();  //read one by one character    
//             command[i] = inchar;               
//             i++;    
//         if (k < 3) delay (10); //it gives possibility to collect more characters on stream    
//             k = Serial.available();     
//     }  
//         i++;
//     }
// }





/**
 * @brief print text on screen
 * @param char* command
 */
// void testdrawchar() {
//     display.clearDisplay();
//     //Size 3 approx 7 letters in one line
//     display.setTextSize(2);      // Normal 1:1 pixel scale
//     display.setTextColor(SSD1306_WHITE); // Draw white text
//     display.setCursor(0, 0);     // Start at top-left corner
//     display.cp437(true);         // Use full 256 char 'Code Page 437' font

//     display.write();
//     // Show the display buffer on the screen. You MUST call display() after
//     // drawing commands to make them visible on screen!
//     display.display();
//     delay(10);
//     // display.display() is NOT necessary after every single drawing command,
//     // unless that's what you want...rather, you can batch up a bunch of
//     // drawing operations and then update the screen all at once by calling
//     // display.display().
// }

// void recvOneChar() {
//     if (Serial.available() > 0) {
//         receivedChar = Serial.read();
//         newData = true;
//     }
// }

// void showNewData() {
//     if (newData == true) {
//         Serial.print("Received: ");
//         Serial.println(receivedChar);
//         testdrawchar(receivedChar);
//         digitalWrite(LED_BUILTIN, HIGH); 
//         digitalWrite(D12, HIGH);  
//         delay(10);                       
//         digitalWrite(LED_BUILTIN, LOW); 
//         digitalWrite(D12, LOW);     
//         delay(10);        
//         newData = false;
//     }
// }
