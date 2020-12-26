#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

bool stringComplete = false;
char test[15];
int b = 0;


void setup() {
  // initialize serial:
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    stringComplete = false;
    Serial.println("STRING::");
    testdrawchar(test);
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


void testdrawchar(char print[]) {
    display.clearDisplay();
    //Size 3 approx 7 letters in one line
    display.setTextSize(2);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.cp437(true);         // Use full 256 char 'Code Page 437' font

    display.write(print);
    // Show the display buffer on the screen. You MUST call display() after
    // drawing commands to make them visible on screen!
    display.display();
    delay(2000);
    display.clearDisplay();
    // display.display() is NOT necessary after every single drawing command,
    // unless that's what you want...rather, you can batch up a bunch of
    // drawing operations and then update the screen all at once by calling
    // display.display().
}