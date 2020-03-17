//version 2.0

#include "Arduino.h"
#include "Pixy2.h"
#include "pixy2_get_color_info.h"

Pixy2 pixy;

///pixy start///

void start_pixy2(){
  pixy.init();
}

///orange angle///
int get_angle_orange(int x_offset,int y_offset) {
	
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks>=2){
	int x1 = pixy.ccc.blocks[1].m_x;
    int y1 = pixy.ccc.blocks[1].m_y;
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


///yellow angle///
int get_angle_yellow(int x_offset,int y_offset) {

  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks){
	int x1 = pixy.ccc.blocks[0].m_x;
    int y1 = pixy.ccc.blocks[0].m_y;
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

///blue angle///
int get_angle_blue(int x_offset,int y_offset) {

  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks){
	int x1 = pixy.ccc.blocks[2].m_x;
    int y1 = pixy.ccc.blocks[2].m_y;
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

///orange distance///
/*int get_dist_orange(int x_offset,int y_offset){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_orange) {

    int x1 = pixy.ccc.blocks[0].m_x;
    int y1 = pixy.ccc.blocks[0].m_y;
    int x = x1 - x_offset;
    int y = (y1 - y_offset) * (-1);
    
    int dist0 = 2 *  sqrt(x*x + y*y);
    int dist5 = 151- dist0;
    int dist1 = sqrt(dist5);
    int dist2 = 306.1862 * dist1;
    int dist3 = 3159 - dist2;
    int dist = dist3 /45;
    
    if(dist0 > 151){
		dist = 65;
	}
    
    return dist;
  }
}  

///yellow distance///
int get_dist_yellow(int x_offset,int y_offset){
	static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_yellow) {

    int x1 = pixy.ccc.blocks[0].m_x;
    int y1 = pixy.ccc.blocks[0].m_y;
    int x = x1 - x_offset;
    int y = (y1 - y_offset) * (-1);

    int dist0 = 2 *  sqrt(x*x + y*y);
    int dist5 = 151- dist0;
    int dist1 = sqrt(dist5);
    int dist2 = 306.1862 * dist1;
    int dist3 = 3159 - dist2;
    int dist = dist3 /45;
    
    if(dist0 > 151){
		dist = 65;
	}
    return dist;
  }
}  

///blue distance///
int get_dist_blue(int x_offset,int y_offset){
	static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_blue) {

    int x1 = pixy.ccc.blocks[0].m_x;
    int y1 = pixy.ccc.blocks[0].m_y;
    int x = x1 - x_offset;
    int y = (y1 - y_offset) * (-1);

    int dist0 = 2 *  sqrt(x*x + y*y);
    int dist5 = 151- dist0;
    int dist1 = sqrt(dist5);
    int dist2 = 306.1862 * dist1;
    int dist3 = 3159 - dist2;
    int dist = dist3 /45;
    
    if(dist0 > 151){
		dist = 65;
	}
    return dist;
  }
}  
*/
int get_x_orange(int x_offset,int y_offset){

  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks){
	int x1 = pixy.ccc.blocks[1].m_x;
    int x = x1 - x_offset;
    return -1 * x;
  }
  else {
	  return 810;
  }
}

int get_y_orange(int x_offset,int y_offset){

  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks){
	int y1 = pixy.ccc.blocks[1].m_y;
    int y = y1 - y_offset;
    return -1 * y;
  }
  else {
	  return 810;
  }
}	

int get_x_yellow(int x_offset,int y_offset){

  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks){
	int x1 = pixy.ccc.blocks[0].m_x;
    int x = x1 - x_offset;
    return -1 * x;
  }
  else {
	  return 810;
  }
}

int get_y_yellow(int x_offset,int y_offset){

  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks){
	int y1 = pixy.ccc.blocks[0].m_y;
    int y = y1 - y_offset;
    return -1 * y;
  }
  else {
	  return 810;
  }
}

int get_x_blue(int x_offset,int y_offset){

  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks){
	int x1 = pixy.ccc.blocks[2].m_x;
    int x = x1 - x_offset;
    return -1 * x;
  }
  else {
	  return 810;
  }
}

int get_y_blue(int x_offset,int y_offset){

  pixy.ccc.getBlocks();
  if (pixy.ccc.numBlocks){
	int y1 = pixy.ccc.blocks[2].m_y;
    int y = y1 - y_offset;
    return -1 * y;
  }
  else {
	  return 810;
  }
}
