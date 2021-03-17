const int red = 26;
const int green = 27;
const int blue = 14;

const int freq = 5000;
const int redChannel = 0;
const int greenChannel = 1;
const int blueChannel = 2;
const int resolution = 8;

void setup() {
  ledcSetup(redChannel, freq, resolution);
  ledcSetup(greenChannel, freq, resolution);
  ledcSetup(blueChannel, freq, resolution);

  ledcAttachPin(red, redChannel);
  ledcAttachPin(green, greenChannel);
  ledcAttachPin(blue, blueChannel);
}

void loop() {
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle+=2){   
    ledcWrite(redChannel, dutyCycle);
    delay(15);
  }
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle+=2){   
    ledcWrite(greenChannel, dutyCycle);
    delay(15);
  }
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle+=2){   
    ledcWrite(blueChannel, dutyCycle);
    delay(15);
  }

  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle-=2){
    ledcWrite(redChannel, dutyCycle);  
    delay(15);
  }
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle-=2){
    ledcWrite(greenChannel, dutyCycle);  
    delay(15);
  }
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle-=2){
    ledcWrite(blueChannel, dutyCycle); 
    delay(15);
  }
}
