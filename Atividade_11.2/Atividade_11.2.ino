#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define TOPICO_PUBLISH   "v1/devices/me/attributes"
#define ID_MQTT  "Client ESP"
#define TOKEN "A1_TEST_TOKEN"

const int led = 5;

const char* SSID = "Villamarin";
const char* PASSWORD = "villamarin2709";

const char* IP = "192.168.0.50";
int PORT = 1883;

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
  pinMode(led, OUTPUT);
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
  MQTT.setCallback(mqtt_callback);  
}
void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String topico = topic;
    char json[40];
    for(int i = 0; i < length; i++){
       char c = (char)payload[i];
       json[i] = c;
    }
    DynamicJsonDocument doc(40);
    deserializeJson(doc, json);
    const char* metodo = doc["method"];
    boolean parametro = doc["params"];
    Serial.print("[MQTT] Mensagem recebida ");
    if(parametro){
      digitalWrite(led, LOW);
      Serial.println("Acende led");
    }
    else if(!parametro){
      digitalWrite(led, HIGH);
      Serial.println("Apaga led");
    }
}
void reconnect_mqtt(void) {
  while (!MQTT.connected()) {
    Serial.print("* Tentando se conectar ao Broker MQTT: ");
    Serial.println(ID_MQTT);
    if (MQTT.connect(ID_MQTT, TOKEN, " "))
    {
      Serial.println("Conectado com sucesso ao broker MQTT!");
      MQTT.subscribe("v1/devices/me/rpc/request/+");
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
  MQTT.loop();
  delay(1000);
}
