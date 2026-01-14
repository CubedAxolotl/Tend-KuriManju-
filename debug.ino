   void loadStats(){
    EEPROM.get(0,child);
  }
 
  void clearMemory(){
    struct kuri empty = {'B',1, 100, 9, 100, 0, 0, 0};
    EEPROM.put(0, empty);
  }

//Debug------------------------------

  void printStats(){
    Serial.println("Stats!");
    Serial.print("Stage: ");
    Serial.println(child.stage);
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
    Serial.print("Poops: ");
    Serial.println(child.poopPoints);
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