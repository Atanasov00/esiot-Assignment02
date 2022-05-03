#ifndef __USER_PRESENCE_TASK__
#define __USER_PRESENCE_TASK__

#include "Task.h"
#include "Display.h"
#include <LiquidCrystal_I2C.h>
#include "Pir.h"

class UserPresenceTask: public Task {

    public:
        UserPresenceTask(Display* lcd, Task* selectionTask);
        void init();
        void tick();

    private:
        enum {ACTIVE, IDLE, SLEEP} state;


        unsigned long startTime;
        unsigned long time;
        Display* lcd;
        Pir* pir;
        Task* selectionTask;
  
};

#endif
