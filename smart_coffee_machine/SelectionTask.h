#ifndef __SELECTION_TASK__
#define __SELECTION_TASK__

#include "Task.h"
#include "Display.h"
#include <LiquidCrystal_I2C.h>
#include "Button.h"
#include "Pot.h"
#include "Config.h"
#include "Drink.h"
#include "BootTask.h"
#include "Arduino.h"

class SelectionTask: public Task {

    public:
        SelectionTask(Display* lcd, Task* makingTask, Task* userPresenceTask);
        void init();
        void tick();        

    private:

        enum {SELECTION, READY, WAITING, SUGAR_SELECTION, START_MAKE, ASSISTANCE} state;        

        void bUpPressed();
        void bDownPressed();
        void checkIfAnyButtonPressed();
        void checkIfPotChanged();
        void checkIfMakingPressed();
        void potChanged();

        long time;
        long actualTime;
        long startTime;
        Display* lcd;
        int coffeeQuantity;
        int teaQuantity;
        int chocolateQuantity;
        Button* bUp;
        Button* bDown;
        Button* bMake;
        Potentiometer* pot;
        int currentSelection;
        int sugarValue;
        Task* makingTask;
        Task* userPresenceTask;  
        
};

#endif
