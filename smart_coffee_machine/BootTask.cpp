#include "BootTask.h"
#include "Arduino.h"
#include "Config.h"

BootTask::BootTask(Display* plcd): lcd(plcd){
    state = WELCOME;
}

void BootTask::tick(){
    switch(state){
        case WELCOME: {
            lcd->print("Prova", 2, 1);
        }
        break;
    }
}
