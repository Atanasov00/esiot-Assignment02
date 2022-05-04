#ifndef __CHOCOLATE__
#define __CHOCOLATE__

#include "Drink.h"
#include "Arduino.h"

class Chocolate: public Drink {
    
    public:
        Chocolate();

        String getName();
        int getQuantity();
        void newProduct();

     private:
        int quantity;
        String name;
};

#endif
