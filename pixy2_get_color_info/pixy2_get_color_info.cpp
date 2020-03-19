#include <Arduino.h>
#include <Pixy2.h>
#include <pixy2_get_color_info.h>

Pixy2 pixy;

pixy2_info::pixy2_info(){
	pixy.init();
}

void pixy2_info::set_offset(int offset_x, int offset_y){
	x_offset = offset_x;
	y_offset = offset_y;
}

void pixy2_info::attach_sig_num(int orange_sig, int yellow_sig, int blue_sig){
	sig_orange = orange_sig;
    sig_yellow = yellow_sig;
    sig_blue = blue_sig;
}

int pixy2_info::orange_angle(){
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks>=2){
	int x1 = pixy.ccc.blocks[sig_orange].m_x;
    int y1 = pixy.ccc.blocks[sig_orange].m_y;
    int x = x1 - x_offset;
    int y = (y1 - y_offset) * (-1);

    int rad = atan2(y , x) * 100;
  
    if (rad >= 0) {
      rad = 314 - rad;
    }
    else if (0 > rad) {
      rad = -1 * rad - 314;
    }
    return rad;
  }
  else {
	  return 810;
  }	
}

int pixy2_info::orange_x(){
	pixy.ccc.getBlocks();
	
  if (pixy.ccc.numBlocks){
	int x1 = pixy.ccc.blocks[sig_orange].m_x;
    int x = x1 - x_offset;
    return -1 * x;
  }
  else {
	  return 810;
  }
}

int pixy2_info::orange_y(){
	pixy.ccc.getBlocks();
	
  if (pixy.ccc.numBlocks){
	int y1 = pixy.ccc.blocks[sig_orange].m_y;
    int y = y1 - y_offset;
    return -1 * y;
  }
  else {
	  return 810;
  }
}

/*int pixy2_info::orange_dist(){}*/

int pixy2_info::yellow_angle(){
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks>=2){
	int x1 = pixy.ccc.blocks[sig_yellow].m_x;
    int y1 = pixy.ccc.blocks[sig_yellow].m_y;
    int x = x1 - x_offset;
    int y = (y1 - y_offset) * (-1);

    int rad = atan2(y , x) * 100;
  
    if (rad >= 0) {
      rad = 314 - rad;
    }
    else if (0 > rad) {
      rad = -1 * rad - 314;
    }
    return rad;
  }
  else {
	  return 810;
  }	
}

int pixy2_info::yellow_x(){
	pixy.ccc.getBlocks();
	
  if (pixy.ccc.numBlocks){
	int x1 = pixy.ccc.blocks[sig_yellow].m_x;
    int x = x1 - x_offset;
    return -1 * x;
  }
  else {
	  return 810;
  }
}

int pixy2_info::yellow_y(){
	pixy.ccc.getBlocks();
	
  if (pixy.ccc.numBlocks){
	int y1 = pixy.ccc.blocks[sig_yellow].m_y;
    int y = y1 - y_offset;
    return -1 * y;
  }
  else {
	  return 810;
  }
}

/*int pixy2_info::yellow_dist(){}*/

int pixy2_info::blue_angle(){
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks>=2){
	int x1 = pixy.ccc.blocks[sig_blue].m_x;
    int y1 = pixy.ccc.blocks[sig_blue].m_y;
    int x = x1 - x_offset;
    int y = (y1 - y_offset) * (-1);

    int rad = atan2(y , x) * 100;
  
    if (rad >= 0) {
      rad = 314 - rad;
    }
    else if (0 > rad) {
      rad = -1 * rad - 314;
    }
    return rad;
  }
  else {
	  return 810;
  }	
}

int pixy2_info::blue_x(){
	pixy.ccc.getBlocks();
	
  if (pixy.ccc.numBlocks){
	int x1 = pixy.ccc.blocks[sig_blue].m_x;
    int x = x1 - x_offset;
    return -1 * x;
  }
  else {
	  return 810;
  }
}

int pixy2_info::blue_y(){
	pixy.ccc.getBlocks();
	
  if (pixy.ccc.numBlocks){
	int y1 = pixy.ccc.blocks[sig_blue].m_y;
    int y = y1 - y_offset;
    return -1 * y;
  }
  else {
	  return 810;
  }
}

/*int pixy2_info::blue_dist(){}*/
