#include "Scheduler.h"
#include "Display.h"
#include "BootTask.h"
#include "SelectionTask.h"
#include "UserPresenceTask.h"
#include "MakingTask.h"

Scheduler scheduler;

Task* selectionTask;
Task* makingTask;
Task* userPresenceTask;
Task* bootTask; 

void setup() {
  scheduler.init(50);

  Serial.begin(9600);
  Display* lcd = new Display();

  makingTask = new MakingTask(lcd, selectionTask);
  makingTask->init();
  
  selectionTask = new SelectionTask(lcd, makingTask, userPresenceTask);
  selectionTask->init();

  userPresenceTask = new UserPresenceTask(lcd, selectionTask);
  userPresenceTask->init();

  bootTask = new BootTask(lcd, selectionTask, userPresenceTask);
  bootTask->init();
  bootTask->setActive(true);

  //Add tasks here
  scheduler.addTask(bootTask);
  scheduler.addTask(selectionTask);
  scheduler.addTask(userPresenceTask);
  scheduler.addTask(makingTask);
}

void loop() {
  scheduler.schedule();
}
