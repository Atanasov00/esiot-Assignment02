#ifndef __LCD__
#define __LCD__
#include <LiquidCrystal_I2C.h> 

class Display{

    public:
        Display(String sda, String scl);

        void initialize();
        void print(String msg, int col, int row);

    private:
        String pinSda, pinScl;
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
};

#endif
