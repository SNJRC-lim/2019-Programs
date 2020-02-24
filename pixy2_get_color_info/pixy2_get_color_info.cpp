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
float get_angle_orange(float x_offset,float y_offset) {

  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_orange) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - x_offset;
    float y = (y1 - y_offset) * (-1);

    float rad = atan2(y , x);
    return -1 * rad;
  }
}


///yellow angle///
float get_angle_yellow(float x_offset,float y_offset) {

  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_yellow) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - x_offset;
    float y = (y1 - y_offset) * (-1);

    float rad = atan2(y , x);
    return -1 * rad;
  }
}

///blue angle///
float get_angle_blue(float x_offset,float y_offset) {

  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_blue) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - x_offset;
    float y = (y1 - y_offset) * (-1);

    float rad = atan2(y , x);
    return -1 * rad;
  }
}

///orange distance///
float get_dist_orange(float x_offset,float y_offset){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_orange) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - x_offset;
    float y = (y1 - y_offset) * (-1);
    
    float dist0 = 2 *  sqrt(x*x + y*y);
    float dist5 = 151- dist0;
    float dist1 = sqrt(dist5);
    float dist2 = 306.1862 * dist1;
    float dist3 = 3159 - dist2;
    float dist = dist3 /45;
    
    if(dist0 > 151){
		dist = 65;
	}
    
    return dist;
  }
}  

///yellow distance///
float get_dist_yellow(float x_offset,float y_offset){
	static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_yellow) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - x_offset;
    float y = (y1 - y_offset) * (-1);

    float dist0 = 2 *  sqrt(x*x + y*y);
    float dist5 = 151- dist0;
    float dist1 = sqrt(dist5);
    float dist2 = 306.1862 * dist1;
    float dist3 = 3159 - dist2;
    float dist = dist3 /45;
    
    if(dist0 > 151){
		dist = 65;
	}
    return dist;
  }
}  

///blue distance///
float get_dist_blue(float x_offset,float y_offset){
	static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_blue) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - x_offset;
    float y = (y1 - y_offset) * (-1);

    float dist0 = 2 *  sqrt(x*x + y*y);
    float dist5 = 151- dist0;
    float dist1 = sqrt(dist5);
    float dist2 = 306.1862 * dist1;
    float dist3 = 3159 - dist2;
    float dist = dist3 /45;
    
    if(dist0 > 151){
		dist = 65;
	}
    return dist;
  }
}  

float x_orange(float x_offset,float y_offset){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_orange) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float x = x1 - x_offset;
   
	return -1 * x;
  }
}

float y_orange(float x_offset,float y_offset){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_orange) {

  
    float y1 = pixy.ccc.blocks[0].m_y;
    float y = (y1 - y_offset) * (-1);
   
	return -1 * y;
  }
}	

float x_yellow(float x_offset,float y_offset){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_yellow) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float x = x1 - x_offset;
   
	return -1 * x;
  }
}

float y_yellow(float x_offset,float y_offset){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_yellow) {

  
    float y1 = pixy.ccc.blocks[0].m_y;
    float y = (y1 - y_offset) * (-1);
   
	return -1 * y;
  }
}

float x_blue(float x_offset,float y_offset){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_blue) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float x = x1 - x_offset;
   
	return -1 * x;
  }
}

float y_blue(float x_offset,float y_offset){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_blue) {

  
    float y1 = pixy.ccc.blocks[0].m_y;
    float y = (y1 - y_offset) * (-1);
   
	return -1 * y;
  }
}
