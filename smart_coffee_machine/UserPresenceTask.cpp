#include "UserPresenceTask.h"
#include "Arduino.h"
#include "Config.h"
#include "Pir.h"

#include <avr/sleep.h>

extern Task* selectionTask;

void wakeUp(){}

UserPresenceTask::UserPresenceTask(Display* plcd): lcd(plcd) {
  state = IDLE;
  pir = new Pir(PIR_PIN);
}


void UserPresenceTask:: init(){
  //pir->calibrate();
  startTime = millis();
}

void UserPresenceTask::tick(){
  switch(state){
    case IDLE: {
      time = millis();
      if(!pir->isDetected() && time - startTime >= T_IDLE){
        Serial.println("Going to sleep");
        state = SLEEP;
      } else if(pir->isDetected()){
        Serial.println("Switch to active");
        state = ACTIVE;
      }
    }
    break;
    case ACTIVE: {
      if(!pir->isDetected()){
        Serial.println("Going to idle");
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
        Serial.println("Wake up");
        sleep_disable();
        detachInterrupt(PIR_PIN);
        lcd->getLcd().backlight();
        selectionTask->setActive(true);
        Serial.println("Going active");
        state = ACTIVE;
    }
    break;
  }
}
