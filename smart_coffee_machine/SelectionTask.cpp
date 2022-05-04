#include "SelectionTask.h"
#include "Arduino.h"
#include "ButtonImpl.h"
#include "Config.h"
#include "Pot.h"

extern Drink* coffee;
extern Drink* tea;
extern Drink* chocolate;

String currentDrink;

SelectionTask::SelectionTask(Display* plcd, Task* mTask, Task* pTask): lcd(plcd), makingTask(mTask), userPresenceTask(pTask) {
  state = READY;
}

void SelectionTask::checkIfAnyButtonPressed(){
  if(bUp->isPressed()){
    bUpPressed();
    state = SELECTION;
  } else if(bDown->isPressed()){
    bDownPressed();
    state = SELECTION;
  }
}

void SelectionTask::bUpPressed(){
  switch(currentSelection){
    case 0:{
      currentDrink = "Tea";
      currentSelection = 1;
    }
      
     break;
     case 1:{
      currentDrink = "Chocolate";
      currentSelection = 2;
    }
     break;
     case 2:{
      currentDrink = "Coffee";
      currentSelection = 0;
    }
     break;
  }
}

void SelectionTask::checkIfPotChanged(){
  if(pot->getValue() != sugarValue){
    potChanged();
    state = SUGAR_SELECTION;
  }
}

void SelectionTask::potChanged(){
  sugarValue = pot->getValue();
}

void SelectionTask::bDownPressed(){ 
  switch(currentSelection){
    case 0:{
      currentDrink = "Chocolate";
      currentSelection = 2;
    }
     break;
     case 1:{
      currentDrink = "Coffee";
      currentSelection = 0;
    }
     break;
     case 2:{
      currentDrink = "Tea";
      currentSelection = 1;
    }
     break;
  }
}

void SelectionTask::checkIfMakingPressed(){
  if(bMake->isPressed()){
    state = START_MAKE;
    Serial.println("Start making");
  }
}

void SelectionTask::init(){
  bUp = new ButtonImpl(BUP_PIN);
  bDown = new ButtonImpl(BDOWN_PIN);
  bMake = new ButtonImpl(BMAKE_PIN);
  pot = new Potentiometer(POT_PIN);
  startTime = millis();
  currentSelection = 0;
  currentDrink = "Coffee";
  sugarValue = pot->getValue();
}

void SelectionTask::tick(){
  switch(state){
    case READY:{
      //Serial.println("ready");
      lcd->getLcd().clear();
      lcd->print("Ready", 2, 1);
      checkIfAnyButtonPressed();
      checkIfPotChanged();
      checkIfMakingPressed();
    }
    break;
    case SELECTION:{
      lcd->getLcd().clear();
      lcd->print(String(currentDrink), 2, 1);
      time = millis();
      state = WAITING;
    }
    break;
    case SUGAR_SELECTION:{
      lcd->getLcd().clear();
      lcd->print("Sugar level: " + String(sugarValue), 2, 1);
      time = millis();
      state = WAITING;
    }
    break;
    case WAITING:{
      actualTime = millis();
      if(actualTime - time >= T_TIMEOUT){
        state = READY;
      }
      checkIfAnyButtonPressed();
      checkIfPotChanged();
      checkIfMakingPressed();
    }
    break;
    case START_MAKE: {
      //userPresenceTask->setActive(false);
      makingTask->setActive(true);
      this->setCompleted();
    }
    break;
    case ASSISTANCE:
    break;
  }
}
