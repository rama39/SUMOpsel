
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

// Biblio dos QRE1113
/*
Biblioteca simples para leitura de dois sensores de linha QRE1113
*/

#define LIN1 35
#define LIN2 34

#define LED 23

void setupLin();
void readLinhas(bool);
bool Li(int);
void printLinhas();
void ledLinhas();

bool lin1();
bool lin2();

//------------------------------------------------------------------------------------------------

int linha1, linha2;

void setupLin(){
    pinMode(LIN1, INPUT);
    pinMode(LIN2, INPUT);

    pinMode(LED, OUTPUT);
}

void readLinhas(bool print) {
    linha1 = analogRead(LIN1);
    linha2 = analogRead(LIN2);
    if(print) printLinhas();
}
bool Li(int linhai) {
    return linhai > 2000;
}
void printLinhas() {
    // TODO usar F("")
    Serial.print("linha: ");
    Serial.print(linha1);
    Serial.print(" ");
    Serial.println(linha2);
}
void ledLinhas() {
    analogWrite(LED, 120*readLinha(linha1)+120*readLinha(linha2));
}

bool lin1() {
    return linha1 > 2000;
}
bool lin2() {
    return linha2 > 2000;
}

//================================================================================================
//================================================================================================

// Biblio do controle dos motores
/*
    Biblioteca para controle dos motores do robô com ponte H l298n mini
*/

#define A1 25
#define A2 26
#define B1 27
#define B2 14

void setupContr();

void controle(int,int,int,int);
void contrPara();
void contrFren();
void contrDire();
void contrEsqu();

//------------------------------------------------------------------------------------------------

void setupContr() {
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
}

void controle(int IN1, int IN2, int IN3, int IN4) {
  digitalWrite(A1, IN1);
  digitalWrite(A2, IN2);
  digitalWrite(B1, IN3);
  digitalWrite(B2, IN4);
}

// TODO: achar valores que façam sentido pra isso (testando)
void contrPara() {
  controle(LOW, LOW, LOW, LOW);
}
void contrFren() {
  controle(HIGH, LOW, HIGH, LOW);
}
void contrTras() {
  controle(LOW, HIGH, LOW, HIGH);
}
void contrDire() {
  controle(HIGH, LOW, LOW, HIGH);
}
void contrEsqu() {
  controle(LOW, HIGH, HIGH, LOW);
}

//================================================================================================
//================================================================================================

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
