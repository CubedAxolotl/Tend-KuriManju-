#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>

#define SCREEN_WIDTH 128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
/* _    __      __               
  | |  / /___ _/ /_  _____  _____
  | | / / __ `/ / / / / _ \/ ___/
  | |/ / /_/ / / /_/ /  __(__  ) 
  |___/\__,_/_/\__,_/\___/____/  */

  // character-------------------------------
   struct kuri {
    unsigned int age; //EEPROM 0,1
    unsigned int health; //EEPROM 2,3
    unsigned int hunger; //EEPROM 4,5
    unsigned int happy; //EEPROM 6,7 -heheh funny number
    unsigned int money; //EEPROM 8,9
    bool sick;  //EEPROM 10
    bool dirty; ////EEPROM 11
  };
  struct kuri child;

  // Timing --------------------------------
  unsigned long startTime = 0;
  unsigned long elapsedTime = 0;
  unsigned long lastSecondMark=0;
  unsigned int seconds =0; 
  unsigned int minutes = 0; 
  unsigned int hours = 0; 
  unsigned int days = 0;

  //Gameplay
  

  // Logic------------------------------
  int buttonPins[3] = {2,3,4};
  int currentState[3];
  //_--------------------------------------------------_




/* __                   _   _                 
  / _|                 | | (_)                
  | |_ _   _ _ __   ___| |_ _  ___  _ __  ___ 
  |  _| | | | '_ \ / __| __| |/ _ \| '_ \/ __|
  | | | |_| | | | | (__| |_| | (_) | | | \__ \
  |_|  \__,_|_| |_|\___|\__|_|\___/|_| |_|___/*/

  //Memory-------------------------------

  void loadStats(){
    EEPROM.get(0,child);
  }

  
  void clearMemory(){
    struct kuri empty = {1, 100, 100, 100, 0, false, false};
    EEPROM.put(0, empty);
  }

//Debug------------------------------

  void printStats(){
    Serial.println("Stats!");
    Serial.print("Age: ");
    Serial.println(child.age);
    Serial.print("Health: ");
    Serial.println(child.health);
    Serial.print("Hunger: ");
    Serial.println(child.hunger);
    Serial.print("Happy: ");
    Serial.println(child.happy);
    Serial.print("Money: ");
    Serial.println(child.money);
    Serial.println("---------------------------------------------");
    Serial.println("Total Time Elapsed!");
    Serial.print("Days: ");
    Serial.println(days);
    Serial.print("Hours: ");
    Serial.println(hours);
    Serial.print("Minutes: ");
    Serial.println(minutes);
    Serial.print("Seconds: ");
    Serial.println(seconds);
    Serial.println("---------------------------------------------");
    
  }

  //Time-----------------------------------------

  void clk(){ //Keeps track of sec, min, hrs, and days. 
    unsigned long now = millis(); //Millis returns miliseconds passed

    if (now - lastSecondMark >= 1000.0){ //Updates seconds
        lastSecondMark += 1000; 
        seconds++;
        printStats();
      }

    if (seconds==60){ //updates minutes
      seconds=0;
      minutes++;
    }
    if (minutes==60){ //updates hours
      minutes=0;
      hours++;
    }
    if (hours==24){ //updates days
      hours=0;
      days++;
    }
  }


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
    // initialize OLED display with I2C address 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("failed to start SSD1306 OLED"));
    while (1);
  }

  delay(2000);         // wait two seconds for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);         // set text size
  oled.setTextColor(WHITE);    // set text color
  oled.setCursor(0, 2);       // set position to display (x,y)
  oled.println("Robotronix"); // set text
  oled.display();  
  randomSeed(analogRead(A0));
  
  if (digitalRead(buttonPins[1]) == LOW) { //if center button is pressed during boot, it resets mem
    Serial.println("Button pressed during startup, clearing memory...");
    clearMemory();
    }

  loadStats();

  startTime = millis();

  
}

void loop() {
  clk(); //Keeps track of sec, min, hrs, and days. 
  
  

}
