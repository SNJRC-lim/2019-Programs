#ifndef VNH_H
#define VNH_H

#include <Arduino.h>

class VNH {
	private :
	    /*byte PWM_1 = 5;
      byte PWM_2 = 6;
      byte PWM_3 = 7;
      byte PWM_4 = 8;

      byte A_1 = 23;
      byte A_2 = 27;
      byte A_3 = 31;
      byte A_4 = 35;

      byte B_1 = 25;
      byte B_2 = 29;
      byte B_3 = 33;
      byte B_4 = 37;*/

      byte PWM_1 = 8;
      byte PWM_2 = 7;
      byte PWM_3 = 5;
      byte PWM_4 = 6;

      byte A_1 = 35;
      byte A_2 = 31;
      byte A_3 = 23;
      byte A_4 = 27;

      byte B_1 = 37;
      byte B_2 = 33;
      byte B_3 = 25;
      byte B_4 = 29;
      
    public :
      VNH();
      void attach_pin(byte Ai, byte Aii, byte Aiii, byte Aiiii, byte Bi, byte Bii, byte Biii, byte Biiii, byte PWMi, byte PWMii, byte PWMiii, byte PWMiiii);
      void init();
      void motor_1 (const int pwm_value);
      void motor_2 (const int pwm_value);
      void motor_3 (const int pwm_value);
      void motor_4 (const int pwm_value);

      void pwm (float angle1 , int percentage);

      void rotate (int speed);    
};

#endif
