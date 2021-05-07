//#include <ESPAsyncTCP.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFi.h>
#include <fauxmoESP.h
>

#define ch1 14
#define ch2 27
#define ch3 33
#define ch4 32
const uint16_t ir = 12;
#define anodo 26
#define led 25

#define SERIAL_BAUDRATE 115200

#define WIFI_SSID "Villamarin"
#define WIFI_PASS "villamarin2709"

#define DEVICE_1 "device one"
#define DEVICE_2 "device two"
#define DEVICE_3 "device three"
#define DEVICE_4 "device four"
#define VolumeUp "Volume Up"
#define VolumeDown "Volume Down"
#define Filme "Hora do Filme"
#define Serie "Hora da Série"
#define OnOff "On/Off"

int flag = 0;

IRsend irsend(ir); 

fauxmoESP fauxmo;


// Wi-Fi Connection
void wifiSetup() {
  // Set WIFI module to STA mode
  WiFi.mode(WIFI_STA);

  // Connect
  Serial.printf("[WIFI] Connecting to %s ", WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Wait
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  // Connected!
  Serial.printf("[WIFI] STATION Mode, SSID: %s, IP address: %s\n", WiFi.SSID().c_str(), WiFi.localIP().toString().c_str());
}

void setup() {
  irsend.begin();
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();

  wifiSetup();

  dacWrite(anodo, 0);
  dacWrite(led, 255);
  
  // LED
  pinMode(ch1, OUTPUT);
  digitalWrite(ch1, HIGH);

  pinMode(ch2, OUTPUT);
  digitalWrite(ch2, HIGH);

  pinMode(ch3, OUTPUT);
  digitalWrite(ch3, HIGH);

  pinMode(ch4, OUTPUT);
  digitalWrite(ch4, HIGH);

  // By default, fauxmoESP creates it's own webserver on the defined port
  // The TCP port must be 80 for gen3 devices (default is 1901)
  // This has to be done before the call to enable()
  fauxmo.createServer(true); // not needed, this is the default value
  fauxmo.setPort(80); // This is required for gen3 devices

  // You have to call enable(true) once you have a WiFi connection
  // You can enable or disable the library at any moment
  // Disabling it will prevent the devices from being discovered and switched
  fauxmo.enable(true);
  // You can use different ways to invoke alexa to modify the devices state:
  // "Alexa, turn lamp two on"

  // Add virtual devices
  fauxmo.addDevice(DEVICE_1);
  fauxmo.addDevice(DEVICE_2);
  fauxmo.addDevice(DEVICE_3);
  fauxmo.addDevice(DEVICE_4);
  fauxmo.addDevice(VolumeUp);
  fauxmo.addDevice(VolumeDown);
  fauxmo.addDevice(Filme);
  fauxmo.addDevice(Serie);
  fauxmo.addDevice(OnOff);

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    // Callback when a command from Alexa is received.
    // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
    // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
    // Just remember not to delay too much here, this is a callback, exit as soon as possible.
    // If you have to do something more involved here set a flag and process it in your main loop.

    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if ( (strcmp(device_name, DEVICE_1) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 1 switched by Alexa");
      //digitalWrite(ch1, !digitalRead(ch1));
      if (state) {
        digitalWrite(ch1, HIGH);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      } else {
        digitalWrite(ch1, LOW);
        dacWrite(led, 0);
        delay(300);
        dacWrite(led, 255);
      }
    }
    if ( (strcmp(device_name, DEVICE_2) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 2 switched by Alexa");
      if (state) {
        digitalWrite(ch2, HIGH);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      } else {
        digitalWrite(ch2, LOW);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      }
    }
    if ( (strcmp(device_name, DEVICE_3) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 3 switched by Alexa");
      if (state) {
        digitalWrite(ch3, HIGH);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      } else {
        digitalWrite(ch3, LOW);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      }
    }
    if ( (strcmp(device_name, DEVICE_4) == 0) ) {
      Serial.println("RELAY 4 switched by Alexa");
      if (state) {
        digitalWrite(ch4, HIGH);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      } else {
        digitalWrite(ch4, LOW);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      }
    }
    if ( (strcmp(device_name, VolumeUp) == 0) ) {
      if (state) {
        Serial.println("VolumeUp switched by Alexa");
        irsend.sendNEC(551502015);
        irsend.sendNEC(551502015);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      }
    }    
    if ( (strcmp(device_name, VolumeDown) == 0) ) {
      if (state) {
        Serial.println("VolumeDown switched by Alexa");
        irsend.sendNEC(551534655);
        irsend.sendNEC(551534655);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      }
    }
    if ( (strcmp(device_name, Serie) == 0) ) {
      if (state) {
        flag = 1;
      }
    }
    if ( (strcmp(device_name, Filme) == 0) ) {
      // this just sets a variable that the main loop() does something about
      if (state) {
        Serial.println("Hora do Filme switched by Alexa");
        irsend.sendNEC(551501505);
        delay(2000);
        irsend.sendNEC(551494365);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      }
    }
    if ( (strcmp(device_name, OnOff) == 0) ) {
      // this just sets a variable that the main loop() does something about
      if (state) {
        Serial.println("TV On switched by Alexa");
        irsend.sendNEC(551489775);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      }
      else{
        Serial.println("TV Off switched by Alexa");
        irsend.sendNEC(551489775);
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
      }
    }   
  });

}

void loop() {
  // fauxmoESP uses an async TCP server but a sync UDP server
  // Therefore, we have to manually poll for UDP packets
  if(WiFi.status() != WL_CONNECTED){
    wifiSetup();
  }
  fauxmo.handle();

  if(flag){
      Serial.println("Hora da Série switched by Alexa");
        dacWrite(anodo, 255);
        delay(300);
        dacWrite(anodo, 0);
        irsend.sendNEC(551501505);
        delay(500);
        irsend.sendNEC(551510175);
        delay(500);
        irsend.sendNEC(551510175);
        delay(500);
        irsend.sendNEC(551494365);
        delay(7000);
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
        delay(2500);
        irsend.sendNEC(551494365);
        delay(2500);
        irsend.sendNEC(551518845);
        delay(300);
        irsend.sendNEC(551518845);
        delay(300);
        irsend.sendNEC(551494365);
        flag = 0;
  }
  
  static unsigned long last = millis();
  if (millis() - last > 5000) {
    last = millis();
    Serial.printf("[MAIN] Free heap: %d bytes\n", ESP.getFreeHeap());
  }

}
