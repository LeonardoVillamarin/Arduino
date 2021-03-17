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
    delay(50);
    digitalWrite(red, HIGH);
    delay(50);
  }
  vTaskDelete(NULL);
}
void greenLed(void *) {
  while(true) {
    digitalWrite(green, LOW);
    delay(300);
    digitalWrite(green, HIGH);
    delay(300);
  }
  vTaskDelete(NULL);
}
void blueLed(void *) {
  while(true){
    digitalWrite(blue, LOW);
    delay(2000);
    digitalWrite(blue, HIGH);
    delay(2000);
  }
  vTaskDelete(NULL);
}
