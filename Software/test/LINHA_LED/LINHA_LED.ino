
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

void setup() {
  
  Serial.begin(9600);

  setupLin();

}

void loop() {

  printLinha();
  ledLinhas();
  delay(10);

}
