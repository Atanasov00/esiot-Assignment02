#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int pEcho, int pTrig): echoPin(pEcho), trigPin(pTrig){
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  //Temperature at 20°C by default
  temperature = 20;
}

void Sonar::setTemperature(float temp) {
  temperature = temp;
}

float Sonar::getSoundSpeed() {
  return 331.5+0.6*temperature;
}

float Sonar::getDistance(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  float pulse = pulseIn(echoPin, HIGH);
  if(pulse == 0) {
    return -1;
  } else {
    float t = pulse/1000.0/1000.0/2;
    float d = t*getSoundSpeed();
    return d;
  }
}
