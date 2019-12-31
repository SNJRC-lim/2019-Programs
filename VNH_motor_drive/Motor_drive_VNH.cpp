//version 0.2

#include "Motor_drive_VNH.h"
#include "Arduino.h"

void VNH_pwm(float angle1 , int percentage){
  //float rad_x = (angle1 - 45) / (180 / PI);
  //float X = cos(rad_x);

  //float rad_y = (angle1 - 45) / (180 / PI);
  //float Y = sin(rad_y);
  float angle2;
  
  if((-3/4)*PI<angle1<=-PI){
	  angle2 = PI/4 - angle1;
  }
  else angle2 = angle1 - PI/4;
  
  float x = cos(angle2);
  float y = sin(angle2);
  
  float a = max(abs(x),abs(y));
  
  float X = x * (1/a);
  float Y = y * (1/a);
  
  int V1 = -X*255*percentage/100; 
  int V2 = -Y*255*percentage/100;
  int V3 = X*255*percentage/100;
  int V4 = Y*255*percentage/100;

  VNH1(V1);
  VNH2(V2);
  VNH3(V3);
  VNH4(V4);
}

void VNH1 (int pwm_value) {

  if (pwm_value > 0) {
    digitalWrite (A_1, 1);
    digitalWrite (B_1, 0);
    analogWrite  (PWM_1, abs(pwm_value));
  }
  else if (pwm_value < 0) {
    digitalWrite (A_1, 0);
    digitalWrite (B_1, 1);
    analogWrite  (PWM_1, abs(pwm_value));
  }
  else {
    digitalWrite (A_1, 0);
    digitalWrite (B_1, 0);
    analogWrite  (PWM_1, 0);
  }
}

void VNH2 (int pwm_value) {

  if (pwm_value > 0) {
    digitalWrite (A_2, 1);
    digitalWrite (B_2, 0);
    analogWrite  (PWM_2, abs(pwm_value));
  }
  else if (pwm_value < 0) {
    digitalWrite (A_2, 0);
    digitalWrite (B_2, 1);
    analogWrite  (PWM_2, abs(pwm_value));
  }
  else {
    digitalWrite (A_2, 0);
    digitalWrite (B_2, 0);
    analogWrite  (PWM_2, 0);
  }
}

void VNH3 (int pwm_value) {

  if (pwm_value > 0) {
    digitalWrite (A_3, 1);
    digitalWrite (B_3, 0);
    analogWrite  (PWM_3, abs(pwm_value));
  }
  else if (pwm_value < 0) {
    digitalWrite (A_3, 0);
    digitalWrite (B_3, 1);
    analogWrite  (PWM_3, abs(pwm_value));
  }
  else {
    digitalWrite (A_3, 0);
    digitalWrite (B_3, 0);
    analogWrite  (PWM_3, 0);
  }
}

void VNH4 (int pwm_value) {

  if (pwm_value > 0) {
    digitalWrite (A_4, 1);
    digitalWrite (B_4, 0);
    analogWrite  (PWM_4, abs(pwm_value));
  }
  else if (pwm_value < 0) {
    digitalWrite (A_4, 0);
    digitalWrite (B_4, 1);
    analogWrite  (PWM_4, abs(pwm_value));
  }
  else {
    digitalWrite (A_4, 0);
    digitalWrite (B_4, 0);
    analogWrite  (PWM_4, 0);
  }
}

void VNH_rotate(int speed){
	int pwm_value  = 255*speed/100;
	VNH1(pwm_value);
	VNH2(pwm_value);
	VNH3(pwm_value);
	VNH4(pwm_value);
}
