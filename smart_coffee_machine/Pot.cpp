#include "Pot.h"
#include "Arduino.h"

Potentiometer::Potentiometer(int pin){
    this->pin = pin;
}

int Potentiometer::getValue(){
    float val = analogRead(pin);
    int mappedValue =  map(val, 0, 1023, 0, 5);
    return mappedValue;
}
