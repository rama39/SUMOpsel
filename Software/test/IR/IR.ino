//================================================================================================

// Biblio do sensor infra vermelho ky022

// Versão reduzida deste código:
// https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino

#define IR 15
#define LED 23

#include <Arduino.h>
#include <IRremote.h> // include the library

#define comandoIr IrReceiver.decodedIRData.command

bool ON = false;

void setupIr();
void updateOn();
void runIr();

void setupIr(){
  IrReceiver.begin(IR, true);
  pinMode(LED, OUTPUT);
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
    IrReceiver.resume(), // Early enable receiving of the next IR frame
    updateOn();

}

//================================================================================================

void setup() {
  
  Serial.begin(9600);

  setupIr();

}

void loop() {

  runIr();
  delay(10);

}

//================================================================================================