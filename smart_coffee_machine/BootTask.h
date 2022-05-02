#ifndef __BOOT_TASK__
#define __BOOT_TASK__

#include "Task.h"
#include "Display.h"
#include <LiquidCrystal_I2C.h>

class BootTask: public Task {

    public:
        BootTask(Display* plcd);
        void init();
        void tick();
        
    private:

        enum {WELCOME, INITIALIZATION, READY} state;

        long time;
        long startTime;
        Display* lcd;
        int coffeeQuantity;
        int teaQuantity;
        int chocolateQuantity;

};

#endif
