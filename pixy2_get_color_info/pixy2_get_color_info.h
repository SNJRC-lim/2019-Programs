//version 2.0

#ifndef pixy2_get_color_info_h
#define pixy2_get_color_info_h

#include "Arduino.h"
#include "Pixy2.h"

const int sig_orange = 1;
const int sig_yellow = 2;
const int sig_blue = 3;

float get_angle_orange(float x_offset,float y_offset);
float get_angle_yellow(float x_offset,float y_offset);
float get_angle_blue(float x_offset,float y_offset);
float get_dist_orange(float x_offset,float y_offset);
float get_dist_yellow(float x_offset,float y_offset);
float get_dist_blue(float x_offset,float y_offset);
float x_orange(float x_offset,float y_offset);
float y_orange(float x_offset,float y_offset);
float x_yellow(float x_offset,float y_offset);
float y_yellow(float x_offset,float y_offset);
float x_blue(float x_offset,float y_offset);
float y_blue(float x_offset,float y_offset);

void start_pixy2();

#endif
