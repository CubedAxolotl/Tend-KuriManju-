void decay(){
  int deduction=0;
  int addition=0;
  switch (child.stage){
    case 'E':
      if (decayedHunger== false && minutes%5==0){ //goes down every 5 min
        decayedHunger=true;
        deduction = random(20,51); // makes deduction a number between 20-50

        if (child.hunger >= deduction){ //this if else is if deduction is bigger than the current stat, to prevent overflow. 
          child.hunger -= deduction;
        } 
        else if (child.hunger < deduction){
          child.hunger = 0;
        }

      } 
      else if (decayedHunger==true && minutes%5!=0){
        decayedHunger=false;
      }


      if (decayedHappyness== false && minutes%5==0){//goes down every 5 min
        decayedHappyness=true;
        deduction = random(20,51); //it goes down by a random number between 20-50;

        if (child.happy >= deduction){ //this if else is if deduction is bigger than the current stat, to prevent overflow. 
          child.happy -= deduction;
        } 
        else if (child.happy < deduction){
          child.happy = 0;
        }
      } 
      else if (decayedHappyness==true && minutes%5!=0){
        decayedHappyness=false;
      }
    break;
    case 'B':
      //decays Hunger
      if (decayedHunger== false && minutes%10==0){ //goes down every 10 min
        decayedHunger=true;
        deduction = random(20,31); // makes deduction a number between 20-30

        if (child.hunger >= deduction){ //this if else is if deduction is bigger than the current stat, to prevent overflow. 
          child.hunger -= deduction;
        } 
        else if (child.hunger < deduction){
          child.hunger = 0;
        }

      } 
      else if (decayedHunger==true && minutes%10!=0){
        decayedHunger=false;
      }

      //decays Happyness
      if (decayedHappyness== false && minutes%10==0){//goes down every 10 min
        decayedHappyness=true;
        deduction = random(20,31); //it goes down by a random number between 20-30;

        if (child.happy >= deduction){ //this if else is if deduction is bigger than the current stat, to prevent overflow. 
          child.happy -= deduction;
        } 
        else if (child.happy < deduction){
          child.happy = 0;
        }
      } 
      else if (decayedHappyness==true && minutes%10!=0){
        decayedHappyness=false;
      }
      //updates poops
      if (minutes%5==0 && hasPooped == false){
        
        if (child.poopPoints !=3)
        hasPooped = true;
        child.poopPoints +=1; //adds one poop
      }
      else if (minutes%5!=0 && hasPooped == true){
        hasPooped = false;
      }
      //Rolls for sickness 
      int k= 1+ 2*child.poopPoints;
      if (minutes%2==0 && rolledSick== false ){
        rolledSick = true;
        if (child.isSick==false && random(50)<k){
          child.isSick = true;
          Serial.print("Child has the flu!");
        }
        
      }
      else if (minutes%2!=0&&rolledSick == true){
        rolledSick = false;
      }



    break;
}

}