#include "Motor_drive_VNH.h" //set motor driver pin && VNH1,VNH2,VNH3.VNH4 function

void setup() {
  pinMode(PWM_1, OUTPUT);
  pinMode(PWM_2, OUTPUT);
  pinMode(PWM_3, OUTPUT);
  pinMode(PWM_4, OUTPUT);
  pinMode(A_1, OUTPUT);
  pinMode(A_2, OUTPUT);
  pinMode(A_3, OUTPUT);
  pinMode(A_4, OUTPUT);
  pinMode(B_1, OUTPUT);
  pinMode(B_2, OUTPUT);
  pinMode(B_3, OUTPUT);
  pinMode(B_4, OUTPUT);

}

void loop() {
  
  VNH_pwm(180);

}


