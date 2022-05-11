#include "UserPresenceTask.h"
#include "Arduino.h"
#include "Config.h"
#include "Pir.h"
#include "Logger.h"

#include <avr/sleep.h>

extern Task* selectionTask;

void wakeUp(){}

UserPresenceTask::UserPresenceTask(Display* plcd): lcd(plcd) {
  state = IDLE;
  pir = new Pir(PIR_PIN);
}


void UserPresenceTask:: init(){
  pir->calibrate();
  startTime = millis();
}

void UserPresenceTask::tick(){
  switch(state){
    case IDLE: {
      time = millis();
      if(!pir->isDetected() && time - startTime >= T_IDLE){
        logger.log("Going to sleep");
        state = SLEEP;
      } else if(pir->isDetected()){
        logger.log("Switch to active");
        state = ACTIVE;
      }
    }
    break;
    case ACTIVE: {
      if(!pir->isDetected()){
        logger.log("Going to idle");
        state = IDLE;
        startTime = millis();
      }
    }
    break;
    case SLEEP: {
        selectionTask->setActive(false);
        lcd->getLcd().clear();
        lcd->getLcd().noBacklight();
        attachInterrupt(digitalPinToInterrupt(PIR_PIN), wakeUp, RISING);
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        logger.log("Wake up");
        sleep_disable();
        detachInterrupt(PIR_PIN);
        lcd->getLcd().backlight();
        selectionTask->setActive(true);
        logger.log("Going active");
        state = ACTIVE;
    }
    break;
  }
}
