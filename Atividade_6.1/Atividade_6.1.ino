const int red = 14;
const int green = 27;
const int blue = 26;

void setup() {
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  digitalWrite(red, LOW); //Como o meu led é anodo, ele acende quando recebe GND ou LOW
  delay(100);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  delay(50);
  digitalWrite(green, LOW);
  delay(50);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  delay(50);
  digitalWrite(green, LOW);
  delay(50);
  digitalWrite(red, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  digitalWrite(blue, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  delay(50);
  digitalWrite(green, LOW);
  delay(50);
  digitalWrite(red, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(100);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  delay(50);
  digitalWrite(green, LOW);
  delay(50);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(red, LOW);
  delay(100);
  digitalWrite(red, HIGH);
  digitalWrite(green, HIGH);
  digitalWrite(blue, HIGH);  
}
