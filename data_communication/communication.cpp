//version 0.1

#include "Arduino.h"
#include "communication.h"

int get_robot_angle(){
  digitalWrite(4,LOW);
  digitalWrite(4,HIGH);
  while(Serial1.available()<=0);
  int angle = Serial1.read();
  digitalWrite(4,LOW);
  int angle1 = angle / 128.0 * 314;
  int angle2;
    
  if(angle1<314){
   angle2 = angle1;
  }
  if(angle1>=314){
    angle2 = angle1 - 628;
  }
  else;
  return angle2;   
  
}
