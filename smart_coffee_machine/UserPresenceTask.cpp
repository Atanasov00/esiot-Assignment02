#include "UserPresenceTask.h"
#include "Arduino.h"
#include "Config.h"
#include "Pir.h"
#include <avr/sleep.h>
#include <EnableInterrupt.h>

UserPresenceTask::UserPresenceTask(Display* plcd, Task* sTask): lcd(plcd), selectionTask(sTask) {
  state = IDLE;
  pir = new Pir(PIR_PIN);
}


void wakeUp(){
  
}

void UserPresenceTask:: init(){
  pir->calibrate();
}

void UserPresenceTask::tick(){
  switch(state){
    case IDLE: {
      time = millis();
      if(!pir->isDetected() && startTime - time >= 10000){
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
        lcd->getLcd().noDisplay();
        enableInterrupt(PIR_PIN, wakeUp, RISING);
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_enable();
        sleep_mode();
        Serial.println("Wake up");
        sleep_disable();
        disableInterrupt(PIR_PIN);
        lcd->getLcd().display();
        selectionTask->setActive(true);
        Serial.println("Going active");
        state = ACTIVE;
    }
  }
}
