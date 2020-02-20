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
float get_angle_orange() {

  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_orange) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - 144.6;
    float y = (y1 - 127.8) * (-1);

    float rad = atan2(y , x);
    return rad;
  }
}


///yellow angle///
float get_angle_yellow() {

  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_yellow) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - 144.6;
    float y = (y1 - 127.8) * (-1);

    float rad = atan2(y , x);
    return rad;
  }
}

///blue angle///
float get_angle_blue() {

  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_blue) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - 144.6;
    float y = (y1 - 127.8) * (-1);

    float rad = atan2(y , x);
    return rad;
  }
}

///orange distance///
float get_dist_orange(){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_orange) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - 144.6;
    float y = (y1 - 127.8) * (-1);
    
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
float get_dist_yellow(){
	static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_yellow) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - 144.6;
    float y = (y1 - 127.8) * (-1);

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
float get_dist_blue(){
	static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_blue) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - 144.6;
    float y = (y1 - 127.8) * (-1);

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

float x_orange(){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_orange) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float x = x1 - 144.6;
   
	return x;
  }
}

float y_orange(){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_orange) {

  
    float y1 = pixy.ccc.blocks[0].m_y;
    float y = (y1 - 127.8) * (-1);
   
	return y;
  }
}	

float x_yellow(){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_yellow) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float x = x1 - 144.6;
   
	return x;
  }
}

float y_yellow(){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_yellow) {

  
    float y1 = pixy.ccc.blocks[0].m_y;
    float y = (y1 - 127.8) * (-1);
   
	return y;
  }
}

float x_blue(){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_blue) {

    float x1 = pixy.ccc.blocks[0].m_x;
    float x = x1 - 144.6;
   
	return x;
  }
}

float y_blue(){
  static int i = 0;
  int j;
  uint16_t blocks;
  char buf[32];


  blocks = pixy.ccc.getBlocks();

  if (pixy.ccc.blocks[0].m_signature == sig_blue) {

  
    float y1 = pixy.ccc.blocks[0].m_y;
    float y = (y1 - 127.8) * (-1);
   
	return y;
  }
}
