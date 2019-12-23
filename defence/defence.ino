//version 3.2

///library files///
#include <FlexiTimer2.h>
#include <avr/io.h>

///my header file///
#include "Motor_drive_VNH.h" //set motor driver pin && VNH_pwm,VNH1,VNH2,VNH3.VNH4 function
#include "White_line.h"
#include "pixy2_get_color_info.h" //set start_pixy2 , get angle orange , get angle yellow , get angle blue
#include "esc_control.h"
#include "communication.h" //set function get_robot_angle

///ball status///
bool ball; //ball true or false

///angles///
//in this program,all angle use RAD//
float angle_orange;
float angle_blue;
float angle_yellow;

float angle; //where you want to go

float robot_angle;

///distance///
float dist_orange;
float dist_blue;
float dist_yellow;

///start button///
const int start_button = 48;

///solenoid FET///
const int sloenoid_FET = 49;

///ball caught sensor///
const int ball_sensor = 47;

//////

void setup() {
  ///pin setup here///
  pinMode(PWM_1, OUTPUT); //pin 5
  pinMode(PWM_2, OUTPUT); //pin 6
  pinMode(PWM_3, OUTPUT); //pin 7
  pinMode(PWM_4, OUTPUT); //pin 8
  pinMode(A_1, OUTPUT);   //pin 22
  pinMode(A_2, OUTPUT);   //pin 23
  pinMode(A_3, OUTPUT);   //pin 24
  pinMode(A_4, OUTPUT);   //pin 25
  pinMode(B_1, OUTPUT);   //pin 26
  pinMode(B_2, OUTPUT);   //pin 27
  pinMode(B_3, OUTPUT);   //pin 28
  pinMode(B_4, OUTPUT);   //pin 29
 
  pinMode(start_button, INPUT_PULLUP); //start button = pin 48

  pinMode(sloenoid_FET, OUTPUT); //sloenoid_FET = pin 49

  pinMode(ball_sensor, INPUT_PULLUP); //ball caught sensor = pin 47

  //////

  Serial.begin(115200);
   Serial1.begin(115200);
  
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

}

void loop() {

}

///ball caught///
void ball_caught(){
  
}
