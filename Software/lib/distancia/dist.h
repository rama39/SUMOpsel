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
void read_triple_sensors();

#include "dist.cpp"