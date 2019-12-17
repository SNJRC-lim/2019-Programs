#include <IR_get_dist.h>

float dist[4];
void setup() {
  Serial.begin(9600);
}

void loop() {
  dist[0] = get_dist1;
  dist[1] = get_dist2;
  dist[2] = get_dist3;
  dist[3] = get_dist4;
  for (int i = 0; i < 5; i = i + 1) {
    Serial.println(dist[i]);
  }
}
