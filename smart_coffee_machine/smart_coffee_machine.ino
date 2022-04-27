#include "Scheduler.h"

Scheduler scheduler;

void setup() {
  scheduler.init(50);

  //Add tasks here
}

void loop() {
  scheduler.schedule();
}
