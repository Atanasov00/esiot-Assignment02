#include "Coffee.h"
#include "Arduino.h"

Coffee::Coffee(){
  name = "Coffee";
}

String Coffee::getName(){
  return name;
}
