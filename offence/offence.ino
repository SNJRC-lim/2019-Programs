//version 6.5

///program for main game///
#define program_for_game //comment out this line when it is not real game

///set debug options///
#define DEBUG
#define DEBUG_Gyro_sensor //use this when debug gyro sensor in this program
#define DEBUG_color_angle //use this when debug pixy in this program

///library files///
#include <FlexiTimer2.h>
#include <avr/io.h>

///my header files///
#include "Motor_drive_VNH.h" //all function use percentage. set motor driver pin && VNH_pwm(degree,percentage),VNH1(pwm_value),VNH2(pwm_value),VNH3(vpwm_value),VNH4(pwm_value),VNH_rotate(percentage) function.
#include "White_line.h"      //use it by flexitimer2 (timer interrapt)
#include "pixy2_get_color_info.h" //set start_pixy2 , get angle orange , get angle yellow , get angle blue , get_dist_orange , get_dist_yellow , get_dist_blue
#include "esc_control.h"   //operating esc(brushless motor) , speed up or speed down
#include "communication.h" //set function get_robot_angle

///goal color///
bool goal = true; //true : yellow , false : blue

///ball status///
bool ball; //ball true or false

///angles///
//in this program,all angle defined as RAD//
int angle_orange;
int angle_blue;
int angle_yellow;

int angle; //where you want to go

int robot_angle;  //get from arduino pro mini , robots yaw degree

///distance///
int dist_orange;
int dist_blue;
int dist_yellow;

///color info x and y axis///
int x_orange;
int y_orange;
int x_yellow;
int y_yellow;
int x_blue;
int y_blue;

int dist_IR [4]; //get from arduino pro mini , [forward,back,right,left]

///start button///
const int start_button = 48;

///solenoid FET///
const int sloenoid_FET = 47;

///ball caught sensor///
const int ball_sensor = 49;

///set pixy2 x & y offset///
/*const int x_offset = 145;
const int y_offset = 128;*/
const int x_offset = 151;
const int y_offset = 130;
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
  //esc_setup();

///wait for start///
#ifdef program_for_game
  while (digitalRead(start_button) == 1);
#endif
}

void loop() {
#ifdef DEBUG
  #ifdef DEBUG_Gyro_sensor
    robot_angle = get_robot_angle();
  #endif

  #ifdef DEBUG_color_angle
    angle_orange = get_angle_orange(x_offset,y_offset);
  #endif

  #ifdef DEBUG_Gyro_sensor
    Serial.println(robot_angle * 180/PI);
  #endif

  #ifdef DEBUG_color_angle
    Serial.println(angle_orange * 180/PI);
  #endif
#endif
  robot_go_angle(); //set where the robot go to

  ///if robot lost ball position,jump to ball_catch()///
  if ((angle_orange < -314) || (314 < angle_orange)) {
    ball_catch();
  }

  if (get_angle_orange(x_offset,y_offset) == 810) {
    ball_catch();
  }

  else {
    float angle2 = angle / 100;
    VNH_pwm(angle2, 40);
  }
   
  ///Angle adjustment///
  angle_adjustment();
}

///ball caught///
void ball_catch() {
  if (digitalRead(ball_sensor) == 0) {
    if (digitalRead(ball_sensor) == 0) {
      if (digitalRead(ball_sensor) == 0) {
        if (digitalRead(ball_sensor) == 0) {
          bool kicked;
          //esc_speed_up();
          if (goal == true) {
            angle_yellow = get_angle_yellow(x_offset, y_offset);

            if (angle_yellow <= 0) {
              angle_yellow = angle_yellow + 314;
            }
            else if (0 < angle_yellow) {
              angle_yellow = angle_yellow - 314;
            }

            while ((-314 / 2 <= angle_yellow) && (angle_yellow < 314 / 3)) {
              VNH_pwm(PI / 6, 30);
              angle_yellow = get_angle_yellow(x_offset, y_offset);

              if (angle_yellow <= 0) {
                angle_yellow = angle_yellow + 314;
              }
              else if (0 < angle_yellow) {
                angle_yellow = angle_yellow - 314;
              }

              angle_adjustment();
            }
            while (((2 * 314 / 3 <= angle_yellow) && (angle_yellow < 314)) || ((-314 <= angle_yellow) && (angle_yellow < -314 / 2))) {
              VNH_pwm(5 * PI / 6, 30);
              angle_yellow = get_angle_yellow(x_offset, y_offset);

              if (angle_yellow <= 0) {
                angle_yellow = angle_yellow + 314;
              }
              else if (0 < angle_yellow) {
                angle_yellow = angle_yellow - 314;
              }

              angle_adjustment();
            }

            angle_yellow = get_angle_yellow(x_offset,y_offset);

              if ((4/9 * PI <= angle_yellow) && (angle_yellow <= 5/9 * PI)) {
              //esc_speed_down();
              digitalWrite(sloenoid_FET, HIGH);
              delay(10);
              digitalWrite(sloenoid_FET, LOW);
              kicked = true;
              }

              else {
              angle_yellow = get_angle_yellow(x_offset,y_offset);
              VNH_pwm(angle_yellow,70);
              }
            angle_yellow = get_angle_yellow(x_offset, y_offset);

            if (angle_yellow <= 0) {
              angle_yellow = angle_yellow + 314;
            }
            else if (0 < angle_yellow) {
              angle_yellow = angle_yellow - 314;
            }

            if ((314 / 3 <= angle_yellow) && (angle_yellow < 2 * 314 / 3)) {
              VNH_pwm(angle_yellow, 60);
            }
          }

          if (goal == false) {
            angle_blue = get_angle_blue(x_offset, y_offset);

            if (angle_blue <= 0) {
              angle_blue = angle_blue + 314;
            }
            else if (0 < angle_yellow) {
              angle_blue = angle_blue - 314;
            }

            while ((-314 / 2 <= angle_blue) && (angle_blue < 314 / 3)) {
              VNH_pwm(PI / 6, 30);
              angle_blue = get_angle_blue(x_offset, y_offset);

              if (angle_blue <= 0) {
                angle_blue = angle_blue + 314;
              }
              else if (0 < angle_yellow) {
                angle_blue = angle_blue - 314;
              }

              angle_adjustment();
            }
            while (((2 * 314 / 3 <= angle_blue) && (angle_blue < 314)) || ((-314 <= angle_blue) && (angle_blue < -314 / 2))) {
              VNH_pwm(5 * PI / 6, 30);
              angle_blue = get_angle_blue(x_offset, y_offset);

              if (angle_blue <= 0) {
                angle_blue = angle_blue + 314;
              }
              else if (0 < angle_yellow) {
                angle_blue = angle_blue - 314;
              }

              angle_adjustment();
            }

             angle_blue = get_angle_blue(x_offset,y_offset);

              if ((4/9 * PI <= angle_blue) && (angle_blue <= 5/9 * PI)) {
               //esc_speed_down();
               digitalWrite(sloenoid_FET, HIGH);
               delay(10);
               digitalWrite(sloenoid_FET, LOW);
               kicked = true;
              }


              else {
              angle_blue = get_angle_blue(x_offset,y_offset);
              VNH_pwm(angle_blue,70);
              }
            angle_yellow = get_angle_yellow(x_offset, y_offset);

            if (angle_blue <= 0) {
              angle_blue = angle_blue + 314;
            }
            else if (0 < angle_yellow) {
              angle_blue = angle_blue - 314;
            }

            if ((314 / 3 <= angle_blue) && (angle_blue < 2 * 314 / 3)) {
              VNH_pwm(angle_yellow, 60);
            }

          }
          if ((digitalRead(ball_sensor) == 0) && (kicked == false)) {
            //esc_speed_down();
          }
          //FlexiTimer2::start();
          kicked = false;
        }
      }
    }
  }
  else {
  VNH_pwm(PI / 2, 40);
  }
}

///set where the robot have to go///
void robot_go_angle(){
  angle_orange = get_angle_orange(x_offset, y_offset);

  if (angle_orange <= 0) {
    angle_orange = angle_orange + 314;
  }
  else if (0 < angle_orange) {
    angle_orange = angle_orange - 314;
  }

  if ((314 / 3 <= angle_orange) && (angle_orange <= 2 * 314 / 3)) {
    angle = angle_orange;
  }


  if (((0 <= angle_orange) && (angle_orange < 314 / 12)) || ((11 * 314 / 12 < angle_orange) && (angle_orange <= 314))) {
    angle = -157;
  }

  else if ((314 / 12 <= angle_orange) && (angle_orange < 314 / 3)) {
    angle = angle_orange - 314 / 2;
  }

  else if ((2 * 314 / 3 < angle_orange) && (angle_orange <= 11 * 314 / 12)) {
    angle = angle_orange - 3 * 314 / 2;
  }

  else if ((-314 / 2 <= angle_orange) && (angle_orange < 0)) {
    angle = -314 / 2 + angle_orange;
  }
  else if ((-314 <= angle_orange) && (angle_orange < -314 / 2 )) {
    angle = 314 / 2 + angle_orange;
  }
}

void angle_adjustment(){
  robot_angle = -1 * get_robot_angle();
  while (((314 / 18 <= robot_angle) && (robot_angle < 4 * 314 / 5))) {
    VNH_rotate(-30);
    robot_angle = -1 * get_robot_angle();
  }
  while (((-4 * 314 / 5 < robot_angle) && (robot_angle <= -314 / 18))) {
    VNH_rotate(30);
    robot_angle = -1 * get_robot_angle();
  }
}
