const int pir = 4;
const int led = 5;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);
  Serial.begin(115200);
}

void loop() {
  int pirStatus = digitalRead(pir);
  if(pirStatus == HIGH){
    digitalWrite(led, LOW);
    Serial.println("Movimento detectado");
  }
  else{
    digitalWrite(led,HIGH);
  }
}
