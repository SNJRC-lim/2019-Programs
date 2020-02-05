//version 3.8.5

///library files///
#include <FlexiTimer2.h>
#include <avr/io.h>

///my header files///
#include "Motor_drive_VNH.h" //set motor driver pin && VNH_pwm,VNH1,VNH2,VNH3.VNH4 function
#include "White_line.h"      //use it by flexitimer2 (timer interrapt)
#include "pixy2_get_color_info.h" //set start_pixy2 , get angle orange , get angle yellow , get angle blue
#include "esc_control.h"   //operating esc(brushless motor) , speed up or speed down
#include "communication.h" //set function get_robot_angle
#include "esc_control.h"   //operating esc(brushless motor) , speed up or speed down
#include "communication.h" //get_robot_angle
///goal color///
bool goal = true; //true : yellow , false : blue
///debug options///
#define DEBUG
#define DEBUG_Gyro_sensor //use this when debug gyro sensor in this program
#define DEBUG_color_angle //use this when debUg pixy in this program VNH_pwmellow , get angle blueon get_robot_angle

///game options///
#define start_soccer_game   //use this when real game
//#define developing_options  //use this if the function completed

///angles///
//in this program,all angle use RAD//
float angle_orange;
float angle_blue;
float angle_yellow;

float angle; //where you want to go

float robot_angle;  //get from arduino pro mini , robots yaw degree

///distance///
float dist_orange;VNH_pwm
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
  FlexiTimer2::set(1, 1.0 / 7500, White_line);
  FlexiTimer2::start();

  ///pixy setup///
  start_pixy2();

  ///esc setup///
  esc_setup();

  ///wait start///
  #ifdef start_soccer_game
    while (digitalRead(start_button) == 1);
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

  robot_angle = get_robot_angle()   //set robot_angle

  angle_orange == get_angle_orange() //set angle_orange

///division into cases according to ball status///
  if(-PI <= angle_orange <= PI){                  //robot find ball
    defence_goal();
  }

  if(-PI > angle_orange | PI < angle_orange){    //robot doesn't find ball
    VNH_pwm(PI,0);                               //don't move
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

void defence_goal(){
  if(-PI > angle_orange | PI < angle_orange){     //not find ball
    VNH_pwm(PI,0);                                //don't move
  }
  if(-PI <= angle_orange <= PI){                  //robot recognize ball
    if(5*PI/12 < angle_orange <= 7*PI/12){        //there is ball in front of robot
      if(digitalReadI(ball_sensor) = LOW){
        go_enemy_goal();
        kick_ball();
        back_goal();
      }
      else if(-PI/4 <= angle_orange <= 5*PI/12){  //there is ball on the right of robot
        while(-PI/4 <= angle_orange <= 5*PI/12){     
          VNH_rotate(50);                         //turn left until angle_orange comes in front
        }
        go_enemy_goal();
        kick_ball();
        back_goal();
      }
      else if(7*PI/12 <  angle_orange <= PI | -PI <= angle_orange <= 3*PI/4){    //there is ball on the left of robot
        while(7*PI/12 <  angle_orange <= PI | -PI <= angle_orange <= 3*PI/4){
          VNH_rotate(-50);                        //turn right until angle_orange comes in front
        }
        go_enemy_goal();
        kick_ball();
        back_goal();
      }
      else if(angle_orange == angle_orange == angle_orange){  //the same value is returned three times
        if(digitalRead(ball_sensor) == HIGH){     //robot doesn't have ball
          VNH_pwm(PI,0);
        }
        if(digitalRdad(ball_sensor) == LOW){      //robot has ball
          if(digitalRead(ball_sensor) == LOW){    //check ball status twice
            go_enemy_goal();
            kick_ball();
            back_goal();
          }
        }
      }
    }
  }
}

void kick_ball(){
  ///if enemy goal color is yellow...///
  if(goal == true){
    if(5*PI/12 <= angle_yellow <= 7*PI/12){     //robot find enemy goal
      digitalWrite(sloenoid_FET,HIGH);
    }
    if(0 <= angle_yellow <= 5*PI/12){           //there is enemy goal on the right of robot
      while(0 <= angle_yellow <= 5*PI/12){
        VNH_rotate(50);
      }
    }

    if(7*PI/12 < angle_yellow <= PI){           //there is enemy goal on the left of robot
      while(7*PI/12 < angle_yellow <= PI){
        VNH_rotate(-50);
      }
    }
  }

  ///if enemy goal color is blue...///
  if(goal == false){
    if(5*PI/12 <= angle_blue <= 7*PI/12){     //robot find enemy goal
      digitalWrite(sloenoid_FET,HIGH);
    }
    if(0 <= angle_blue <= 5*PI/12){
      while(0 <= angle_blue <= 5*PI/12){
        VNH_rotate(50);
      }
    }
    
    if(7*PI/12 < angle_blue <= PI){
      while(7*PI/12 < angle_blue <= PI){
        VNH_rotate(-50);
      }
    }
  }
}

#ifdef developing_options
void back_goal(){
  dist_blue == get_dist_blue();       //set dist_blue
  dist_yellow == get_dist_yellow();   //set dist_yellow
  if(digitalRead(ball_sensor) == LOW){  //check again 
    if(goal == true){
      FlexTimer2::stop();
      angle_blue == get_angle_blue();
      VNH_pwm(angle_blue,100);
    }
    if(goal == false){
      FlexTimer2::stop();
      angle_yellow == get_angle_yellow();
      VNH_pwm(angle_yellow,100);
      FlexTimer2::start();
    }
  }
}

void go_enemy_goal(){
  if(digitalRead(ball_sensor) == HIGH){
    if(goal == true){
        
    }
    if(goal == false){
        
    }
  }
}
#endif