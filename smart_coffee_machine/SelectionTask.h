#ifndef __SELECTION_TASK__
#define __SELECTION_TASK__

#include "Task.h"
#include "Display.h"
#include <LiquidCrystal_I2C.h>

class SelectionTask: public Task {

    public:
        SelectionTask(Display* lcd);
        void init();
        void tick();

    private:
        enum {SELECTION, READY, SUGAR_SELECTION, START_MAKE, ASSISTANCE} state;
        enum {COFFEE = "Coffee", TEA = "Tea", CHOCOLATE = "Chocolate"} drinks;

        long time;
        long startTime;
        Display* lcd;
        int coffeeQuantity;
        int teaQuantity;
        int chocolateQuantity;
  
};

#endif
