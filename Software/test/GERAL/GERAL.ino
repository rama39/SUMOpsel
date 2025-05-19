//================================================================================================

// Definição de pinos

#define DIST_XSHUT_1 5
#define DIST_XSHUT_2 17
#define DIST_XSHUT_3 16

#define LIN1 4
#define LIN2 13

#define A1 25
#define A2 26
#define B1 27
#define B2 14

#define IR 15

#define LED 23

#define RADIO 32

//================================================================================================

// Sensores de distância

// Configuração de endereço i2c implementada neste link, eu só extrapolei para 3 sensores
//   https://github.com/adafruit/Adafruit_VL53L0X/blob/master/examples/vl53l0x_dual/vl53l0x_dual.ino

#include "Adafruit_VL53L0X.h"

// address we will assign if dual sensor is present
#define LOX1_ADDRESS 0x30
#define LOX2_ADDRESS 0x31
#define LOX3_ADDRESS 0x32

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
void _printDistInd(string, VL53L0X_RangingMeasurementData_t &);
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

// Sensores de linha

#define boolLinha(leitura) ((leitura) < 2000);

bool linha1, linha2;

void readLinhas();
void printLinhas();
//void ledLinhas();

void readLinhas() {
  linha1 = boolLinha(analogRead(LIN1));
  linha2 = boolLinha(analogRead(LIN2));
}

void printLinhas() {
  //TODO: aprender formatação de string pra printar mais facil
  Serial.print("linha: ");
  Serial.print(analogRead(LIN1));
  Serial.print(" ");
  Serial.println(analogRead(LIN2));
}

/*void ledLinhas() {
  analogWrite(LED, 120*readLinha(linha1)+120*readLinha(linha2));
}*/

//================================================================================================

// Controle dos motores

void setupCont(); //serving cont
void escreve(int, int, int, int);

void setupCont() {
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
}

void escreve(int _A1, int _A2, int _B1, int _B2) {
  digitalWrite(A1, _A1);
  digitalWrite(A2, _A2);
  digitalWrite(B1, _B1);
  digitalWrite(B2, _B2);
}

void frente() {
  Serial.println("frente");
  escreve(LOW, HIGH, LOW, HIGH);
}

void reverso() {
  Serial.println("reverso");
  escreve(HIGH, LOW, HIGH, LOW);
}

void para() {
  Serial.println("parou");
  escreve(LOW, LOW, LOW, LOW);
}

//================================================================================================

// Sensor IR (Infravermelho)

// Versão reduzida deste código:
// https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino

#include <Arduino.h>
#include <IRremote.h>

#define comandoIr IrReceiver.decodedIRData.command

bool ON = false;

void setupIr();
void updateOn();
void runIr();

void setupIr() {
  IrReceiver.begin(IR, true);
}

void updateOn() {
  switch (comandoIr) {
    case 0x3:
      ON = true;
    break;
    case 0x2:
      ON = false;
    break;
    default:break;
  }
  digitalWrite(LED, ON ? HIGH : LOW);
}

void runIr() {
  if (IrReceiver.decode())
    IrReceiver.resume(),
    updateOn();
}

//================================================================================================

// 'main'

void setup() {
  
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  pinMode(LIN1, INPUT);
  pinMode(LIN2, INPUT);

  setupCont();

  setupDist();
  
  setupIr();

}


void loop() {

  static int test_mode = 0;
  if(ON) {
    // PONTE H
    switch(test_mode) {
      case 0:
        frente();
      break; case 1:
        reverso();

      break; case 2:
        para();
    }
    test_mode++;
    if(test_mode == 3) test_mode = 0;

    readLinhas();
    printLinhas();

    readDist();
    printDist();

    delay(500);
  }
  else {
    para();
  }

  runIr();
  delay(25);

}
