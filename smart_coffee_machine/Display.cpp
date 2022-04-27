#include "Display.h"
#include "Arduino.h"
#include <LiquidCrystal_I2C.h> 


Display::Display(String sda, String scl){
    this->pinSda = sda;
    this->pinScl = scl;
    this->lcd = LiquidCrystal_I2C(0x27, 20, 4);
}

void Display::initialize(){
    lcd.init();
    lcd.backlight();
}

void Display::print(String msg, int col, int row){
    lcd.SetCursor(col, row);
    lcd.print(msg);
}