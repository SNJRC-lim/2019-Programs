//version 0.0

#include <IR_get_dist.h>

float get_dist1(){
  float dist  = 26.549*pow(5.0*analogRead(A0)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A0)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A0)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A0)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A0)/1023,-1.2091);
  float dist1 = dist / 5;
  return dist1;
}

float get_dist2(){
  float dist  = 26.549*pow(5.0*analogRead(A1)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A1)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A1)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A1)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A1)/1023,-1.2091);
  float dist2 = dist / 5;
  return dist2;
}

float get_dist3(){
  float dist  = 26.549*pow(5.0*analogRead(A2)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A2)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A2)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A2)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A2)/1023,-1.2091);
  float dist3 = dist / 5;
  return dist3;
}

float get_dist4(){
  float dist  = 26.549*pow(5.0*analogRead(A3)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A3)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A3)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A3)/1023,-1.2091) + 26.549*pow(5.0*analogRead(A3)/1023,-1.2091);
  float dist4 = dist / 5;
  return dist4;
}


