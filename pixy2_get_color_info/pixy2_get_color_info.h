//version 2.0

#ifndef pixy2_get_color_info_h
#define pixy2_get_color_info_h

#include "Arduino.h"
#include "Pixy2.h"

const int sig_orange = 1;
const int sig_yellow = 2;
const int sig_blue = 3;

int get_angle_orange(int x_offset,int y_offset);
int get_angle_yellow(int x_offset,int y_offset);
int get_angle_blue(int x_offset,int y_offset);
/*int get_dist_orange(int x_offset,int y_offset);
int get_dist_yellow(int x_offset,int y_offset);
int get_dist_blue(int x_offset,int y_offset);*/
int get_x_orange(int x_offset,int y_offset);
int get_y_orange(int x_offset,int y_offset);
int get_x_yellow(int x_offset,int y_offset);
int get_y_yellow(int x_offset,int y_offset);
int get_x_blue(int x_offset,int y_offset);
int get_y_blue(int x_offset,int y_offset);

void start_pixy2();

#endif
