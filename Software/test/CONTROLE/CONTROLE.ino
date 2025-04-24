
//================================================================================================
//================================================================================================

// Biblio do controle dos motores
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

//------------------------------------------------------------------------------------------------

void setupContr() {
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
}

void controle(int IN1, int IN2, int IN3, int IN4) {
  digitalWrite(A1, IN1);
  digitalWrite(A2, IN2);
  digitalWrite(B1, IN3);
  digitalWrite(B2, IN4);
}

// TODO: achar valores que façam sentido pra isso (testando)
void contrPara() {
  controle(LOW, LOW, LOW, LOW);
}
void contrFren() {
  controle(HIGH, LOW, HIGH, LOW);
}
void contrTras() {
  controle(LOW, HIGH, LOW, HIGH);
}
void contrDire() {
  controle(HIGH, LOW, LOW, HIGH);
}
void contrEsqu() {
  controle(LOW, HIGH, HIGH, LOW);
}

//================================================================================================
//================================================================================================

void setup() {
  
  Serial.begin(9600);

  setupContr();

}

void loop() {
  // put your main code here, to run repeatedly:

  // PONTE H
  Serial.println("girando para la");
  digitalWrite(A1, LOW);
  digitalWrite(A2, HIGH);
  digitalWrite(B1, LOW);
  digitalWrite(B2, HIGH);
  delay(2000);

  Serial.println("girando para ca");
  digitalWrite(A1, HIGH);
  digitalWrite(A2, LOW);
  digitalWrite(B1, HIGH);
  digitalWrite(B2, LOW);
  delay(2000);

  Serial.println("parou");
  digitalWrite(A1, LOW);
  digitalWrite(A2, LOW);
  digitalWrite(B1, LOW);
  digitalWrite(B2, LOW);
  delay(2000);

}
