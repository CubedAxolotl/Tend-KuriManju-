/*The following character is owned by Nagano and assosiate companies. 
  Tend KuriManju is a tamagotchi like game. 
  Gameplay 
    Stage: Kuri will age over time. This is the durations
        - egg: 0-1 hrs ('E')
        - baby: 24hhrs ('B')
        - teen: 48h hrs ('T')
        - Adult: 7 days ('A')
        -Old Man Kurimanju: 10 days. Kurimaju will suffer a heart attack the 20th day due to his unhealthy drinking habbits ('O')

    Age: Age is the measure of ammount of days lived. 

    Health: Kuris health will drop for the following reasons
        - He is Unhappy AND Hungry (both equal 0)
        - He has more than three poops.
        - He is sick

    Hunger: Kurimanjus hunger decreases based on age
        -Egg: every 5 min(✓)
        -Baby: every 10 min(✓)
        -Child: every 30 min
        -Teen: every 45 min
        -Adult: every hr
        -Old Man Kuri: Every hr

    Happyness Kurimanjus Happyness decreases based on age
        -Egg: every 5 min(✓)
        -Baby: every 10 min(✓)
        -Child: every 20 min
        -Teen: every 30 min
        -Adult: every 40h min 
        -Old Man Kuri: 50 minr
    Sick: Sickness brings down health based on age. It is calculated by 
          (1+2*number of poops)/n, n changes value depending on age. Baby n=25, Child n=75, Adult n=100, Old Man n=76.
          Sickness is rolled
        -Egg: egg can't get sick(✓)
        -Baby: every 5 min
        -Child: every 10 min
        -Teen: every 15 min
        -Adult: every 20
        -Old Man Kuri: 15

    POOP: Kurimanjus poops based on age, 1 poop is 1 point with a max of 3
        -Egg: egg don't poop(✓)
        -Baby: every 5 min poopin(✓)
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
    char stage;//EEPROM 0,1
    unsigned int age; //EEPROM 2,3
    unsigned int health; //EEPROM 4,5
    unsigned int hunger; //EEPROM 6,7 -heheh funny number
    unsigned int happy; //EEPROM 8,9
    unsigned int money; //EEPROM 10,11
    bool isSick;  //EEPROM 12,13//outdated
    unsigned int poopPoints; //EEPROM 14,15
  };

  struct kuri child;

  // Timing --------------------------------
  //used for clk()
    unsigned long startTime = 0;
    unsigned long elapsedTime = 0;
    unsigned long lastSecondMark=0;
    unsigned int seconds =55; 
    unsigned int minutes = 9; 
    unsigned int hours = 0; 
    unsigned int days = 0;

  // Used for Decay
    bool decayedHunger = false;
    bool decayedHappyness = false;
    bool hasPooped = false;
    bool rolledSick= false;

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



  


  //Time-----------------------------------------



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
 decay();

}