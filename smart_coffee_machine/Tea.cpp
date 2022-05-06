#include "Tea.h"
#include "Arduino.h"
#include "Config.h"

Tea::Tea(){
  name = "Tea";
  quantity = N_MAX_ITEMS;
}

String Tea::getName(){
  return name;
}

int Tea::getQuantity(){
  return quantity;
}

void Tea::newProduct(){
  if(quantity>0){
    quantity--;
  }
}

void Tea::refill(){
  quantity = N_MAX_ITEMS;
}
