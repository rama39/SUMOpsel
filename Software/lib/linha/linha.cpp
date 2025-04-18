
int linha1, linha2;

void setupLin(){
    pinMode(LIN1, INPUT);
    pinMode(LIN2, INPUT);

    pinMode(LED, OUTPUT);
}

void printLinha() {
    linha1 = analogRead(LIN1);
    linha2 = analogRead(LIN2);
    Serial.print("linha: ");
    Serial.print(linha1);
    Serial.print(" ");
    Serial.println(linha2);
}
bool readLinha(int linhai) {
    return linhai < 2000;
}
void ledLinhas() {
    analogWrite(LED, 120*readLinha(linha1)+120*readLinha(linha2));
}

bool lin1() {
    return analogRead(LIN1) > 2000;
}
bool lin2() {
    return analogRead(LIN2) > 2000;
}