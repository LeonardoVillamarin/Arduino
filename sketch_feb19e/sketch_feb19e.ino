const int pin = 12;
int tensao;
float valor;

void setup() {
    Serial.begin(115200);
}

void loop() {
    for(int t = 0; t<256; t--){
        dacWrite(26, t);
        tensao = analogRead(pin);
        valor = (3.3*tensao)/4095;
        Serial.println(valor);
        delay(8);
        
    }
    for(int t = 256; t>0; t--){
        dacWrite(26, t);
        tensao = analogRead(pin);
        valor = (3.3*tensao)/4095;
        Serial.println(valor);
        delay(8);
    }
}
