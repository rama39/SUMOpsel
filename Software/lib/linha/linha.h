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

#include "linha.cpp"