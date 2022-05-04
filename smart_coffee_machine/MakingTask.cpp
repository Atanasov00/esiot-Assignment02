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
    startTime = millis();
}

void MakingTask::tick() {
  switch(state) {
    case INITIALIZATION: {
      Serial.println(String(currentDrink));
      Serial.println("MAKING TASK");
      lcd->getLcd().clear();
      lcd->print("Making a coffee", 2, 1);
      servo->on();
      state = MAKING;
    }
    break;
    case MAKING: {
      progress = millis() - startTime;
      if (progress <= T_MAKING){
        pos = map(progress, 0, T_MAKING, 0, 180);
        servo->setPosition(pos);
      } else{
        state = READY;
      }
    }
    break;
    case READY: {
      lcd->getLcd().clear();
      lcd->print("The coffee is ready", 2 ,1);
    }
  }
}
