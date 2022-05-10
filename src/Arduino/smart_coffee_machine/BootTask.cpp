#include "BootTask.h"
#include "Arduino.h"
#include "Config.h"
#include "Coffee.h"
#include "Tea.h"
#include "Chocolate.h"
#include "SelfCheckTask.h"
#include "MsgService.h"

extern Task* selectionTask;
extern Task* userPresenceTask;
extern Task* selfCheckTask;

Drink* coffee;
Drink* chocolate;
Drink* tea;

BootTask::BootTask(Display* plcd): lcd(plcd){
    state = WELCOME;
}

void BootTask::init(){
  chocolate = new Chocolate();
  tea = new Tea();
  coffee = new Coffee();
}

void BootTask::tick(){
    switch(state){
        case WELCOME: {
            //MsgService.init();
            Serial.println("Welcome to Smart-Coffee machine.");
            lcd->initialize();
            lcd->print("Setting up...", 2, 1);
            startTime = millis();
            state = MESSAGE;
        }
        break;
        case MESSAGE: {
          timeExp = millis();
          if(timeExp - startTime >= 2000){
            state = INITIALIZATION;
          }
        }
        break;
        case INITIALIZATION: {
            coffeeQuantity = N_MAX_ITEMS;
            teaQuantity = N_MAX_ITEMS;
            chocolateQuantity = N_MAX_ITEMS;
            state = READY;
        }
        break;
        case READY: {
            MsgService.sendMsg("cm:dl");
            MsgService.sendMsg("cm:cfq:"+String(coffee->getQuantity()));
            MsgService.sendMsg("cm:teq:"+String(tea->getQuantity()));
            MsgService.sendMsg("cm:chq:"+String(chocolate->getQuantity()));
            lcd->getLcd().clear();
            lcd->print("Ready", 2, 1);
            selectionTask->setActive(true);
            userPresenceTask->setActive(true);
            selfCheckTask->setActive(true);
            //Serial.println(selfCheckTask->isActive());
            state = COMPLETED;
        }
        break;
        case COMPLETED: {
            this->setCompleted();
        }
        break;
    }
}
