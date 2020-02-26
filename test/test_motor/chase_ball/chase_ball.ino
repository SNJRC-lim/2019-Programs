//version 1.5
///library files///
#include <FlexiTimer2.h>
#include <avr/io.h>
///my header files///
#include "Motor_drive_VNH.h" //set motor driver pin && VNH_pwm,VNH1,VNH2,VNH3.VNH4 function
#include "White_line.h"      //use it by flexitimer2 (timer interrapt)
#include "pixy2_get_color_info.h" //set start_pixy2 , get angle orange , get angle yellow , get angle blue
#include "esc_control.h"   //operating esc(brushless motor) , speed up or speed down
#include "communication.h" //set function get_robot_angle
///goal color///
bool goal = true; //true : yellow , false : blue
///game options///
#define start_soccer_game   //use this when real game
#define angle_adjustment
///angles///
//in this program,all angle use RAD//
float angle_orange;
float angle_blue;
float angle_yellow;
float angle; //where you want to go
float robot_angle;  //get from arduino pro mini , robots yaw degree
///distance///
float dist_orange;
float dist_blue;
float dist_yellow;
float dist_IR [4]; //get from arduino pro mini , [forward,back,right,left]
///start button///
const int start_button = 48;
///solenoid FET///
const int sloenoid_FET = 47;
///ball caught sensor///
const int ball_sensor = 49;
//////VNH_pwm
void setup() {
  ///pin setup here///
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
  pinMode(start_button, INPUT_PULLUP); //start button = pin 48
  pinMode(sloenoid_FET, OUTPUT); //sloenoid_FET = pin 47
  pinMode(ball_sensor, INPUT); //ball caught sensor = pin 49
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  ///change PWM freqency///
  TCCR3B = (TCCR3B & 0b11111000) | 1;
  TCCR4B = (TCCR4B & 0b11111000) | 1;
  ///set timer interrupt///
  //FlexiTimer2::set(1, 1.0 / 7500, White_line);
  //FlexiTimer2::start();
  ///pixy setup///
  start_pixy2();
  ///esc setup///
  esc_setup();
  ///wait start///
  #ifdef start_soccer_game
    while (digitalRead(start_button) == 1);
  #endif
}
void loop(){
  angle_orange = -1 * get_angle_orange();
  if((-1*PI <= angle_orange) && (angle_orange <= PI)){
    ///there is the orange ball in 0~PI///
    if((0 <= angle_orange) && (angle_orange <= PI)){
      if((4*PI/9 <= angle_orange) && (angle_orange <= 5*PI/9)){
        VNH_pwm(PI/2,50);
      }
      if((0 <= angle_orange) && (angle_orange < 4*PI/9)){
        while((0 <= angle_orange) && (angle_orange < 4*PI/9)){
          VNH_pwm(0,50);
          angle_orange = -1*get_angle_orange();
        } 
      }
      if((5*PI/9 < angle_orange ) && (angle_orange <= PI)){
        while((5*PI/9 < angle_orange) && (angle_orange <= PI)){
          VNH_pwm(PI,50);
  　　        angle_orange = -1*get_angle_orange();
        }
      }
    }
  }
    ///there is the orange ball in -PI~0///
    /*if((-1*PI <= angle_orange) && (angle_orange < 0)){
      if((-1*PI <= angle_orange) && (angle_orange <= -1*PI/2)){
        while(angle_orange < 0){
          angle = angle_orange + PI/2;
          VNH_pwm(angle,50);
          angle_orange = -1 * get_angle_orange();
        }
      }
      if((-1*PI/2 < angle_orange) && (angle_orange < 0)){
        while(angle_orange < 0){
          angle = angle_orange -PI/2;
          VNH_pwm(angle,50);
          angle_orange = -1 * get_angle_orange();
        }
      }
    }
    else if (get_angle_orange() == get_angle_orange()){
      VNH_pwm(0,0);
    }
  }
  if((angle_orange < -1*PI) && (PI < angle_orange)){
    VNH_pwm(0,0);
  }*/
  
  /*robot_angle = get_robot_angle();
  robot_angle = get_robot_angle();
  robot_angle = get_robot_angle();
  robot_angle = get_robot_angle();
  robot_angle = get_robot_angle();
  robot_angle = -1 * get_robot_angle();
  while (((PI / 18<= robot_angle) && (robot_angle < 4 * PI / 5))) {
     VNH_rotate(-30);
     robot_angle = -1 * get_robot_angle();
   }
  while (((-4 * PI / 5 < robot_angle) && (robot_angle <= -PI / 18))){
    VNH_rotate(30);
    robot_angle = -1 * get_robot_angle();
  }*/
}