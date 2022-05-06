#ifndef __DRINK__
#define __DRINK__
#include "Config.h"
#include "Arduino.h"

class Drink {
    public:
        
        virtual String getName() = 0;
        
        virtual int getQuantity() = 0;
        
        virtual void newProduct() = 0;

        virtual void refill() = 0;
};

#endif
