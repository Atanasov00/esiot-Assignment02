#include "MakingTask.h"
#include "Arduino.h"
#include "ServoImpl.h"
#include "Config.h"
#include "Display.h"

MakingTask::MakingTask(Display* plcd): lcd(plcd) {
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
      lcd->getLcd().clear();
      lcd->print("Making " + String(drinkSelected), 2, 1);
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
      lcd->print("The " + String(drinkSelected) + " is ready", 2 ,1);
    }
  }
}
