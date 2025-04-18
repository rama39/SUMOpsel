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

#include "cont.cpp"