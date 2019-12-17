//version 0.0

#ifndef Motor_drive_VNH_h
#define Motor_drive_VNH_h

#include "Arduino.h"

const byte PWM_1 = 5;
const byte PWM_2 = 6;
const byte PWM_3 = 7;
const byte PWM_4 = 8;

const byte A_1 = 22;
const byte A_2 = 23;
const byte A_3 = 24;
const byte A_4 = 25;

const byte B_1 = 26;
const byte B_2 = 27;
const byte B_3 = 28;
const byte B_4 = 29;

void VNH1 (const int pwm_value);
void VNH2 (const int pwm_value);
void VNH3 (const int pwm_value);
void VNH4 (const int pwm_value);

void VNH_pwm (float angle1 , int percentage);

#endif
