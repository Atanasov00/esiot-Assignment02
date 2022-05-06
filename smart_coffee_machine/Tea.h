#ifndef __TEA__
#define __TEA__

#include "Drink.h"
#include "Arduino.h"

class Tea: public Drink {
    
    public:
        Tea();

        String getName();
        int getQuantity();
        void newProduct();
        void refill();

     private:
        int quantity;
        String name;
};

#endif
