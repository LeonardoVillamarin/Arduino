int Vermelho = 18;
int Verde = 19;
int Azul = 21;
int Anodo = 5;
int Interno = 2;

void setup() {
  pinMode(Verde, OUTPUT);
  pinMode(Vermelho, OUTPUT);
  pinMode(Azul, OUTPUT);
  pinMode(Anodo, OUTPUT);        //Criei o anodo para o led não ficar sempre ligado (Se eu conecta-se no pin 3v3 ele ficaria 100% do tempo ligado)
  pinMode(Interno, OUTPUT);
}

void loop() {
  digitalWrite(Interno, HIGH);
  delay(1000);
  digitalWrite(Interno, LOW);
  digitalWrite(Anodo, HIGH);
  digitalWrite(Verde, HIGH);
  delay(1000);
  digitalWrite(Interno, HIGH);
  delay(1000);
  digitalWrite(Interno, LOW);
  digitalWrite(Verde, LOW);
  digitalWrite(Anodo, LOW);
  delay(1000);
  digitalWrite(Interno, HIGH);
  delay(1000);
  digitalWrite(Interno, LOW);
  digitalWrite(Anodo, HIGH);
  digitalWrite(Vermelho, HIGH);
  delay(1000);
  digitalWrite(Interno, HIGH);
  delay(1000);
  digitalWrite(Interno, LOW);
  digitalWrite(Anodo, LOW);
  digitalWrite(Vermelho, LOW);
  delay(1000);
  digitalWrite(Interno, HIGH);
  delay(1000);
  digitalWrite(Interno, LOW);
  digitalWrite(Azul, HIGH);
  digitalWrite(Anodo, HIGH);
  delay(1000);
  digitalWrite(Interno, HIGH);
  delay(1000);
  digitalWrite(Interno, LOW);
  digitalWrite(Anodo, LOW);
  digitalWrite(Azul, LOW);
  delay(1000);
}
