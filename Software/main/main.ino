
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

  Serial.println("---");
  readSensores(true);
  readLinhas(true);

  if(TARGET(measure2)) {
    contrFren();
    goto skip;
  }
  if(TARGET(measure1)) {
    contrEsqu();
    goto skip;
  }
  if(TARGET(measure3)) {
    contrDire();
    goto skip;
  }

  if(linha1) {
    contrTras();
    goto skip;
  }
  if(linha2) {
    contrFren();
    goto skip;
  }





  skip:
  delay(10);

}
