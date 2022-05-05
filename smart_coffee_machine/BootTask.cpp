#include "BootTask.h"
#include "Arduino.h"
#include "Config.h"
#include "Coffee.h"
#include "Tea.h"
#include "Chocolate.h"

extern Task* selectionTask;
extern Task* userPresenceTask;

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
          Serial.println("ciao");
            lcd->initialize();
            lcd->print("Setting up...", 2, 1);
            startTime = millis();
            state = MESSAGE;
        }
        break;
        case MESSAGE: {
          time = millis();
          if(time - startTime >= 5000){
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
            Serial.println("BOOT");
            lcd->getLcd().clear();
            lcd->print("Ready", 2, 1);
            selectionTask->setActive(true);
            userPresenceTask->setActive(true);
            state = COMPLETED;
        }
        break;
        case COMPLETED: {
            this->setCompleted();
        }
        break;
    }
}
