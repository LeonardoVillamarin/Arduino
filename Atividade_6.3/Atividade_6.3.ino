const int red = 14;
const int green = 27;
const int blue = 26;

void setup() {
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  xTaskCreate(redLed, "redLed", 10000, NULL, 1, NULL);
  xTaskCreate(greenLed, "greenLed", 10000, NULL, 1, NULL);
  xTaskCreate(blueLed, "blueLed", 10000, NULL, 1, NULL);
}

void loop() {
}
void redLed(void *) {
  while(true) {
    digitalWrite(red, LOW);
    delay(100);
    digitalWrite(red, HIGH);
    delay(100);
  }
  vTaskDelete(NULL);
}
void greenLed(void *) {
  while(true) {
    digitalWrite(green, LOW);
    delay(250);
    digitalWrite(green, HIGH);
    delay(250);
  }
  vTaskDelete(NULL);
}
void blueLed(void *) {
  while(true){
    digitalWrite(blue, LOW);
    delay(1000);
    digitalWrite(blue, HIGH);
    delay(1000);
  }
  vTaskDelete(NULL);
}
