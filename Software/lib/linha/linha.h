/*
    Biblioteca simples para leitura de dois sensores de linha QRE1113
*/

#define LIN1 35
#define LIN2 34

#define LED 23

void setupLin();

void printLinha();
bool readLinha(int);
void ledLinhas();

bool lin1();
bool lin2();

#include "linha.cpp"