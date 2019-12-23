//version 3.5

///program for main game///
//#define program_for_game //comment out this line when it is not real game

///set debag options///
#define DEBAG
#define DEBAG_Gyro_sensor //use this when debag gyro sensor in this program
#define DEBAG_color_angle //use this when debag pixy in this program
#define DEBAG_White_line  //use this when debag whit line sensor programm

///library files///
#include <FlexiTimer2.h>
#include <avr/io.h>

///my header files///
#include "Motor_drive_VNH.h" //set motor driver pin && VNH_pwm,VNH1,VNH2,VNH3.VNH4 function
#include "White_line.h"      //use it by flexitimer2 (timer interrapt)
#include "pixy2_get_color_info.h" //set start_pixy2 , get angle orange , get angle yellow , get angle blue , get_dist_orange , get_dist_yellow , get_dist_blue
#include "esc_control.h"   //operating esc(brushless motor) , speed up or speed down
#include "communication.h" //set function get_robot_angle

///ball status///
bool ball; //ball true or false

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

  ///wait for start///
  #ifdef program_for_game
    while(digitalRead(start_button)==1);
  #endif
}

void loop() {

  #ifdef DEBAG
    #ifdef DEBAG_Gyro_sensor
      robot_angle = get_robot_angle();
    #endif 

    #ifdef DEBAG_color_angle 
      angle_orange = get_angle_orange();
    #endif
  
    #ifdef DEBAG_Gyro_sensor
      Serial.println(robot_angle);
    #endif 

    #ifdef DEBAG_color_angle 
      Serial.println(angle_orange);
    #endif

    #ifdef DEBAG_White_line
      Serial.println(digitalRead(30));
    #endif
  #endif

  angle_orange = get_angle_orange();
  
  if(angle_orange < -PI | PI < angle_orange){
    ball_caught();
  }
  
  if(PI/4<=angle_orange<=3/4*PI){
    angle = angle_orange;
  }
  if(0<=angle_orange<PI/4){
    angle = -1/4*PI;
  }
  if(3/4*PI<angle_orange<=PI){
    angle = -3/4*PI;
  }
  if(0<angle_orange<=-1/4*PI | -3/4*PI<=angle_orange<-PI){
    angle = -1/2*PI;
  }
  if(-1/2*PI<=angle_orange<-3/4*PI){
    angle = -1/6*PI;
  }
  if(-1/4*PI<=angle_orange<-1/2*PI){
    angle = -5/6*PI;
  }
 
  ball_caught();
  
  #ifdef program_for_game
    
  #endif
}

///ball caught///
void ball_caught(){
  if(digitalRead(ball_sensor)==1){
    if(digitalRead(ball_sensor)==1){
      robot_angle = get_robot_angle();
      angle_yellow = get_angle_yellow();
      dist_yellow = get_dist_yellow();
      angle_blue = get_angle_blue();
      dist_blue = get_dist_blue();
    }
  }
}
