//version 0.0

#include "White_line.h"
#include "Arduino.h"

void White_line() {
  volatile bool line1 = digitalRead(A0); //white line forward
  volatile bool line2 = digitalRead(A1); //white line left side
  volatile bool line3 = digitalRead(A2); //white line back
  volatile bool line4 = digitalRead(A3); //white line right side
 
   if (line1 == 1) {
      digitalWrite (22, HIGH);
      digitalWrite (26, LOW);
      analogWrite  (5, 255);

      digitalWrite (23, HIGH);
      digitalWrite (27, LOW);
      analogWrite  (6, 255);

      digitalWrite (24, LOW);
      digitalWrite (28, HIGH);
      analogWrite  (7, 255);

      digitalWrite (25, LOW);
      digitalWrite (29, HIGH);
      analogWrite  (8, 255);

      line1 = digitalRead(A0);
      line2 = digitalRead(A1); 
      line3 = digitalRead(A2);
      line4 = digitalRead(A3);
    }

   if (line2 == 1) {
      digitalWrite (22, LOW);
      digitalWrite (26, HIGH);
      analogWrite  (5, 255);

      digitalWrite (23, HIGH);
      digitalWrite (27, LOW);
      analogWrite  (6, 255);

      digitalWrite (24, HIGH);
      digitalWrite (28, LOW);
      analogWrite  (7, 255);

      digitalWrite (25, LOW);
      digitalWrite (29, HIGH);
      analogWrite  (8, 255);

      line1 = digitalRead(A0);
      line2 = digitalRead(A1); 
      line3 = digitalRead(A2);
      line4 = digitalRead(A3);
    }

    if (line3 == 1) {
      digitalWrite (22, LOW);
      digitalWrite (26, HIGH);
      analogWrite  (5, 255);

      digitalWrite (23, LOW);
      digitalWrite (27, HIGH);
      analogWrite  (6, 255);

      digitalWrite (24, HIGH);
      digitalWrite (28, LOW);
      analogWrite  (7, 255);

      digitalWrite (25, HIGH);
      digitalWrite (29, LOW);
      analogWrite  (8, 255);

      line1 = digitalRead(A0);
      line2 = digitalRead(A1);
      line3 = digitalRead(A2);
      line4 = digitalRead(A3);
    }

    if (line4 == 1) {
      digitalWrite (22, HIGH);
      digitalWrite (26, LOW);
      analogWrite  (5, 255);

      digitalWrite (23, LOW);
      digitalWrite (27, HIGH);
      analogWrite  (6, 255);

      digitalWrite (24, LOW);
      digitalWrite (28, HIGH);
      analogWrite  (7, 255);

      digitalWrite (25, HIGH);
      digitalWrite (29, LOW);
      analogWrite  (8, 255);

      line1 = digitalRead(A0);
      line2 = digitalRead(A1); 
      line3 = digitalRead(A2);
      line4 = digitalRead(A3);
   }
   
 }
