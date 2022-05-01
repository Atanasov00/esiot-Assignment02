#include "Scheduler.h"
#include "Display.h"
#include "BootTask.h"

Scheduler scheduler;

void setup() {
  scheduler.init(50);

  Display* lcd = new Display();
  Task* bootTask = new BootTask(lcd);

  //Add tasks here
  scheduler.addTask(bootTask);
}

void loop() {
  scheduler.schedule();
}
