#ifndef __BOOT_TASK__
#define __BOOT_TASK__

#include "Task.h"
#include "Display.h"
#include <LiquidCrystal_I2C.h>
#include "Drink.h"
#include "Arduino.h"

class BootTask: public Task {

    public:
        BootTask(Display* lcd, Task* selectionTask, Task* userPresenceTask);
        void init();
        void tick();
        
    private:

        enum {WELCOME, INITIALIZATION, READY, COMPLETED} state;

        long time;
        long startTime;
        Display* lcd;
        int coffeeQuantity;
        int teaQuantity;
        int chocolateQuantity;
        Task* selectionTask;
        Task* userPresenceTask;
        Drink* coffee;
        Drink* chocolate;
        Drink* tea;

};

#endif
