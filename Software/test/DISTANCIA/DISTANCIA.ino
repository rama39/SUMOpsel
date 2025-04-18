
// Biblio dos VL53L0X
#include "../../lib/distancia/dist.h"

void setup() {
  
  Serial.begin(9600);

  setupDist();

}

void loop() {

  read_triple_sensors();
  delay(10);

}



