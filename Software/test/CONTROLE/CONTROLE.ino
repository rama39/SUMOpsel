
// Biblio do controle dos motores
#include "../../lib/controle/cont.h"

void setup() {
  
  Serial.begin(9600);

  setupContr();

}

void loop() {
  // put your main code here, to run repeatedly:

  // PONTE H
  Serial.println("girando para la");
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(B1, LOW);
  digitalWrite(B2, HIGH);
  delay(2000);

  Serial.println("girando para ca");
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(B1, HIGH);
  digitalWrite(B2, LOW);
  delay(2000);

  Serial.println("parou");
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
  delay(2000);

}
