#include "SelectionTask.h"
#include "Arduino.h"
#include "ButtonImpl.h"
#include "Config.h"
#include "Pot.h"
#include <EnableInterrupt.h>

SelectionTask::SelectionTask(Display* plcd):lcd(plcd){
  state = READY;
}

void SelectionTask::bUpPressed(){
  switch(currentDrink){
    case Coffee:{
      currentDrink = Tea;
    }
      
     break;
     case Tea:{
      currentDrink = Chocolate;
    }
     break;
     case Chocolate:{
      currentDrink = Coffee;
    }
     break;
  }
}

void SelectionTask::bDownPressed(){ 
  switch(currentDrink){
    case Coffee:{
      currentDrink = Chocolate;
    }
     break;
     case Tea:{
      currentDrink = Coffee;
    }
     break;
     case Chocolate:{
      currentDrink = Tea;
    }
     break;
  }
}

void SelectionTask::init(){
  bUp = new ButtonImpl(BUP_PIN);
  bDown = new ButtonImpl(BDOWN_PIN);
  bMake = new ButtonImpl(BMAKE_PIN);
  pot = new Potentiometer(POT_PIN);
  startTime = millis();
  currentDrink = Coffee;
}

void SelectionTask::tick(){
  switch(state){
    case READY:{
      Serial.println("Task 2");
      lcd->getLcd().clear();
      lcd->print("Ready", 2, 1);
      if(bUp->isPressed()){
        bUpPressed();
        state = SELECTION;
      } else if(bDown->isPressed()){
        bDownPressed();
        state = SELECTION;
      }
    }
    break;
    case SELECTION:{
      lcd->getLcd().clear();
      lcd->print(String(currentDrink), 2, 1);
      Serial.println("Selecting");
      time = millis();
      state = WAITING;
    }
    break;
    case WAITING:{
      actualTime = millis();
      if(actualTime - time >= T_TIMEOUT){
        state = READY;
      }
    }
    break;
  }
}
