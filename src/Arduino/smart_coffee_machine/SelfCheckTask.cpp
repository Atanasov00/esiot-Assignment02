#include "SelfCheckTask.h"
#include "Arduino.h"
#include "ServoImpl.h"
#include "TempSensorTMP36.h"
#include "Config.h"
#include "Display.h"
#include "SelectionTask.h"
#include "UserPresenceTask.h"
#include "MsgService.h"

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
      //Serial.println("SelfCheckTask");
      startTime = millis();
      state = WAITING;
    }
    break;
    case WAITING: {
     //Serial.println("SelfCheckTask2");
     actualTime = millis();
     //Serial.println(actualTime - startTime);
     if(actualTime - startTime >= T_CHECK){
      Serial.println("Machine is doing a self-test...");
      lcd->getLcd().clear();
      lcd->print("Doing self test", 2, 1);
      MsgService.sendMsg("cm:wk");
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
        MsgService.sendMsg("cm:sf");
        temperature = temp->getTemperature();
        Serial.println("Temperature is " + String(temperature) + "°C");
        if(temperature < TEMP_MIN || temperature > TEMP_MAX) {
          Serial.println("Entering assistance mode (machine temperature is out of bounds..)");
          lcd->getLcd().clear();
          lcd->print("Assistance Required.", 0, 1);
          MsgService.sendMsg("cm:ss");
          MsgService.sendMsg("cm:tm");
          state = ASSISTANCE;
        } else {
          MsgService.sendMsg("cm:dl");
          selectionTask->setActive(true);
          userPresenceTask->setActive(true);
          state = INIT;
        }
      }
    }
    break;
    case ASSISTANCE:
      if (MsgService.isMsgAvailable()){
        Msg* msg = MsgService.receiveMsg();    
        if (msg->getContent() == "ok"){
           MsgService.sendMsg("cm:dl");
           selectionTask->setActive(true);
           userPresenceTask->setActive(true);
           state = INIT;
         }
        /* NOT TO FORGET: msg deallocation */
        delete msg;
    }
    break;
  }
}
