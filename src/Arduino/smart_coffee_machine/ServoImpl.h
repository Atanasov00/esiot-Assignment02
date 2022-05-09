#ifndef __SERVO_IMPL__
#define __SERVO_IMPL__

#include "Arduino.h"
#include "ServoTimer2.h"
#include "Servo.h"

class ServoImpl: public ServoMotor {

  public:

  ServoImpl(int pin);
  void on();
  void setPosition(int angle);
  void off();

  private:

  int pin;
  ServoTimer2 motor;
};

#endif
