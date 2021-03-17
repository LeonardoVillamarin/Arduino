#include "DHT.h"
#include "BluetoothSerial.h"

#define DHTPIN 4    
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);
BluetoothSerial SerialBT;


void setup() {
  Serial.begin(9600);
  SerialBT.begin("Esp32");
  dht.begin();
}

void loop() {
  delay(1000);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    SerialBT.println(F("Failed to read from DHT sensor!"));
    return;
  }
  
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidade: "));
  SerialBT.print(F("Humidade: "));
  Serial.print(h);
  SerialBT.print(h);
  Serial.print(F("%  Temperatura: "));
  SerialBT.print(F("% Temperatura: "));
  Serial.print(t);
  SerialBT.print(t);
  Serial.println(F("°C "));
  SerialBT.println(F("ºC"));
}
