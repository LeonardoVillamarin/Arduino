#include <WiFi.h>
#include <PubSubClient.h>
  
#define TOPICO_PUBLISH   "ESP32_envia_informacao"  
#define ID_MQTT  "Cliente_MQTT"     

const char* SSID = "Villamarin"; 
const char* PASSWORD = "villamarin2709"; 
  
const char* BROKER_MQTT = "192.168.0.50"; 
int BROKER_PORT = 1883;
 
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
    MQTT.setServer(BROKER_MQTT, BROKER_PORT); 
    MQTT.setCallback(mqtt_callback);            
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
    Serial.print("[MQTT] Mensagem recebida: ");
    Serial.println(msg);     
}
  
void reconnect_mqtt(void) {
    while (!MQTT.connected()) {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
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

void verifica_conexoes_wifi_mqtt(void){
    reconnect_wifi(); 
    if (!MQTT.connected()) 
        reconnect_mqtt(); 
} 
 
void loop() {   
    verifica_conexoes_wifi_mqtt();
    MQTT.publish(TOPICO_PUBLISH, "ESP32 se comunicando com MQTT");
    MQTT.loop();
    delay(1000);   
}
