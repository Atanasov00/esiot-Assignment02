#ifndef __COFFEE__
#define __COFFEE__

#include "Drink.h"
#include "Arduino.h"

class Coffee: public Drink {
    
    public:
        Coffee();

        String getName();
        int getQuantity();
        void newProduct();

     private:
        int quantity;
        String name;
};

#endif
