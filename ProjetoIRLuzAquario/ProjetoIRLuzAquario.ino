const int led = 4;
const int recv = 2;
const int anodo = 32;
const int tensao = 15;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
}

void loop() {
  float valorInput = analogRead(tensao);
  float valor = (3.3*float(valorInput))/4095.0;
  //float valorled = analogRead(4);
  if(valor >= 0.0 && valor < 1.0){
    //Serial.println(valorled);
    digitalWrite(led, HIGH);
  }
  if(valor > 1.0){
    digitalWrite(led, LOW);
    //Serial.println(valorled);
  }
  Serial.println(valor);
}
