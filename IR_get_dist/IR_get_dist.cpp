#include "IR_get_dist.h"
#include "Arduino.h"

IR_dist::IR_dist(){}

void IR_dist::attach_pin(byte pin_front, byte pin_right, byte pin_left, byte pin_back){
	front_pin = pin_front;
	back_pin = pin_back;
	right_pin = pin_right;
	left_pin = pin_left;
}

int IR_dist::front(){
  int dist  = (26.549*pow(5.0*analogRead(front_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(front_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(front_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(front_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(front_pin)/1023,-1.2091)) * 20;
  return dist;
}

int IR_dist::right(){
  int dist  = (26.549*pow(5.0*analogRead(right_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(right_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(right_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(right_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(right_pin)/1023,-1.2091)) * 20;
  return dist;
}

int IR_dist::left(){
  int dist  = (26.549*pow(5.0*analogRead(left_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(left_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(left_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(left_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(left_pin)/1023,-1.2091)) * 20;
  return dist;
}

int IR_dist::back(){
  int dist  = (26.549*pow(5.0*analogRead(back_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(back_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(back_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(back_pin)/1023,-1.2091) + 26.549*pow(5.0*analogRead(back_pin)/1023,-1.2091)) * 20;
  return dist;
}

