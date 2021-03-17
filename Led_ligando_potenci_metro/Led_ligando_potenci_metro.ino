int pot = 4;
int valorPot;
void setup() {
  Serial.begin(115200);
}

void loop() {
  valorPot = analogRead(pot);
  float   valor = (3.3*valorPot)/4095;
  Serial.println(valor);
  delay(400);
}
