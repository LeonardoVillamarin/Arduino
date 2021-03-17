const int red = 26;

const int freq = 5000;
const int redChannel = 0;
const int resolution = 8;

void setup() {
  ledcSetup(redChannel, freq, resolution);
  ledcAttachPin(red, redChannel);
}

void loop() {
  for(int dutyCycle = 131; dutyCycle <= 255; dutyCycle++){   
    ledcWrite(redChannel, dutyCycle);
    delay(8);
  }
  for(int dutyCycle = 255; dutyCycle >= 131; dutyCycle--){
    ledcWrite(redChannel, dutyCycle); 
    delay(8);
  }
}
