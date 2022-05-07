#include "WaitingUserTask.h"
#include "Arduino.h"
#include "Sonar.h"
#include "Config.h"
#include "SelectionTask.h"
#include "ServoImpl.h"

extern Task* selectionTask;
extern Task* userPresenceTask;
extern Task* selfCheckTask;

WaitingUserTask::WaitingUserTask(){
  state =  INIT; 
}

void WaitingUserTask::init(){
  startTime = 0;
  time = 0;
  sonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN);
  servo = new ServoImpl(SERVO_PIN);
}

void WaitingUserTask::tick(){
  switch(state) {
    case INIT: {
      startTime = millis();
      state = WAITING;
      Serial.println("WAITING");
    }
    break;
    case WAITING: {
      time = millis();
      //Serial.println(sonar->getDistance());
      if(time - startTime >= T_TIMEOUT || sonar->getDistance() >= 0.4){
        Serial.println("BYE!");
        Serial.println(time - startTime);
        Serial.println(sonar->getDistance());
        state = RESET;
      }
    }
    break;
    case RESET: {
      servo->on();
      servo->setPosition(0);
      delay(1000);
      servo->off();
      state = DONE;
    }
    break;
    case DONE: {
      selectionTask->setActive(true);
      userPresenceTask->setActive(true);
      selfCheckTask->setActive(true);
      this->setActive(false);
      state = INIT;
    }
  }
}
