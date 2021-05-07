
void setup() {
  Serial.begin(115200);
}

void loop() {
  float tensao = analogRead(15);
  tensao = (3.3*tensao)/4095;
  Serial.println(tensao);
}
