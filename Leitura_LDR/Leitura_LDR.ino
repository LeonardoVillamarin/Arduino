const int ldr = 15;
 
void setup() {
  Serial.begin(115200);
  pinMode(ldr, INPUT);
}
 
void loop() {
  int leitura = analogRead(ldr);
  if (leitura < 1365)
    Serial.println("Luminosidade baixa");
  else if (leitura >= 1365 && leitura < 2730)
    Serial.println("Luminosidade média");
  else if(leitura >= 2730)
    Serial.println("Luminosidade alta");
  delay(1000);
}
