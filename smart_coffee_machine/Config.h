#ifndef __CONFIG__
#define __CONFIG__

#define BUP_PIN 5
#define BDOWN_PIN 3
#define BMAKE_PIN 4

#define POT_PIN A0

#define TEMP_PIN A1

#define DISPLAY_SDA_PIN A4
#define DISPLAY_SCL_PIN A5

#define PIR_PIN 2

#define SONAR_TRIG_PIN 12
#define SONAR_ECHO_PIN 13

#define SERVO_PIN 9

//Time expressed in ms

#define T_MAKING 10000
#define T_TIMEOUT 5000
#define T_IDLE 60000
#define T_CHECK 180000

//Temperature expressed in °C
#define TEMP_MIN 17
#define TEMP_MAX 24

#define N_MAX_ITEMS 1

#endif
