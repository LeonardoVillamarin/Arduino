const int input = 35;

void setup() {
    Serial.begin(115200);
}

void loop() {
    dacWrite(26,150);
    float valorInput = analogRead(input);
    float valor = (3.3*valorInput)/4095;
    Serial.println(valor);
    delay(40);
}
