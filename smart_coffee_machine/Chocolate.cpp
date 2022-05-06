#include "Chocolate.h"
#include "Arduino.h"
#include "Config.h"

Chocolate::Chocolate(){
  name = "Chocolate";
  quantity = N_MAX_ITEMS;
}

String Chocolate::getName(){
  return name;
}

int Chocolate::getQuantity(){
  return quantity;
}

void Chocolate::newProduct(){
  if(quantity>0){
    quantity--;
  }
}

void Chocolate::refill(){
  quantity = N_MAX_ITEMS;
}
