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
  unsigned int thirst = 0;// max 100 . using eeprom 0
  unsigned int age = 0; //max 50. using eeprom 1
  unsigned int health = 0; // max 100. using eeprom 2
  unsigned int hunger = 0; // max 100. using eeprom 3
  unsigned int happy = 0; //max 100. using eeprom 4
  unsigned int money = 0; //max 999. Using eeprom.get it uses 5,6
  };
  
  struct kuri child;

  // Timing --------------------------------
  unsigned long startTime = 0;
  unsigned long elapsedTime = 0;
  unsigned long lastSecondMark=0;
  unsigned int seconds =0; //Using eeprom 7
  unsigned int minutes = 0; //Using eeprom 8
  unsigned int hours = 0; //Using eeprom 9
  unsigned int days = 0; //Using eeprom 10

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
  void clearMemory(){
    EEPROM.update(0, 100);//thirst
    EEPROM.update(1, 1);// age
    EEPROM.update(2, 100);//health
    EEPROM.update(3, 100);//hunger
    EEPROM.update(4, 100);//happy
    EEPROM.put(5, 0); //sets 5: 0x00 and 6: 0x00 money
    EEPROM.update(7, 0);// seconds
    EEPROM.update(8, 0);// minutes
    EEPROM.update(9, 0);// hours
    EEPROM.update(10, 0);// days
 
  }

  void loadStats(){
    child.thirst = EEPROM.read(0);
    child.age = EEPROM.read(1);
    child.health = EEPROM.read(2);
    child.hunger = EEPROM.read(3);
    child.happy = EEPROM.read(4);

    EEPROM.get(5,child.money);

    //Also Load time elapsed
    seconds = EEPROM.read(7);
    minutes = EEPROM.read(8);
    hours = EEPROM.read(9);
    days = EEPROM.read(10);
  }

//Debug------------------------------

  void printStats(){
    Serial.println("Stats!");
    Serial.print("Thirst: ");
    Serial.println(child.thirst);
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
        EEPROM.update(7, seconds);
        printStats();
      }

    if (seconds==60){ //updates minutes
      seconds=0;
      minutes++;
      EEPROM.update(8, minutes);
    }
    if (minutes==60){ //updates hours
      minutes=0;
      hours++;
      EEPROM.update(9, hours);
    }
    if (hours==24){ //updates days
      hours=0;
      days++;
      EEPROM.update(10, hours);
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