#include "SelfCheckTask.h"
#include "Arduino.h"
#include "ServoImpl.h"
#include "TempSensorTMP36.h"
#include "Config.h"
#include "Display.h"
#include "SelectionTask.h"
#include "UserPresenceTask.h"


extern Task* selectionTask;
extern Task* userPresenceTask;
extern ServoMotor* servo;

SelfCheckTask::SelfCheckTask(Display* plcd): lcd(plcd) {
  state = INIT;
}

void SelfCheckTask::init(){
  temp = new TempSensorTMP36(TEMP_PIN);
  pos = 0;
  delta = 1;
}

void SelfCheckTask::tick(){
  switch(state){
    case INIT: {
      Serial.println("SelfCheckTask");
      startTime = millis();
      state = WAITING;
    }
    break;
    case WAITING: {
     //Serial.println("SelfCheckTask2");
     actualTime = millis();
     Serial.println(actualTime - startTime);
     if(actualTime - startTime >= T_CHECK){
      lcd->getLcd().clear();
      lcd->print("Doing self test", 2, 1);
      selectionTask->setActive(false);
      userPresenceTask->setActive(false);
      startTime = millis();
      servo->on();
      state = CHECKING;
     }
    }
    break;
    case CHECKING: {
      actualTime = millis();
      if(actualTime - startTime <= 10000){
        while(pos < 180){
          servo->setPosition(pos);
          pos+=delta;
        }
        pos -= delta;
        delta = -delta;
        delay(500);
      } else {
        servo->off();
        selectionTask->setActive(true);
        userPresenceTask->setActive(true);
        state = INIT;
      }
    }
    break;
  }
    
}
