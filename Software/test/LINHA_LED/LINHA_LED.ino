
// Biblio dos QRE1113
#include "../../lib/linha/linha.h"

void setup() {
  
  Serial.begin(9600);

  setupLin();

}

void loop() {

  printLinha();
  ledLinhas();
  delay(10);

}
