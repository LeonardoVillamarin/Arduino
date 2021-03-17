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
  digitalWrite(Anodo, HIGH);
  digitalWrite(Verde, HIGH);
  digitalWrite(Interno, HIGH);
  delay(1000);
  digitalWrite(Verde, LOW);
  digitalWrite(Anodo, LOW);
  digitalWrite(Interno, LOW);
  delay(1000);

  digitalWrite(Interno, HIGH);
  digitalWrite(Anodo, HIGH);
  digitalWrite(Vermelho, HIGH);
  delay(1000);
  digitalWrite(Vermelho, LOW);
  digitalWrite(Anodo, LOW);
  digitalWrite(Interno, LOW);
  delay(1000);

  digitalWrite(Interno, HIGH);
  digitalWrite(Anodo, HIGH);
  digitalWrite(Azul, HIGH);
  delay(1000);
  digitalWrite(Azul, LOW);
  digitalWrite(Anodo, LOW);
  digitalWrite(Interno, LOW);
  delay(1000);
}
