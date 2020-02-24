//version 0.1

#include "White_line.h"
#include "Arduino.h"

void White_line() {
  volatile bool line1 = digitalRead(A2); //white line forward
  volatile bool line2 = digitalRead(A3); //white line left side
  volatile bool line3 = digitalRead(A1); //white line back
  volatile bool line4 = digitalRead(A0); //white line right side
 
   if (line1 == 1) {
      digitalWrite (31, HIGH);
      digitalWrite (33, LOW);
      analogWrite  (7, 125);

      digitalWrite (35, HIGH);
      digitalWrite (37, LOW);
      analogWrite  (8, 125);

      digitalWrite (27, LOW);
      digitalWrite (25, HIGH);
      analogWrite  (6, 125);

      digitalWrite (23, LOW);
      digitalWrite (25, HIGH);
      analogWrite  (5, 125);

      line1 = digitalRead(A0);
      line2 = digitalRead(A1); 
      line3 = digitalRead(A2);
      line4 = digitalRead(A3);
    }

   if (line2 == 1) {
      digitalWrite (31, LOW);
      digitalWrite (33, HIGH);
      analogWrite  (7, 125);

      digitalWrite (35, HIGH);
      digitalWrite (37, LOW);
      analogWrite  (8, 125);

      digitalWrite (27, HIGH);
      digitalWrite (25, LOW);
      analogWrite  (6, 125);

      digitalWrite (23, LOW);
      digitalWrite (25, HIGH);
      analogWrite  (5, 125);

      line1 = digitalRead(A0);
      line2 = digitalRead(A1); 
      line3 = digitalRead(A2);
      line4 = digitalRead(A3);
    }

    if (line3 == 1) {
      digitalWrite (31, LOW);
      digitalWrite (33, HIGH);
      analogWrite  (7, 125);

      digitalWrite (35, LOW);
      digitalWrite (37, HIGH);
      analogWrite  (8, 125);

      digitalWrite (27, HIGH);
      digitalWrite (25, LOW);
      analogWrite  (6, 125);

      digitalWrite (23, HIGH);
      digitalWrite (25, LOW);
      analogWrite  (5, 125);

      line1 = digitalRead(A0);
      line2 = digitalRead(A1);
      line3 = digitalRead(A2);
      line4 = digitalRead(A3);
    }

    if (line4 == 1) {
      digitalWrite (31, HIGH);
      digitalWrite (33, LOW);
      analogWrite  (7, 125);

      digitalWrite (35, LOW);
      digitalWrite (37, HIGH);
      analogWrite  (8, 125);

      digitalWrite (27, LOW);
      digitalWrite (25, HIGH);
      analogWrite  (6, 125);

      digitalWrite (23, HIGH);
      digitalWrite (25, LOW);
      analogWrite  (5, 125);

      line1 = digitalRead(A0);
      line2 = digitalRead(A1); 
      line3 = digitalRead(A2);
      line4 = digitalRead(A3);
   }
   
 }
