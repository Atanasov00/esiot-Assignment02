#ifndef __DRINK__
#define __DRINK__
#include "Config.h"
#include "Arduino.h"

class Drink {

    private:
    
        int quantity = N_MAX_ITEMS;

    public:
        
        virtual String getName() = 0;
        
        int getQuantity(){
          return quantity;
        }
        
        void newProduct() {
          quantity--;
        }

        void refill(){
          quantity = N_MAX_ITEMS;
        }
};

#endif
