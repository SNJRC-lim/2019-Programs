//version 0.0

#include "Arduino.h"
#include "Servo.h"
#include "esc_control.h"

Servo esc;

void esc_setup(){
  esc.attach(9);   //esc PWM output = pin 9
  int level = 1000;
  esc.writeMicroseconds(level);
  delay(800);
}

void esc_speed_up(){
  for (int level = 1100; level <= 2000; level += 1) { //PWM幅を1100から2000まで徐々に上げる
    esc.writeMicroseconds(level);
    delay(3);
  }
  esc.writeMicroseconds(2000);
}

void esc_speed_down(){
  for (int level = 2000; level >= 1100; level -= 1) { //PWM幅を2000から1100まで徐々に下げる
    esc.writeMicroseconds(level);
    delay(3);
  }
}
