#include "WaitingUserTask.h"
#include "Arduino.h"
#include "Sonar.h"
#include "Config.h"
#include "SelectionTask.h"
#include "ServoImpl.h"
#include "MsgService.h"
#include "Logger.h"

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
      logger.log("Waiting for user...");
    }
    break;
    case WAITING: {
      time = millis();
      if(time - startTime >= T_TIMEOUT || sonar->getDistance() >= 0.4){
        logger.log("Bye!");
        logger.log("Time: " + String(time - startTime) + " ms");
        logger.log("Distance: " + String(sonar->getDistance()) + " m");
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
      MsgService.sendMsg("cm:dl");
      selectionTask->setActive(true);
      userPresenceTask->setActive(true);
      selfCheckTask->setActive(true);
      this->setActive(false);
      state = INIT;
    }
  }
}
