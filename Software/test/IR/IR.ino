
// Biblio do sensor infra vermelho ky022

#include <Arduino.h>
#include <IRremote.h> // include the library

#define IR 15
#define LED 23

void setupIr();
void updateIr();
void runIr();
uint16_t commandIr();

void setupIr(){

  IrReceiver.begin(IR, true);

  pinMode(LED, OUTPUT);

}

bool ON = false;

void updateIr() {
  if (commandIr() == 0x3) {
    ON = true;
  } else if (commandIr() == 0x02) {
    ON = false;
  }
}

void runIr() {

  if (IrReceiver.decode())
    IrReceiver.resume(), // Early enable receiving of the next IR frame
    updateIr();

}

uint16_t commandIr() {
  return IrReceiver.decodedIRData.command;
}



void setup() {
  
  Serial.begin(9600);

  setupIr();

}

void loop() {

  runIr();

  digitalWrite(LED, ON ? HIGH : LOW);

  delay(10);

}