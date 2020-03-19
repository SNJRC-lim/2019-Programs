//version 3.0

#ifndef pixy2_get_color_info_h
#define pixy2_get_color_info_h

#include <Arduino.h>
#include <Pixy2.h>

class pixy2_info{
	private:
	  int sig_orange = 1;
      int sig_yellow = 2;
      int sig_blue = 3;
      
      int x_offset;
      int y_offset;
    
    public:
      pixy2_info();
      void set_offset(int offset_x, int offset_y);
      void attach_sig_num(int orange_sig, int yellow_sig, int blue_sig);

	  int orange_angle();
	  int orange_x();
	  int orange_y();
	  //int orange_dist();
	  
	  int yellow_angle();
	  int yellow_x();
	  int yellow_y();
	  //int yellow_dist();
	  
	  int blue_angle();
	  int blue_x();
	  int blue_y();
	  //int blue_dist();
};

#endif
