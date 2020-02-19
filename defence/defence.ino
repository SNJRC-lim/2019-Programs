//version 4.6

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


 angle_orange == get_angle_orange(); //set angle_orange

  if ( (-PI <= angle_orange) && (angle_orange <= PI )){ ///there is ball
   defence_goal();
  }
 

  if (angle_orange==get_angle_orange()==get_angle_orange() || angle_orange <= -PI || PI <= angle_orange){//not find to ball position
   if (digitalRead(ball_sensor) == 1){////robot has ball
     kick_ball();
    }
   else if (digitalRead(ball_sensor) == 0){///robot has not ball
     if (digitalRead(ball_sensor) == 0){///robot has not ball (double check)
       VNH_pwm(PI/2,0);//do not move
      }
     else if (digitalRead(ball_sensor) == 1){///robot has ball
       kick_ball();
      }
    }
  }

  if (digitalRead(ball_sensor)==1){///robot has ball
    if (digitalRead(ball_sensor)==1){　///double check
     kick_ball();
    }
  }

 ///Angle adjustment///
  robot_angle = get_robot_angle();
  while (((PI/18 <= robot_angle) && (robot_angle < PI))) {
    VNH_rotate(-40);
    robot_angle = get_robot_angle();
  }
  while (((-PI <= robot_angle) && (robot_angle < -PI/18))) {
    VNH_rotate(40);
    robot_angle = get_robot_angle();
  }
}

void defence_goal(){
  angle_orange = -1 * get_angle_orange();
   //move until angle_orange is 17/36*PI-7/12*PI 
  if ((0 <= angle_orange ) && (angle_orange < 17 * PI / 36)){
    angle = 0;
  }
  else if ((7 * PI / 12 < angle_orange) && (angle_orange <= PI)){
    angle = PI;
  }
  
  else if (((-PI / 4 <= angle_orange) && (angle_orange <= 0))){
    angle = angle_orange - PI / 2;
  }

  else if (((-PI <= angle_orange) && (angle_orange <= -3 * PI / 4))){
    angle = angle_orange + PI / 2;
  }
 
  VNH_pwm(angle,100);
}

void kick_ball(){//if can look enemy goal,kick ball     use flexitimer2_stop_proguram

  //FlexiTimer2::stop()

  if (goal == true){///enemy goal is yellow
   while ((angle_yellow < 4/9*PI) || (5/9*PI < angle_yellow)){
     if (angle_yellow < 4/9*PI){/// there is enemy goal in front of robot and right 
       VNH_pwm(0,100);///move left
       angle_yellow = get_angle_yellow();
      }
     else if (5/9*PI < angle_yellow){/// there is enemy goal in front of robot and left
        VNH_pwm(PI,100);///move right
        angle_yellow = get_angle_yellow();
      }
    }
   if ((4/9*PI <= angle_yellow) && (angle_yellow <= 5/9*PI)){///there is enemy goal in front of robot
     digitalWrite(sloenoid_FET,HIGH);///kick ball
     delay(100);
     digitalWrite(sloenoid_FET,LOW);
    }
  }
  else if (goal == false){///enemy goal is blue
    while (angle_blue < 4/9*PI || 5/9*PI < angle_blue){
     if (angle_blue < 4/9*PI){/// there is enemy goal in front of robot and right 
       VNH_pwm(0,100);///move right 
       angle_blue = get_angle_blue();
      }
     else if (5/9*PI < angle_blue){/// there is enemy goal in front of robot and left
       VNH_pwm(PI,100);///move left
       angle_blue = get_angle_blue();
      }
    }
   if ((4/9*PI <= angle_blue) && (angle_blue <= 5/9*PI)){///there is enemy goal in front of robot
     digitalWrite(sloenoid_FET,HIGH);///kick ball
     delay(100);
     digitalWrite(sloenoid_FET,LOW);
    }
  }
}