//version 0.0

#include <SoftwareSerial.h>
#include <Encoder.h>

///my header file///
#include "IR_get_dist.h"


SoftwareSerial mySerial(4,5); // RX, TX

///IR distance sensor////
float distance[4];
float distance_tmp[4];

///set up encoder///
Encoder myEnc(2, 3);
long oldPosition  = -999;
//////

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
}

void loop() {
  get_distance();
  long newPosition = myEnc.read();
  if (newPosition != oldPosition) {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }
}

void get_distance() {
  for (int i = 0; i < 5; i++) {
    distance_tmp[0] = distance_tmp[0] + get_dist1(); //IR distance sensor forward
  }

  for (int i = 0; i < 5; i++) {
    distance_tmp[1] = distance_tmp[1] + get_dist2(); //IR distance sensor left side
  }

  for (int i = 0; i < 5; i++) {
    distance_tmp[2] = distance_tmp[2] + get_dist3(); //IR distance sensor back
  }

  for (int i = 0; i < 5; i++) {
    distance_tmp[3] = distance_tmp[3] + get_dist4(); //IR distance sensor right side
  }

  for (int j = 0; j < 4; j = j + 1) {
    distance[j] = distance_tmp[j] / 5;
  }
}
