#ifndef __WAITING_USER_TASK__
#define __WAITING_USER_TASK__

#include "Sonar.h"
#include "Task.h"
#include "Servo.h"

class WaitingUserTask: public Task {
    
    public:
        WaitingUserTask();
        void init();
        void tick();

    private: 

        enum {INIT, WAITING, RESET, DONE} state;
        
        Sonar* sonar;
        ServoMotor* servo;
        unsigned long startTime;
        unsigned long time;
        
};

#endif
