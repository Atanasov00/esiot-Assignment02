#include "BootTask.h"
#include "Arduino.h"
#include "Config.h"

BootTask::BootTask(Display* plcd, Task* sTask): lcd(plcd), selectionTask(sTask){
    state = WELCOME;
}

void BootTask::init(){
  startTime = millis();
}

void BootTask::tick(){
    switch(state){
        case WELCOME: {
            lcd->initialize();
            lcd->print("Setting up...", 2, 1);
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
            lcd->getLcd().clear();
            lcd->print("Ready", 2, 1);
            selectionTask->setActive(true);
            //Serial.println(selectionTask->isActive());
            state = COMPLETED;
        }
        break;
        case COMPLETED: {
            this->setCompleted();
        }
        break;
    }
}
