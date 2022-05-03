#include "UserPresenceTask.h"
#include "Arduino.h"
#include "Config.h"
#include "Pir.h"
#include <EnableInterrupt.h>
#include <avr/sleep.h>


UserPresenceTask::UserPresenceTask(Display* plcd): lcd(plcd){
  state = IDLE;
  pir = new Pir(PIR_PIN);
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
      
    }
  }
}
