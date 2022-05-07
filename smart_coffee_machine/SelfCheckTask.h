#ifndef __SELF_CHECK_TASK__
#define __SELF_CHECK_TASK__

#include "Task.h"
#include "Display.h"
#include <LiquidCrystal_I2C.h>
#include "Servo.h"
#include "TempSensor.h"

class SelfCheckTask: public Task {

  public:
    
    SelfCheckTask(Display* lcd);
    void init();
    void tick();

  private:

    enum {INIT, WAITING, CHECKING, ASSISTANCE} state;

    Display* lcd;
    unsigned long startTime;
    unsigned long actualTime;
    TempSensor* temp;
    int pos;
    int delta;
    float temperature;
};

#endif
