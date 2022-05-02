#include "Scheduler.h"
#include "Display.h"
#include "BootTask.h"
#include "SelectionTask.h"

Scheduler scheduler;

extern int coffeeQuantity;
extern int teaQuantity;
extern int chocolateQuantity;

void setup() {
  scheduler.init(50);

  Serial.begin(9600);
  Display* lcd = new Display();

  Task* selectionTask = new SelectionTask(lcd);
  selectionTask->init();
  
  
  Task* bootTask = new BootTask(lcd, selectionTask);
  bootTask->init();
  bootTask->setActive(true);
  
  //Add tasks here
  scheduler.addTask(bootTask);
  scheduler.addTask(selectionTask);
}

void loop() {
  scheduler.schedule();
}
