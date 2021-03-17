//Bibliotecas utilizadas
#include <WiFi.h>
#include <Arduino.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
 
//Definição dos pinos

const uint16_t kIrLed = 14;

IRsend irsend(kIrLed);  
 
#define WLAN_SSID       "Villamarin"      // Nome da Rede Wifi
#define WLAN_PASS       "villamarin2709"     // Senha da Rede Wifi
 
/************************* Adafruit.io Configuração *********************************/
 
#define AIO_SERVER      "io.adafruit.com" //Adafruit Servidor
#define AIO_SERVERPORT  1883                  
#define AIO_USERNAME    "villamarin"      //Insira o usuario criado na adafruit io
#define AIO_KEY         "aio_uggo312KWOYspCWbpSvOSzOtMZ41" //Insira a chave de comunicação obtida na adafruit io
 
//Váriáveis utilizadas
 
int conectado = 1;
int conexao = 0;
int alarme = 0;
int trava = 0;
 
unsigned long anterior = 0;
unsigned long intervalo = 15000;
unsigned long atual;
 
//Definição do Wifi Client
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
 
//Váriáveis criadas para comunicação com o MQTT   // Crie aqui sua variavel
Adafruit_MQTT_Subscribe volumeUp = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/volume up");        // a palavra feeds deve estar em todos
Adafruit_MQTT_Subscribe volumeDown = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/volume down");    
Adafruit_MQTT_Subscribe cima = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/cima");
Adafruit_MQTT_Subscribe baixo = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/baixo");
Adafruit_MQTT_Subscribe esquerda = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/esquerda");
Adafruit_MQTT_Subscribe direita = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/direita");
Adafruit_MQTT_Subscribe desliga = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/desligar");
Adafruit_MQTT_Subscribe liga = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/liga");
Adafruit_MQTT_Subscribe input = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/input");
Adafruit_MQTT_Subscribe back = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/back");
Adafruit_MQTT_Subscribe enter = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/enter");
Adafruit_MQTT_Subscribe home_ = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/home");
 
//Funções
void MQTT_connect(); //Determina a conexão MQTT
void Conectar();     //Verifica a conexão o Wifi
 
void setup() {
  irsend.begin();
  Serial.begin(115200);
  
   
  //Declaração de Tópicos de Leitura
  mqtt.subscribe(&volumeUp);
  mqtt.subscribe(&volumeDown);
  mqtt.subscribe(&cima);
  mqtt.subscribe(&baixo);
  mqtt.subscribe(&esquerda);
  mqtt.subscribe(&direita);
  mqtt.subscribe(&desliga);
  mqtt.subscribe(&liga);
  mqtt.subscribe(&input);
  mqtt.subscribe(&back);
  mqtt.subscribe(&enter);
  mqtt.subscribe(&home_);
  
}
 
void loop() {
 
  Conectar();
  MQTT_connect();
 
  //Leitura do valor recebido através da Adafruit IO
  Adafruit_MQTT_Subscribe *subscription;
  if((subscription = mqtt.readSubscription(100))) {
    if (subscription == &volumeUp) {
      Serial.println("Volume Up");
      Serial.println((char *)volumeUp.lastread);
      irsend.sendNEC(551502015);
      irsend.sendNEC(551502015);
    }
    if (subscription == &volumeDown) {
      Serial.println("Volume Down");
      irsend.sendNEC(551534655);
      irsend.sendNEC(551534655);
    }
    if (subscription == &cima){ 
      Serial.println("Cima");
      irsend.sendNEC(551486205);
    }
    if (subscription == &baixo){ 
      Serial.println("Baixo");
      irsend.sendNEC(551518845);
    }
    if (subscription == &esquerda){ 
      Serial.println("Esquerda");
      irsend.sendNEC(551542815);
    }    
    if (subscription == &direita){ 
      Serial.println("Direita");
      irsend.sendNEC(551510175);
    }
    if (subscription == &desliga){ 
      int desligaState = atoi((char *)desliga.lastread);
      Serial.println(desligaState);
      if(desligaState == 0){
          Serial.println("Desliga");
          irsend.sendNEC(551489775);
      }
    }
    if (subscription == &liga){ 
      int ligaState = atoi((char *)liga.lastread);
      Serial.println(ligaState);
      if(ligaState == 0){
          Serial.println("Liga");
          irsend.sendNEC(551489775);
      }
    }
    if (subscription == &input){ 
      Serial.println("Input");
      irsend.sendNEC(551546895);
    }
    if (subscription == &back){ 
      Serial.println("Back");
      //irsend.sendNEC(551490795);
      irsend.sendNEC(551501505);
      delay(500);
      irsend.sendNEC(551510175);
      delay(500);
      irsend.sendNEC(551510175);
      delay(500);
      irsend.sendNEC(551494365);
      delay(5000);
      irsend.sendNEC(551494365);
      delay(5000);
      irsend.sendNEC(551510175);
      delay(300);
      irsend.sendNEC(551510175);
      delay(300);
      irsend.sendNEC(551510175);
      delay(300);
      irsend.sendNEC(551494365);
      delay(2000);
      irsend.sendNEC(551510175);
      delay(300);
      irsend.sendNEC(551510175);
      delay(300);
      irsend.sendNEC(551510175);
      delay(300);
      irsend.sendNEC(551494365);
      delay(2000);
      irsend.sendNEC(551494365);
      delay(2000);
      irsend.sendNEC(551518845);
      delay(300);
      irsend.sendNEC(551518845);
      delay(300);
      irsend.sendNEC(551510175);
      delay(300);
      irsend.sendNEC(551494365);
    }
    if (subscription == &enter){ 
      Serial.println("Enter");
      irsend.sendNEC(551494365);
    }
    if (subscription == &home_){ 
      Serial.println("Netflix");
      irsend.sendNEC(551501505);
      delay(2000);
      irsend.sendNEC(551494365);
    }
  }
}
 
void MQTT_connect() {
  int8_t ret;
  //Conectando MQTT
  if (mqtt.connected()) {
    if(conectado){
      conectado = 0;
      Serial.println("MQTT Conectado!");
    }
    return;
  }
  Serial.print("Conectando MQTT...");
  uint8_t retries = 3;
  if((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Reconexao ao MQTT em 5 segundos...");
    mqtt.disconnect();
    delay(5000);
    conectado = 1;
    //retries--;
    if (retries == 0) {
      //retries = 3;
    }
  }
}
 
void Conectar(){
  //Verifica a conexão wifi
  if(WiFi.status() != WL_CONNECTED){
      conexao = 0; 
      //Conectando ao Wifi
      Serial.println();
      Serial.println();
      Serial.print("Conectando a rede: ");
      Serial.println(WLAN_SSID);
      //Inicializa Conexão Wifi
      WiFi.begin(WLAN_SSID, WLAN_PASS);
      while(WiFi.status() != WL_CONNECTED) {
            delay(500);
            Serial.print(".");
            conexao++;
            if(conexao == 50){
              ESP.restart();
            }
      }
      Serial.println("WiFi conectado!");
      Serial.println("Endereco de IP: ");
      Serial.println(WiFi.localIP());
      conectado = 1;
      Serial.println();
  }
}
