#include "MakingTask.h"
#include "Arduino.h"
#include "ServoImpl.h"
#include "Config.h"
#include "Display.h"
#include "SelectionTask.h"

extern String currentDrink;

MakingTask::MakingTask(Display* plcd, Task* sTask): lcd(plcd), selectionTask(sTask){
  state = INITIALIZATION;
}

void MakingTask:: init() {
    servo = new ServoImpl(SERVO_PIN);
    pos = 0;
    servo->on();
    servo->setPosition(0);
}

void MakingTask::tick() {
  switch(state) {
    case INITIALIZATION: {
      /*Serial.println("|--"+String(currentDrink));
      Serial.println("MAKING TASK");*/
      lcd->getLcd().clear();
      lcd->print("Making a " + String(currentDrink), 1, 1);
      servo->on();
      state = MAKING;
      startTime = millis();
    }
    break;
    case MAKING: {
      progress = millis() - startTime;
      if (progress <= T_MAKING){
        pos = map(progress, 0, T_MAKING, 0, 180);
        servo->setPosition(pos);
      } else{
        servo->off();
        state = READY;
      }
    }
    break;
    case READY: {
      lcd->getLcd().clear();
      lcd->print("The "+ String(currentDrink), 1 , 1);
      lcd->print("is ready.", 1, 2);
      this->setCompleted();
    }
  }
}
