//version 4.0.4

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

  if(-PI > angle_orange || PI < angle_orange){     //robot doesn't find ball
    VNH_pwm(PI,0);                                //don't move
  }

 ///Angle adjustment once in 10 routines///
  int count = count + 1;
  if(count = 10){
    count = 0;
    if (goal = true) {
      robot_angle = get_robot_angle();
      angle_yellow = get_angle_yellow();
      while (((-PI / 2 <= angle_yellow) && (angle_yellow < PI / 3)) || ((PI / 18<= robot_angle) && (robot_angle < PI))) {
        VNH_rotate(-50);
        robot_angle = get_robot_angle();
        angle_yellow = get_angle_yellow();
      }
      while (((2 * PI / 3 <= angle_yellow) && (angle_yellow < PI)) || ((-PI <= angle_yellow) && (angle_yellow < -PI / 2)) || ((-PI <= robot_angle) && (robot_angle < -PI / 18))) {
        VNH_rotate(50);
        robot_angle = get_robot_angle();
        angle_yellow = get_angle_yellow();
      }
    }
    if (goal = false) {
      robot_angle = get_robot_angle();
      angle_blue = get_angle_blue();
      while (((-PI / 2 <= angle_blue) && (angle_blue < PI / 3)) || ((1/18 * PI <= robot_angle) && (robot_angle < PI))) {
        VNH_rotate(-50);
        robot_angle = get_robot_angle();
        angle_blue = get_angle_blue();
      }
      while (((2/3 * PI <= angle_blue) && (angle_blue < PI)) || ((-PI <= angle_blue) && (angle_blue < -PI / 2)) || ((-PI <= robot_angle) && (robot_angle < -PI / 18))) {
        VNH_rotate(50);
        robot_angle = get_robot_angle();
        angle_blue = get_angle_blue();
      }
    }
  }
}

void defence_goal(){
  if((-PI > angle_orange) || (PI < angle_orange)){     //not find ball
    VNH_pwm(PI,0);                                    //don't move
  }
  if((-PI <= angle_orange) && (angle_orange <= PI)){  //robot recognize ball
    
    ///there is ball in 0~PI///
    if((0 <= angle_orange) && (angle_orange <= PI)){                  
      if((4*PI/9 < angle_orange) && (angle_orange < 5*PI/9)){   //there is ball in front of robot
        if(digitalRead(ball_sensor) == 1){        //robot has alredy caught ball
          go_enemy_goal();
          kick_ball();
          back_goal();
        }
        else{
          VNH_pwm(0,0)                            //don't move
        }
      }   
      if((0 <= angle_orange) %% (angle_orange <= 4*PI/9)){            //there is ball on the right of robot
        while((0 <= angle_orange) && (angle_orange <= 17*PI/36)){
          VNH_pwm(0,50);
        }
      }   
      if((5*PI/9 <= angle_orange) && (angle_orange < PI)){            //there is ball on the left of robot
        while((19*PI/36 <= angle_orange) && (angle_orange < PI)){ 
          VNH_pwm(PI,50);
        }
      }    
      if(angle_orange == get_angle_orange() == get_angle_orange()){   //the same value is returned three times
        if(digitalRead(ball_sensor) == 0){        //robot has alredy caught ball
          if(digitalRead(ball_sensor) == 0){      //check again
          go_enemy_goal();
          kick_ball();  
          back_goal();
          }
        }            
        if(digitalRead(ball_sensor) == 1){        //robot doesn't have ball
          VNH_pwm(0,0);                           //don't move
        }
      }
    } 
    
    ///there is ball -PI~0///
    if((-PI <= angle_orange) && (angle_orange < 0)){                  
      if((-PI <= angle_orange)&& (angle_orange <= -PI/2)){           //there is ball on the back left
        while(((-PI <= angle_orange) && (angle_orange <= -PI/2)) | (angle_orange <= 5*PI/9)){
          VNH_rotate(-50);
        }
      }
    
      if((-PI/2 < angle_orange) && (angle_orange < 0)){              //there is ball on the back right
        while((-PI/2 < angle_orange) && (angle_orange < 4*PI/9)){
          VNH_rotate(50);
        }
      }
    }
  }
}

void kick_ball(){
  ///if enemy goal color is yellow...///
  if(goal == true){
    
    ///there is yellow goal in 0~PI///
    if((0 <= angle_yellow) && (angle_yellow <= PI)){                  
      if((4*PI/9 < angle_yellow) && (angle_yellow < 5*PI/9)){         //there is yellow goal in front of robot
        digitalWrite(sloenoid_FET,HIGH);
      }
      if((0 <= angle_yellow) && (angle_yellow <= 4*PI/9)){            //there is yellow goal on the right robot 
        while((4*PI/9 < angle_yellow) && (angle_yellow <= 17*PI/36)){
          VNH_rotate(-50);
        }
      }
      if(((5*PI/9 < angle_yellow) && (angle_yellow < PI)){            //there is yellow goal on the left of robot 
        while((19*PI/36 < angle_yellow) && (angle_yellow < PI)){
          VNH_rotate(50);
        }
      }
      if(get_angle_yellow == get_angle_yellow() == get_angle_yellow()){   //the same value is returned three times
        VNH_pwm(0,0);
      }
    }
  
    ///there is yellow goal in -PI~0///
    if((-PI <= angle_yellow) && (angle_yellow < 0)){                  
      if((-4*PI/9 < angle_yellow) && (angle_yellow < 0)){                 //there is yellow goal on the back right        
        while((-4*PI/9 < angle_yellow) && (angle_yellow <= 17*PI/36)){
          VNH_rotate(-50);
        }
      }
      if((-PI < angle_yellow) && (angle_yellow < -5*PI/9)){               //there is yellow goal on the bak left
        while(((-PI < angle_yellow) && (angle_yellow < -5*PI/9)) || (angle_orange > 19*PI/36)){
          VNH_rotate(-50);
        }
      }
      if((-5*PI/9 < angle_yellow) && (angle_yellow < -4*PI/9)){           //there is yellow goal right behind
        while((-5*PI/9 < angle_yellow) && (angle_yellow < -4*PI/9)){
          VNH_pwm(-50);
        }
      }
    }
  }

  ///if enemy goal color is blue...///
  if(goal ==false){
    ///there is blue goal in 0~PI
    if((0 <= angle_blue) && (angle_blue <= PI)){                  
      if((4*PI/9 < angle_yellow) && (angle_yellow < 5*PI/9)){     //there is blue goal in front of goal 
        digitalWrite(sloenoid_FET,HIGH);
      }
      if((0 <= angle_blue) && (angle_blue <= 4*PI/9)){            //there is blue goal on the right 
        while((4*PI/9 < angle_yellow) && (angle_yellow <= 17*PI/36)){
          VNH_rotate(-50);
        }
      }
      if((5*PI/9 < angle_blue) && (angle_blue < PI)){             //there is blue goal on the left
        while((19*PI/36 < angle_blue) && (angle_blue < PI)){
          VNH_rotate(50);
        }
      }
      if(get_angle_blue == get_angle_blue() == get_angle_blue()){ //the same value is returned three times
        VNH_pwm(0,0);
      }
    }
  
    ///there is blue goal in -PI~0///
    if((-PI <= angle_blue) && (angle_blue < 0)){
      if((-4*PI/9 < angle_blue) && (angle_blue < 0)){             //there is blue goal on the back right
        while((-4*PI/9 < angle_blue) && ( angle_blue <= 17*PI/36)){
          VNH_rotate(-50);
        }
      }
      if((-PI < angle_blue) && (angle_blue < -5*PI/9)){           //there is blue goal on the back left 
        while((-PI < angle_blue) && (angle_blue < -5*PI/9) || (angle_blue > 19*PI/36)){
          VNH_rotate(-50);
        }
      }
      if((-5*PI/9 N angle_blue) && (angle_blue < -4*PI/9)){       //there is blue goal right behind 
        while((-5*PI/9 < angle_blue) && (angle_blue < -4*PI/9)){
          VNH_pwm(-50);
        }
      }
    }
  }
}

#ifdef developing_options
void go_enemy_goal(){
  dist_blue == get_dist_blue();               //set dist_blue
  dist_yellow == get_dist_yellow();           //set dist_yellow
  
  if(digitalRead(ball_sensor) == 0){          //robot has ball alredy
    //enemy goal color is yellow 
    if(goal == true){
        
    }
    if(goal == false){
        
    }
  }
}

void back_goal(){
  if(digitalRead(ball_sensor) == 1){          //check ball status 
    if(goal == true){
      FlexiTimer2::stop();                     //stop timer 
      angle_blue == get_angle_blue(); 
      VNH_pwm(angle_blue,100);
    }
    if(goal == false){
      FlexTimer2::stop();
      angle_yellow == get_angle_yellow();
      VNH_pwm(angle_yellow,100);
    }
  }
}
#endif