
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
  Serial.println("girando para la");
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(B1, LOW);
  digitalWrite(B2, HIGH);
  printLinha();
  ledLinhas();
  readSensores(true);
  delay(2000);

  Serial.println("girando para ca");
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(B1, HIGH);
  digitalWrite(B2, LOW);
  printLinha();
  ledLinhas();
  readSensores(true);
  delay(2000);

  Serial.println("parou");
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
  printLinha();
  ledLinhas();
  readSensores(true);
  delay(2000);

}
