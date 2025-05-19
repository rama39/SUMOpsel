
//================================================================================================
// Biblio dos VL53L0X
/*
  Biblioteca que controla a incialização e leitura de três sensores TOF VL53L0X
*/

// pin number 
#define DIST_XSHUT_1 5
#define DIST_XSHUT_2 17
#define DIST_XSHUT_3 16

// Usa biblioteca Adafruit como base
#include "Adafruit_VL53L0X.h"

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

void setupDist();
void readDist();
void _printDistInd(string nome, VL53L0X_RangingMeasurementData_t &);
void printDist();

void setupDist() {
  
  // Configura pinos xshut
  pinMode(DIST_XSHUT_1, OUTPUT);
  pinMode(DIST_XSHUT_2, OUTPUT);
  pinMode(DIST_XSHUT_3, OUTPUT);
  
  // Configura I2C
  Wire.begin(21, 22); 

  // Configura ID de cada sensor VL53L0X

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

  // activating LOX3
  digitalWrite(DIST_XSHUT_3, HIGH);
  delay(10);
  //initing LOX3
  if(!lox3.begin(LOX3_ADDRESS)) {
    Serial.println(F("Failed to boot third VL53L0X"));
    while(1);
  }
}

void readDist() {
  
  lox1.rangingTest(&measure1, false); // pass in 'true' to get debug data printout!
  lox2.rangingTest(&measure2, false); // pass in 'true' to get debug data printout!
  lox3.rangingTest(&measure3, false); // pass in 'true' to get debug data printout!

}

void _printDistInd(string nome, VL53L0X_RangingMeasurementData_t &measurex) {

  // print sensor reading
  Serial.print(nome);
  Serial.print(": ");
  if(measurex.RangeStatus != 4) {     // if not out of range
    Serial.print(measurex.RangeMilliMeter);
  } else {
    Serial.print("Out of range");
  }
  
  Serial.print(" ");
}
void printDist() {

  // print sensor one reading
  _printDistInd("1", measure1);

  // print sensor two reading
  _printDistInd("2", measure2);

  // print sensor three reading
  _printDistInd("3", measure3);
  
  Serial.println();

}

//================================================================================================

void setup() {
  
  Serial.begin(9600);

  setupDist();

}

void loop() {

  readDist();
  printDist();
  delay(10);

}

//================================================================================================