
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
void contrDire() {
    controle(HIGH, LOW, LOW, HIGH);
}
void contrEsqu() {
    controle(LOW, HIGH, HIGH, LOW);
}