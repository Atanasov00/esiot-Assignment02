#ifndef __SONAR__
#define __SONAR__

#include "ProximitySensor.h"

class Sonar: ProximitySensor {

  public:

  Sonar(int echoPin, int trigPin);
  float getDistance();
  void setTemperature(float temperature);

  private:
  
  const float vs = 331.5+0.6*20; //Sound speed at 20°C
  float getSoundSpeed();

  float temperature;
  int echoPin;
  int trigPin;
  long maxTime;
};

#endif
