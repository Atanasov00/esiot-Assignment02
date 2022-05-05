#ifndef __MAKING_TASK__
#define __MAKING_TASK__

#include "ServoImpl.h"
#include "Display.h"
#include <LiquidCrystal_I2C.h>
#include "Task.h"
#include "SelectionTask.h"

class MakingTask: public Task {

    public:
        MakingTask(Display* lcd);
        void init();
        void tick();

   private:

       enum {INITIALIZATION, MAKING, READY} state;

       Display* lcd;
       ServoMotor* servo;
       unsigned long startTime;
       unsigned long progress;
       int pos; 
       

};

#endif
