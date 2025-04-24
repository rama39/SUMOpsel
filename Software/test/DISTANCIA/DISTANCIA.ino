
//================================================================================================
//================================================================================================
// Biblio dos VL53L0X
/*
    Biblioteca que controla a incialização e leitura de três sensores TOF VL53L0X
*/

// Usa biblioteca Adafruit como base
#include "Adafruit_VL53L0X.h"

// pin number 
#define DIST_XSHUT_1 4
#define DIST_XSHUT_2 2
#define DIST_XSHUT_3 15

// address we will assign sensors
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

void setupDist();

void setID();
void readSensores(bool);

//------------------------------------------------------------------------------------------------
/*
  Quase igual ao código encontrado em:
  https://github.com/adafruit/Adafruit_VL53L0X/blob/master/examples/vl53l0x_dual/vl53l0x_dual.ino
  <3 obg comunidade open source 🤝 <3
*/

// objects for the vl53l0x
Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// this holds the measurement
VL53L0X_RangingMeasurementData_t measure1;
VL53L0X_RangingMeasurementData_t measure2;
VL53L0X_RangingMeasurementData_t measure3;

void setupDist() {
  pinMode(DIST_XSHUT_1, OUTPUT);
  pinMode(DIST_XSHUT_2, OUTPUT);
  pinMode(DIST_XSHUT_3, OUTPUT);

  Wire.begin(21, 22); 

  setID();
}

void setID() {
  // all reset
  digitalWrite(DIST_XSHUT_1, LOW);    
  digitalWrite(DIST_XSHUT_2, LOW);
  digitalWrite(DIST_XSHUT_3, LOW);
  delay(10);
  // all unreset
  digitalWrite(DIST_XSHUT_1, HIGH);
  digitalWrite(DIST_XSHUT_2, HIGH);
  digitalWrite(DIST_XSHUT_3, HIGH);
  delay(10);

  // activating LOX1 and resetting LOX2 and LOX3
  digitalWrite(DIST_XSHUT_1, HIGH);
  digitalWrite(DIST_XSHUT_2, LOW);
  digitalWrite(DIST_XSHUT_3, LOW);
  // initing LOX1
  if(!lox1.begin(LOX1_ADDRESS)) {
    Serial.println(F("Failed to boot first VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX2
  digitalWrite(DIST_XSHUT_2, HIGH);
  delay(10);
  //initing LOX2
  if(!lox2.begin(LOX2_ADDRESS)) {
    Serial.println(F("Failed to boot second VL53L0X"));
    while(1);
  }
  delay(10);

  // activating LOX3
  digitalWrite(DIST_XSHUT_3, HIGH);
  delay(10);
  //initing LOX3
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }

}

// retorna leitura do sensor em milimetros
#define MM(x) mm(&x)
int mm(const VL53L0X_RangingMeasurementData_t *measure) {
  return measure->RangeMilliMeter;
}

// TODO: fazer certo
#define TARGET(x) target(&x)
bool target(const VL53L0X_RangingMeasurementData_t *measure) {
  return measure1.RangeStatus == 4 || mm(measure) < 100;
}

void readSensores(bool print) {
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!

  if(!print) return;

  // print sensor one reading
  Serial.print("1: ");
  if(measure1.RangeStatus != 4) {     // if not out of range
    Serial.print(MM(measure1));
  } else {
    Serial.print("Out of range");
  }
  
  Serial.print(" ");

  // print sensor two reading
  Serial.print("2: ");
  if(measure2.RangeStatus != 4) {
    Serial.print(MM(measure2));
  } else {
    Serial.print("Out of range");
  }
  
  Serial.print(" ");

  // print sensor three reading
  Serial.print("3: ");
  if(measure3.RangeStatus != 4) {
    Serial.print(MM(measure3));
  } else {
    Serial.print("Out of range");
  }
  
  Serial.println();
}
//================================================================================================
//================================================================================================

void setup() {
  
  Serial.begin(9600);

  setupDist();

}

void loop() {

  read_triple_sensors();
  delay(10);

}



