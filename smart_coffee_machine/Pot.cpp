#include "Pot.h"
#include "Arduino.h"

Potentiometer::(int pin){
    this->pin = pin;
}

float Potentiometer::getValue(){
    float val = analogRead(pin);
    int mappedValue =  map(val, 0, 1023, 0, 3);
    return mappedValue;
}