/*The following character is owned by Nagano and assosiate companies. 
  Tend KuriManju is a tomogachii like game. 
  Gameplay 
    Stage: Kuri will age over time. This is the durations
        - egg: 0-1 hrs
        - baby: 24hhrs 
        - teen: 48h hrs 
        - Adult: 7 days
        -Old Man Kurimanju: 10 days. Kurimaju will suffer a heart attack the 20th day due to his unhealthy drinking habbits

    Age: Age is the measure of ammount of days lived. 

    Health: Kuris health will drop for the following reasons
        - He is Unhappy AND Hungry (both equal 0)
        - He has more than three poops.
        - He is sick

    Hunger: Kurimanjus hunger decreases based on age
        -Egg: egg dont eat
        -Baby: every 10 min
        -Child: every 30 min
        -Teen: every 45 min
        -Adult: every hr
        -Old Man Kuri: Every hr

    Happyness Kurimanjus Happyness decreases based on age
        -Egg: egg can't experience
        -Baby: every 10 min
        -Child: every 20 min
        -Teen: every 30 min
        -Adult: every 40h min
        -Old Man Kuri: 50 minr
    Sick: Sickness brings down health based on age
        -Egg: egg can't get sick
        -Baby: every 5 min
        -Child: every 10 min
        -Teen: every 15 min
        -Adult: every 20
        -Old Man Kuri: 15

    POOP/dirty: Kurimanjus poops based on age, 1 poop is 25 points of dirty
        -Egg: egg don't poop
        -Baby: every 5 min it has a 50/50 of poopin
        -All other stages: Every 30 min it has a 50/50 to poop

  Tabs:

    Shop: you can shop for the following supplies
        -Tacos: Restores hunger
        -Beer: Restores hunger, restores happiness, but brings down health
        -VapoRab: reduces sickness (doesn't cure it
        -Medicine: medicine has a 50/50 chance at curing kuri. It takes effect 30 minutes after applied. 

    Save: Saves game! Do this before turning off!

    Shower: Deletes poops

    Games!: You can play Flappybird, slot machine, black jack, pong! 
*/

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
    unsigned int sick;  //EEPROM 10,11
    unsigned int dirty; ////EEPROM 12,13
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
    struct kuri empty = {1, 100, 100, 100, 0, 0, 0};
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
    Serial.print("Sick: ");
    Serial.println(child.sick);
    Serial.print("Dirty: ");
    Serial.println(child.dirty);
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