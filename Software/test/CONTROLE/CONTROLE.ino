
//================================================================================================

// Biblio do controle dos motores
/*
  Biblioteca para controle dos motores do robô com ponte H l298n mini
*/

#define A1 25
#define A2 26
#define B1 27
#define B2 14

void setupCont();
void escreve(int, int, int, int);
void frente();
void reverso();
void direita();
void esquerda();
void para();

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

// TODO: achar valores que façam sentido pra isso

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

void setup() {
  
  Serial.begin(9600);

  setupContr();

}

void loop() {

  static int test_mode = 0;
  
  switch(test_mode) {
    case 0:
      frente();
    break; case 1:
      reverso();

    break; default:
      para();
  }

  test_mode++;
  if(test_mode == 3) test_mode = 0;

}

//================================================================================================