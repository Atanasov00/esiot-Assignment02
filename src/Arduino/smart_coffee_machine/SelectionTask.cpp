#include "SelectionTask.h"
#include "Arduino.h"
#include "ButtonImpl.h"
#include "Config.h"
#include "Pot.h"
#include "MsgService.h"

extern Drink* coffee;
extern Drink* tea;
extern Drink* chocolate;

String currentDrink;

extern Task* makingTask;
extern Task* userPresenceTask;
extern Task* selfCheckTask;

SelectionTask::SelectionTask(Display* plcd): lcd(plcd){
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
  Serial.println("You're selecting a " + currentDrink);
}

void SelectionTask::checkIfPotChanged(){
  if(pot->getValue() != sugarValue){
    potChanged();
    state = SUGAR_SELECTION;
  }
}

void SelectionTask::potChanged(){
  sugarValue = pot->getValue();
  Serial.println("You set the sugar level to " + String(sugarValue));
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
  Serial.println("You're selecting a " + currentDrink);
}

void SelectionTask::checkIfMakingPressed(){
  if(bMake->isPressed()){
    if(currentDrink.equals("Coffee") && coffee->getQuantity() > 0){
      Serial.println("Making a coffee...");
      state = START_MAKE;
      coffee->newProduct();
      MsgService.sendMsg("cm:wk");
      MsgService.sendMsg("cm:cfq:"+String(coffee->getQuantity()));
    } else if (currentDrink.equals("Coffee") && coffee->getQuantity() == 0){
      Serial.println("Coffee is empty");
      state = PRODUCT_EMPTY;
      lcd->getLcd().clear();
      lcd->print("Coffee is empty", 1, 1);
      time = millis();
    } else if(currentDrink.equals("Tea") && tea->getQuantity() > 0){
      Serial.println("Making a tea...");
      state = START_MAKE;
      tea->newProduct();
      MsgService.sendMsg("cm:wk");
      MsgService.sendMsg("cm:teq:"+String(tea->getQuantity()));
    } else if (currentDrink.equals("Tea") && tea->getQuantity() == 0) {
      Serial.println("Tea is empty");
      state = PRODUCT_EMPTY;
      lcd->getLcd().clear();
      lcd->print("Tea is empty", 1, 1);
      time = millis();
    } else if(currentDrink.equals("Chocolate") && chocolate->getQuantity() > 0) {
      Serial.println("Making a chocolate...");
      state = START_MAKE;
      chocolate->newProduct();
      MsgService.sendMsg("cm:wk");
      MsgService.sendMsg("cm:chq:"+String(chocolate->getQuantity()));
    } else {
      Serial.println("Chocolate is empty");
      state = PRODUCT_EMPTY;
      lcd->getLcd().clear();
      lcd->print("Chocolate is empty", 1, 1);
      time = millis();
    }
  }
}

bool SelectionTask::allProductsEmpty(){
  return coffee->getQuantity() == 0 && tea->getQuantity() == 0 && chocolate->getQuantity() == 0;
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
  Serial.println("ready");
  switch(state){
    case READY:{
      if(allProductsEmpty()){
        MsgService.sendMsg("cm:ss");
        MsgService.sendMsg("cm:em");
        state = ASSISTANCE;
      } else {
        Serial.println("Ready");
        lcd->getLcd().clear();
        lcd->print("Ready", 2, 1);
        checkIfAnyButtonPressed();
        checkIfPotChanged();
        checkIfMakingPressed();
      }
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
      Serial.println("Coffee: " + String(coffee->getQuantity()));
      Serial.println("Tea: " + String(tea->getQuantity()));
      Serial.println("Chocolate: " + String(chocolate->getQuantity()));
      userPresenceTask->setActive(false);
      makingTask->setActive(true);
      selfCheckTask->setActive(false);
      this->setActive(false);
      state = READY;
    }
    break;
    case PRODUCT_EMPTY:{
      actualTime = millis();
      if(actualTime - time >= T_TIMEOUT){
        state = READY;
      }
    }
    break;
    case ASSISTANCE:
      lcd->getLcd().clear();
      lcd->print("Assistance Required.", 0, 1);
      if (MsgService.isMsgAvailable()){
      Msg* msg = MsgService.receiveMsg();    
      if (msg->getContent() == "10"){
         coffee->refill();
         tea->refill();
         chocolate->refill();
         state = READY;
         MsgService.sendMsg("cm:dl");
         MsgService.sendMsg("cm:cfq:"+String(coffee->getQuantity()));
         MsgService.sendMsg("cm:teq:"+String(tea->getQuantity()));
         MsgService.sendMsg("cm:chq:"+String(chocolate->getQuantity()));
       } 
    /* NOT TO FORGET: msg deallocation */
    delete msg;
  }
    break;
  }
}
