
// Biblio dos VL53L0X
#include "../lib/distancia/dist.h"

// Biblio dos QRE1113
#include "../lib/linha/linha.h"

// Biblio do controle dos motores
#include "../lib/controle/cont.h"

void setup() {
  
  Serial.begin(9600);

  setupContr();

  setupLin();

  setupDist();

}

void loop() {

  // PONTE H
  Serial.println("---");
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(B1, LOW);
  digitalWrite(B2, HIGH);
  printLinhas();
  ledLinhas();
  readSensores(true);
  delay(2000);

  Serial.println("---");
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(B1, HIGH);
  digitalWrite(B2, LOW);
  printLinhas();
  ledLinhas();
  readSensores(true);
  delay(2000);

  Serial.println("---");
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
  printLinhas();
  ledLinhas();
  readSensores(true);
  delay(2000);

}
