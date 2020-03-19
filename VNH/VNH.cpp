#include "VNH.h"
#include "Arduino.h"

VNH::VNH (){
	init();
}

void VNH::init(){
  pinMode(PWM_1, OUTPUT); //pin 5
  pinMode(PWM_2, OUTPUT); //pin 6
  pinMode(PWM_3, OUTPUT); //pin 7
  pinMode(PWM_4, OUTPUT); //pin 8
  pinMode(A_1, OUTPUT);   //pin 23
  pinMode(A_2, OUTPUT);   //pin 27
  pinMode(A_3, OUTPUT);   //pin 31
  pinMode(A_4, OUTPUT);   //pin 35
  pinMode(B_1, OUTPUT);   //pin 25
  pinMode(B_2, OUTPUT);   //pin 29
  pinMode(B_3, OUTPUT);   //pin 33
  pinMode(B_4, OUTPUT);   //pin 37
}

void VNH::attach_pin(byte Ai, byte Aii, byte Aiii, byte Aiiii, byte Bi, byte Bii, byte Biii, byte Biiii, byte PWMi, byte PWMii, byte PWMiii, byte PWMiiii){
	PWM_1 = PWMi;
	PWM_2 = PWMii;
	PWM_3 = PWMiii;
	PWM_4 = PWMiiii;
	
	A_1 = Ai;
	A_2 = Aii;
	A_3 = Aiii;
	A_4 = Aiiii;
	
	B_1 = Bi;
	B_2 = Bii;
	B_3 = Biii;
	B_4 = Biiii;
}

void VNH::pwm(float angle1 , int percentage){
  float angle2;
  
  if((-3 * PI / 4 < angle1) && (angle1 <= -PI)){
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

  motor_1(V1);
  motor_2(V2);
  motor_3(V3);
  motor_4(V4);
}

void VNH::motor_1 (int pwm_value) {

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

void VNH::motor_2 (int pwm_value) {

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

void VNH::motor_3 (int pwm_value) {

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

void VNH::motor_4 (int pwm_value) {

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

void VNH::rotate(int speed){
  int pwm_value  = 255*speed/100;
  motor_1(pwm_value);
  motor_2(pwm_value);
  motor_3(pwm_value);
  motor_4(pwm_value);
}
