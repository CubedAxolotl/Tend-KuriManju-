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
