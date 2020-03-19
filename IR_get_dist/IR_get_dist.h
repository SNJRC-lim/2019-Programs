#ifndef IR_get_dist_H
#define IR_get_dist_H

#include <Arduino.h>

class IR_dist{
	private:
	  byte front_pin = 4;
	  byte right_pin = 5;
	  byte left_pin = 6;
	  byte back_pin = 7;
	  
	public:
	  IR_dist();
	  void attach_pin(byte front, byte right, byte left, byte back);
	  int front();
	  int right();
	  int left();
	  int back();
};

#endif
