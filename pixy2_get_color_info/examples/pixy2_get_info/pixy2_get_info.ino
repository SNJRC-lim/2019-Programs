#include <pixy2_get_color_info.h>

pixy2_info pixy2_info;

int x_offset = 151;
int y_offset = 130;

void setup() {
  Serial.begin(115200);
  pixy2_info.attach_sig_num(0,1,2);
  pixy2_info.set_offset(x_offset,y_offset);
}

void loop() {
  int angle_orange = pixy2_info.orange_angle();
  Serial.println(angle_orange);
}
