
//================================================================================================

// Biblio dos QRE1113
/*
Biblioteca simples para leitura de dois sensores de linha QRE1113
*/

#define LIN1 4
#define LIN2 13

#define LED 23

#define boolLinha(leitura) ((leitura) < 2000);

bool linha1, linha2;

void readLinhas();
void printLinhas();
void ledLinhas();

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

void ledLinhas() {
  analogWrite(LED, 120*linha1 + 120*linha2);
}

//================================================================================================

void setup() {
  
  Serial.begin(9600);

  pinMode(LED, OUTPUT);

  setupLin();

}

void loop() {

  readLinhas();
  printLinhas();
  ledLinhas();

  delay(10);
}
