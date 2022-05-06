#include "Coffee.h"
#include "Arduino.h"
#include "Config.h"

Coffee::Coffee(){
  name = "Coffee";
  quantity = N_MAX_ITEMS;
}

String Coffee::getName(){
  return name;
}

int Coffee::getQuantity(){
  return quantity;
}

void Coffee::newProduct(){
  if(quantity>0){
    quantity--;
  }
}

void Coffee::refill(){
  quantity = N_MAX_ITEMS;
}
