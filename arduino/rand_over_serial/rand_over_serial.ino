#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SerialCommand.h>
#include <SoftwareSerial.h>

SoftwareSerial impSerial(8,7); // RX on 8, TX on 7 (we're going to ignore TX for now);

SerialCommand sCmd(impSerial);     // The SerialCommand object

// set up our OLED
// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  impSerial.begin(9600);
    
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();

  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("N",     handleNumber);  // Converts two arguments to integers and echos them back
  sCmd.addDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
  Serial.println("Ready");
  
  // text display setup
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(48,0);
  display.println("Ready");
  display.display();
}

void loop() {
  sCmd.readSerial();
}

void handleNumber() {
  char *arg;
  arg = sCmd.next();    // Get the next argument from the SerialCommand object buffer
  if (arg != NULL)      // As long as it existed, take it
  {
    Serial.println("Saw data");
    Serial.println(arg);
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print(arg);
    display.setCursor(48,0);
    display.setTextSize(1);
    display.println("is random");
    display.display();
  }

}

void unrecognized() {
  Serial.println("What?");
}
