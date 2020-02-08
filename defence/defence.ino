//version 3.8

///library files///
#include <FlexiTimer2.h>
#include <avr/io.h>

///my header files///
#include "Motor_drive_VNH.h" //set motor driver pin && VNH_pwm,VNH1,VNH2,VNH3.VNH4 function
#include "White_line.h"      //use it by flexitimer2 (timer interrapt)
#include  "pixy2_get_color_info.h" //set start_pixy2 , get angle orange , get angle yellow , get angle blue
#include "esc_control.h"   //operating esc(brushless motor) , speed up or speed down
#include "communication.h" //set function get_robot_angle

#define start_program
#define DEBUG
#define DEBUG_color_angle
#define DEBUG_Gyro_sensor

///ball status///
bool ball; //ball true or false

///goal color///
bool goal = true;//true yellow : false blue

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

//////

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

  //////

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  
  ///change PWM freqency///
  TCCR3B = (TCCR3B & 0b11111000) | 1;
  TCCR4B = (TCCR4B & 0b11111000) | 1;

  ///set timer interrupt///
  FlexiTimer2::set(1, 1.0 / 7500, White_line);
  FlexiTimer2::start();

  ///pixy setup///
  start_pixy2();

  ///esc setup///
  esc_setup();

  #ifdef start_program
   while(digitalRead(start_button)==1);
  #endif 
}

void loop() {
#ifdef DEBUG
  #ifdef DEBUG_Gyro_sensor
    robot_angle = get_robot_angle();
  #endif

  #ifdef DEBUG_color_angle
    angle_orange = get_angle_orange();
  #endif

  #ifdef DEBUG_Gyro_sensor
    Serial.println(robot_angle * 180/PI);
  #endif

  #ifdef DEBUG_color_angle
    Serial.println(angle_orange * 180/PI);
  #endif
#endif

angle_yellow = get_angle_yellow();
angle_blue = get_angle_blue();

  if ( -PI <= angle_orange <= PI ){ ///there is ball
   angle_robot();
  }

  if (angle_orange==get_angle_orange()==get_angle_orange()){//not find to ball position
  VNH_pwm(PI/2,0);//do not move
  }

  if (digitalRead(ball_sensor)==0){
    if (digitalRead(ball_sensor)==0){　///double check
    ball_kick();
    }
  }

  ///Angle adjustment once in 10 routines///
  int count = count + 1;
  if(count = 10){
    count = 0;
    if (goal = true) {
      robot_angle = get_robot_angle();
      angle_yellow = get_angle_yellow();
      while (0 <= angle_yellow < PI / 4 | -PI / 2 <= angle_yellow < 0 | 0 <= robot_angle < 4/9 * PI | -PI / 2 <= robot_angle < 0) {
        VNH_rotate(-50);
        robot_angle = get_robot_angle();
        angle_yellow = get_angle_yellow();
      }
      while (3/4 * PI <= angle_yellow < PI | -PI <= angle_yellow < -PI / 2 | 5/9 * PI <= robot_angle < PI | -PI <= robot_angle < -PI / 2 ) {
        VNH_rotate(50);
        robot_angle = get_robot_angle();
        angle_yellow = get_angle_yellow();
      }
    }
    if (goal = false) {
      robot_angle = get_robot_angle();
      angle_blue = get_angle_blue();
      while (0 <= angle_blue < PI / 3 | -PI / 2 <= angle_blue < 0 | 0 <= robot_angle < 4/9 * PI | -PI / 2 <= robot_angle < 0) {
        VNH_rotate(-50);
        robot_angle = get_robot_angle();
        angle_blue = get_angle_blue();
      }
      while (2/3 * PI <= angle_blue < PI | -PI <= angle_blue < -PI / 2 | 5/9 * PI <= robot_angle < PI | -PI <= robot_angle < -PI / 2 ) {
        VNH_rotate(50);
        robot_angle = get_robot_angle();
        angle_blue = get_angle_blue();
      }
    }
  }
}
}

void angle_robot(){
  //move until angle_orange is 90angle 
   while (0 < angle_orange　< PI/2 | PI/2 < angle_orange < PI){
     if (0 < angle_orange < PI/2){
       VNH_pwm(0,100);
     }
     else if (PI/2 < angle_orange　< PI){
       VNH_pwm(-PI,100);
     }
   }
   if (-PI/2 <=  angle_orange <= 0){
     VNH_pwm( -3/4*PI , 100 );
  }
  else if (-PI <= angle_orange < -PI/2){
     VNH_pwm( -PI/4 , 100 );
  }
}
  
void ball_kick(){//if can look enemy goal,kick ball
  if (goal == true){///enemy goal is yellow
   while (angle_yellow < 4/9*PI | 5/9*PI < angle_yellow){
     if (angle_yellow < 4/9*PI){
      VNH_pwm(0,100);
     }
     else if (5/9*PI < angle_yellow){
      VNH_pwm(-PI,100);
     }
   }
   if (4/9*PI <= angle_yellow <= 5/9*PI){
     digitalWrite(sloenoid_FET,HIGH);
   }
  }
  else if (goal == false){///enemy goal is blue
    while (angle_blue < 4/9*PI | 5/9*PI < angle_blue){
     if (angle_blue < 4/9*PI){
      VNH_pwm(0,100);
     }
     else if (5/9*PI < angle_blue){
      VNH_pwm(-PI,100);
     }
   }
   if (4/9*PI <= angle_blue <= 5/9*PI){
     digitalWrite(sloenoid_FET,HIGH);
   }
  }
}