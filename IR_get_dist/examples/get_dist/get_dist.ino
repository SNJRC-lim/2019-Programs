#include <IR_get_dist.h>

IR_dist IR_dist;

int dist[4];
void setup() {
  Serial.begin(9600);
}

void loop() {
  dist[0] = IR_dist.front();
  dist[1] = IR_dist.right();
  dist[2] = IR_dist.left();
  dist[3] = IR_dist.back();
  for (int i = 0; i < 5; i = i + 1) {
    Serial.println(dist[i]);
  }
}
