#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 5
#define DHTTYPE DHT11

#define TOPICO_PUBLISH   "DHT11_DEMO_TOKEN"
#define ID_MQTT  "Client ESP"
#define TOKEN "DHT11_DEMO_TOKEN"

const char* SSID = "Villamarin";
const char* PASSWORD = "villamarin2709";

const char* IP = "192.168.0.50";
int PORT = 1883;

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient MQTT(espClient);

void init_serial(void);
void init_wifi(void);
void init_mqtt(void);
void reconnect_wifi(void);
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void verifica_conexoes_wifi_mqtt(void);

void setup() {
  init_serial();
  init_wifi();
  init_mqtt();
  dht.begin();
}

void init_serial() {
  Serial.begin(115200);
}

void init_wifi(void) {
  delay(10);
  Serial.println("------Conexao WI-FI------");
  Serial.print("Conectando-se na rede: ");
  Serial.println(SSID);
  Serial.println("Aguarde");
  reconnect_wifi();
}

void init_mqtt(void) {
  MQTT.setServer(IP, PORT);
}

void reconnect_mqtt(void) {
  while (!MQTT.connected()) {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(ID_MQTT);
    if (MQTT.connect(ID_MQTT, TOKEN, " "))
    {
      Serial.println("Conectado com sucesso ao broker MQTT!");
    }
    else
    {
      Serial.println("Falha ao reconectar no broker.");
      Serial.println("Havera nova tentatica de conexao em 2s");
      delay(2000);
    }
  }
}

void reconnect_wifi() {
  if (WiFi.status() == WL_CONNECTED)
    return;
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Conectado com sucesso na rede ");
  Serial.print(SSID);
  Serial.println("IP obtido: ");
  Serial.println(WiFi.localIP());
}

void verifica_conexoes_wifi_mqtt(void) {
  reconnect_wifi();
  if (!MQTT.connected())
    reconnect_mqtt();
}

void loop() {
  verifica_conexoes_wifi_mqtt();
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hic = dht.computeHeatIndex(t, h, false);

  String msg = "{\"humidade\":" + String(h) + ",\"temperaturaCelcius\":" + String(t) + ",\"temperaturaFahrenheit\":" + String(f) + "}";
  char mensagem[msg.length() + 1];
  strcpy(mensagem, msg.c_str());
  Serial.println(mensagem);
  MQTT.publish(TOPICO_PUBLISH, mensagem);
  MQTT.loop();
  delay(1000);
}
