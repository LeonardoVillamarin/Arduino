const int red = 26;

void setup() {
  pinMode(red, OUTPUT);
}
void loop() {
  digitalWrite(red, HIGH);
  delay(2000);
  digitalWrite(red, LOW);
}
