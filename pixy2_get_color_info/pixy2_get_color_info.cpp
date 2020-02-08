//version 1.0

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

    int x1 = pixy.ccc.blocks[0].m_x;
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

    int x1 = pixy.ccc.blocks[0].m_x;
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

    int x1 = pixy.ccc.blocks[0].m_x;
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

    int x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - 144.6;
    float y = (y1 - 127.8) * (-1);

    float dist = sqrt(x*x + y*y);
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

    int x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - 144.6;
    float y = (y1 - 127.8) * (-1);

    float dist = sqrt(x*x + y*y);
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

    int x1 = pixy.ccc.blocks[0].m_x;
    float y1 = pixy.ccc.blocks[0].m_y;
    float x = x1 - 144.6;
    float y = (y1 - 127.8) * (-1);

    float dist = sqrt(x*x + y*y);
    return dist;
  }
}  
