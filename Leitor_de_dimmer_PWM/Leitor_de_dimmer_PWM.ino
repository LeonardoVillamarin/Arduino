const int in = 35;
const int out = 14;
const int freq = 105000;
const int outChannel = 0;
const int resolution = 8;

void setup() {
    Serial.begin(115200);
    ledcSetup(outChannel, freq, resolution);
    ledcAttachPin(out, outChannel);
}

void loop() {
    ledcWrite(outChannel, 150);
    float valorIn = analogRead(in);
    float valor = (3.3*valorIn)/4095;
    Serial.println(valor);
  }
