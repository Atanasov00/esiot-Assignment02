#include "Scheduler.h"
#include "Display.h"
#include "BootTask.h"
#include "SelectionTask.h"
#include "UserPresenceTask.h"

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

  Task* userPresenceTask = new UserPresenceTask(lcd, selectionTask);
  userPresenceTask->init();

  Task* bootTask = new BootTask(lcd, selectionTask, userPresenceTask);
  bootTask->init();
  bootTask->setActive(true);
  
  //Add tasks here
  scheduler.addTask(bootTask);
  scheduler.addTask(selectionTask);
  scheduler.addTask(userPresenceTask);
}

void loop() {
  scheduler.schedule();
}
