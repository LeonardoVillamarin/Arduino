#include <WiFi.h>
#include <PubSubClient.h>
 
#define TOPICO_RED_LED "RedLed"
#define TOPICO_GREEN_LED "GreenLed"
#define TOPICO_BLUE_LED "BlueLed"
#define TOPICO_LEDS "Leds"     
#define ID_MQTT  "Cliente_MQTT"

const int redLed = 27;
const int greenLed = 14;
const int blueLed = 12;

bool redStatus = 0;
bool greenStatus = 0;
bool blueStatus = 0;

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
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    pinMode(blueLed, OUTPUT);
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
    String topico = topic;
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
    Serial.print("[MQTT] Mensagem recebida: ");
    
    if(topico.equals(TOPICO_LEDS)){
      if(msg.equals("Acender")){
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, LOW);
        digitalWrite(blueLed, LOW);
        Serial.println(msg + " todos os leds.");
      }
      else if(msg.equals("Apagar")){
        digitalWrite(redLed, HIGH);
        digitalWrite(greenLed, HIGH);
        digitalWrite(blueLed, HIGH);
        Serial.println(msg + " todos os leds.");
      }
      else if(msg.equals("Piscar")){
          redStatus = true;
          greenStatus = true;
          blueStatus = true;
          xTaskCreate(RedLed, "RedLed", 10000, NULL, 1, NULL);
          xTaskCreate(GreenLed, "GreenLed", 10000, NULL, 1, NULL);
          xTaskCreate(BlueLed, "BlueLed", 10000, NULL, 1, NULL);
          Serial.println(msg + " todos os leds.");
      }
      else if(msg.equals("Parar de piscar")){
          redStatus = false;
          greenStatus = false;
          blueStatus = false;
          Serial.println(msg + " todos os leds.");
      }
    }
    else if(topico.equals(TOPICO_RED_LED)){
        Serial.println(msg + " o led vermelho.");
        if(msg.equals("Acender")){
            digitalWrite(redLed, LOW);
        }
        else if(msg.equals("Apagar")){
            digitalWrite(redLed, HIGH);
            Serial.println(msg + " o led vermelho.");
        }
        else if(msg.equals("Piscar")){
            redStatus = true;
            xTaskCreate(RedLed, "RedLed", 10000, NULL, 1, NULL);
        }
        else if(msg.equals("Parar de Piscar")){
            redStatus = false;
        }
    }
    else if(topico.equals(TOPICO_GREEN_LED)){
        Serial.println(msg + " o led verde.");
        if(msg.equals("Acender")){
            digitalWrite(greenLed, LOW);
        }
        else if(msg.equals("Apagar")){
            digitalWrite(greenLed, HIGH);
        }
        else if(msg.equals("Piscar")){
            greenStatus = true;
            xTaskCreate(GreenLed, "GreenLed", 10000, NULL, 1, NULL);
        }
        else if(msg.equals("Parar de piscar")){
            greenStatus = false;
        }
      
    }       
    else if(topico.equals(TOPICO_BLUE_LED)){
        Serial.println(msg + " o led azul.");
        if(msg.equals("Acender")){
            digitalWrite(blueLed, LOW);
        }
        else if(msg.equals("Apagar")){
            digitalWrite(blueLed, HIGH);
        }
        else if(msg.equals("Piscar")){
            blueStatus = true;
            xTaskCreate(BlueLed, "BlueLed", 10000, NULL, 1, NULL);
        }
        else if(msg.equals("Parar de piscar")){
            blueStatus = false;
            xTaskCreate(BlueLed, "BlueLed", 10000, NULL, 1, NULL);
        }
    }
}
  
void reconnect_mqtt(void) {
    while (!MQTT.connected()) {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_RED_LED);
            MQTT.subscribe(TOPICO_BLUE_LED);
            MQTT.subscribe(TOPICO_GREEN_LED);
            MQTT.subscribe(TOPICO_LEDS); 
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
    MQTT.loop();
    delay(1000);   
}
void RedLed(void *) {
  while(redStatus) {
    digitalWrite(redLed, LOW);
    delay(500);
    digitalWrite(redLed, HIGH);
    delay(500);
  }
  vTaskDelete(NULL);
}
void GreenLed(void *) {
  while(greenStatus) {
    digitalWrite(greenLed, LOW);
    delay(1000);
    digitalWrite(greenLed, HIGH);
    delay(1000);
  }
  vTaskDelete(NULL);
}
void BlueLed(void *) {
  while(blueStatus){
    digitalWrite(blueLed, LOW);
    delay(2000);
    digitalWrite(blueLed, HIGH);
    delay(2000);
  }
  vTaskDelete(NULL);
}
  
