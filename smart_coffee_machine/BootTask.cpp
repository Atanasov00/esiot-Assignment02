#include "BootTask.h"
#include "Arduino.h"
#include "Config.h"
#include "Coffee.h"
#include "Tea.h"
#include "Chocolate.h"

BootTask::BootTask(Display* plcd, Task* sTask, Task* pTask): lcd(plcd), selectionTask(sTask), userPresenceTask(pTask){
    state = WELCOME;
}

void BootTask::init(){
  startTime = millis();
  chocolate = new Chocolate();
  tea = new Tea();
  coffee = new Coffee();

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
            Serial.println("BOOT");
            userPresenceTask->setActive(true);
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
