#include "Scheduler.h"
#include "Display.h"
#include "BootTask.h"

Scheduler scheduler;
extern int coffeeQuantity;
extern int teaQuantity;
extern int chocolateQuantity;

void setup() {
  scheduler.init(50);

  Serial.begin(9600);
  Display* lcd = new Display();
  
  Task* bootTask = new BootTask(lcd);
  bootTask->init();
  //Add tasks here
  scheduler.addTask(bootTask);
}

void loop() {
  scheduler.schedule();
}
