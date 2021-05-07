#include <WiFi.h>
#include <HTTPClient.h>
#include <fauxmoESP.h>
#include <EEPROM.h>

#define EEPROM_SIZE 3

#define WIFI_SSID "Villamarin"
#define WIFI_PASS "villamarin2709"

#define RELE_2 "Rele dois"
#define RELE_3 "Rele tres"
#define RELE_4 "Rele quatro"

const int sensor1 = 5;
const int sensor2 = 18;
const int sensor3 = 19;
const int sensor4 = 21;
const int rele1 = 26;         //1: 26     2: 25     3: 32      4: 33
const int rele2 = 25;
const int rele3 = 33;
const int rele4 = 32;
const int boia = 35;

int releState1 = HIGH;
int releState2 = HIGH;
int releState3 = HIGH;

fauxmoESP fauxmo;

void wifiSetup() {
  WiFi.mode(WIFI_STA);
  Serial.printf("[WIFI] Conectando a %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.printf("[WIFI] SSID: %s, IP: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  releState1 = EEPROM.read(0);
  digitalWrite(rele2, releState1);
  releState2 = EEPROM.read(1);
  digitalWrite(rele3, releState2);
  releState3 = EEPROM.read(2);
  digitalWrite(rele4, releState3);
  wifiSetup();
  xTaskCreate(makeIFTTT, "makeIFTTT", 10000, NULL, 1, NULL);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT); 
  pinMode(rele3, OUTPUT);
  pinMode(rele4, OUTPUT); 
  pinMode(boia, INPUT);
  fauxmo.createServer(true);
  fauxmo.setPort(80);
  fauxmo.enable(true);
  fauxmo.addDevice(RELE_2);
  fauxmo.addDevice(RELE_3);
  fauxmo.addDevice(RELE_4);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if ( (strcmp(device_name, RELE_2) == 0) ) {
      Serial.println("RELAY 2 switched by Alexa");
      if (state) {
        digitalWrite(rele2, HIGH);
        EEPROM.write(0, HIGH);
        EEPROM.commit();
      } else {
        digitalWrite(rele2, LOW);
        EEPROM.write(0, LOW);
        EEPROM.commit();
      }
    }
    if ( (strcmp(device_name, RELE_3) == 0) ) {
      Serial.println("RELAY 3 switched by Alexa");
      if (state) {
        digitalWrite(rele3, HIGH);
        EEPROM.write(1, HIGH);
        EEPROM.commit();
      } else {
        digitalWrite(rele3, LOW);
        EEPROM.write(1, LOW);
        EEPROM.commit();
      }
    }
    if ( (strcmp(device_name, RELE_4) == 0) ) {
      Serial.println("RELAY 4 switched by Alexa");
      if (state) {
        digitalWrite(rele4, HIGH);
        EEPROM.write(2, HIGH);
        EEPROM.commit();
      } else {
        digitalWrite(rele4, LOW);
        EEPROM.write(2, LOW);
        EEPROM.commit();
      }
    }  
  });
}

void loop() {
  fauxmo.handle();
  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
    Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  }
  int readSensor[4];
  readSensor[0] = digitalRead(sensor1);
  readSensor[1] = digitalRead(sensor2);
  readSensor[2] = digitalRead(sensor3);
  readSensor[3] = digitalRead(sensor4);
  if(readSensor[0] == 1 || readSensor[1] == 1 || readSensor[2] == 1 || readSensor[3] == 1) {
    digitalWrite(rele1, HIGH);
  }
  if(readSensor[0] == 0 && readSensor[1] == 0 && readSensor[2] == 0 && readSensor[3] == 0) {
    digitalWrite(rele1, LOW);
  }
}
void makeIFTTT(void *){
  bool status = true; 
  while(true){
    int valorBoia = digitalRead(boia);
    if(!valorBoia && !status){
      HTTPClient http;
      http.begin("https://maker.ifttt.com/trigger/nivelAgua/with/key/cVJOZ7R2OQ-6zJErfKSr7k");
      http.GET();
      http.end();
      status = true;
    }
    if(valorBoia && status){
      status = false;
    }
    delay(5000);
  }
  vTaskDelete(NULL); 
}
