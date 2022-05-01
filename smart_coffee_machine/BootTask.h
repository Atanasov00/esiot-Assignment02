#ifndef __BOOT_TASK__
#define __BOOT_TASK__

#include "Task.h"
#include "Display.h"

class BootTask: public Task {

    public:
        BootTask(Display* plcd);
        void tick();

    private:

        enum {WELCOME, INITIALIZATION, READY} state;

        Display* lcd;

}

#endif
