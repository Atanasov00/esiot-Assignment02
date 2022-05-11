#ifndef __LOGGER__
#define __LOGGER__

#include "Arduino.h"

class Logger {
  public:
    void log(String message);
};

extern Logger logger;

#endif
