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
     Serial.println("SelfCheckTask2");
     actualTime = millis();
     if(actualTime - startTime >= 10000){
      lcd->getLcd().clear();
      lcd->print("Doing self test", 2, 1);
      servo->on();
      servo->setPosition(0);
      delay(1000);
      servo->off();
      startTime = millis();
      state = CHECKING;
     }
    }
    break;
    case CHECKING: {
      actualTime = millis();
      if(actualTime - startTime <= 10000){
        servo->on();
        for(int i = 0; i < 180; i++){
          servo->setPosition(pos);
          pos+=delta;
        }
        servo->off();
        pos -= delta;
        delta = -delta;
        delay(1000);
      }
    }
    break;
  }
    
}
