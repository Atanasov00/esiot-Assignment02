#include "Scheduler.h"
#include "Display.h"
#include "BootTask.h"
#include "SelectionTask.h"
#include "UserPresenceTask.h"
#include "MakingTask.h"
#include "WaitingUserTask.h"

Scheduler scheduler;

Task* selectionTask;
Task* makingTask;
Task* userPresenceTask;
Task* bootTask; 
Task* waitingUserTask;

void setup() {
  scheduler.init(50);

  Serial.begin(9600);
  Display* lcd = new Display();

  bootTask = new BootTask(lcd);
  bootTask->init();
  bootTask->setActive(true);

  selectionTask = new SelectionTask(lcd);
  selectionTask->init();
  
  userPresenceTask = new UserPresenceTask(lcd);
  userPresenceTask->init();

  makingTask = new MakingTask(lcd);
  makingTask->init();

  waitingUserTask = new WaitingUserTask();
  waitingUserTask->init();

  //Add tasks here
  scheduler.addTask(bootTask);
  scheduler.addTask(selectionTask);
  scheduler.addTask(userPresenceTask);
  scheduler.addTask(makingTask);
  scheduler.addTask(waitingUserTask);
}

void loop() {
  scheduler.schedule();
}
