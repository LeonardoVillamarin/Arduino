const int red = 14;
const int green = 27;
const int blue = 26;

void setup() {
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  int status2 = 1;
  int status3 = 1;
  for(int i = 1; i < 161; i++){
    if(i == 1){
      digitalWrite(green, LOW); //Como o meu led é anodo, ele acende quando recebe GND ou LOW
      digitalWrite(blue, LOW);
    }
    if(i % 2 != 0){
      digitalWrite(red, LOW);
    }
    if(i % 2 == 0){
      digitalWrite(red, HIGH);
    }
    if(i % 6 == 0){
      if(!status2){
        digitalWrite(green, LOW);
        status2 = 1;
      }
      else if(status2){
        digitalWrite(green, HIGH);
        status2 = 0;  
      }
    }
    if(i % 40 == 0){
      if(!status3){
        digitalWrite(blue, LOW);
        status3 = 1;
      }
      else if(status3){
        digitalWrite(blue, HIGH);
        status3 = 0;  
      }  
    }
    delay(50);
  }
}
