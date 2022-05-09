#ifndef __LCD__
#define __LCD__
#include <LiquidCrystal_I2C.h> 

class Display{

    public:
        Display();

        void initialize();
        void print(String msg, int col, int row);
        LiquidCrystal_I2C getLcd();

    private:
        LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);
};

#endif
