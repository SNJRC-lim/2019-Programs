//version 0.0

#include "Arduino.h"
#include "communication.h"

float get_robot_angle(){
  if(Serial1.available()>0){
    int angle = Serial1.read();
    float angle1 = angle / 128.0 * PI;
    float angle2;
    
    if(angle1<3.14){
	  angle2 = angle1;
	  }
    if(angle1>=3.14){
      angle2 = angle1 -2*PI;
    }
    else;
  
    return angle2;   
  }
}
