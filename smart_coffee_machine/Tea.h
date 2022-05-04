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

     private:
        int quantity;
        String name;
};

#endif
