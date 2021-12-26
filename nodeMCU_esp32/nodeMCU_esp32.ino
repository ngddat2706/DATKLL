#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "WiFi.h"

#define RXD2 16
#define TXD2 17

#define WLAN_SSID "iPhone"        // name wifi
#define WLAN_PASS "cochacyeuladay"    // password wifi

#define IO_SERVER    "io.adafruit.com"
#define IO_SERVERPORT 1883

#define IO_USERNAME  "NDDIoT"
#define IO_KEY       "aio_aGzS02OLLT4MqLhDWWaO6Ly4ZmfT"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, IO_SERVER, IO_SERVERPORT, IO_USERNAME, IO_KEY);
Adafruit_MQTT_Publish SERIAL_PUBLISH = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/doantkll");

void MQTT_connect();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.print(F("Connecting to "));
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("WiFi connected!");
  MQTT_connect();
  Serial.println("MQTT connected!");  
}

void loop() {
  // put your main code here, to run repeatedly:
  MQTT_connect();
  if (Serial2.available() > 0) {
     char bfr[501];
     memset(bfr,0, 501);
     Serial2.readBytesUntil( '\n',bfr,500);
     Serial.println(bfr);
     MQTT_connect();
     SERIAL_PUBLISH.publish(bfr);
   }
}

void MQTT_connect() {
  
  while(!mqtt.connected()){
    Serial.print("Attempting MQTT connection...");
    if(mqtt.connect()){
      Serial.println("connected!");  
    }else{
      Serial.println("try again in 5 seconds!");
      delay(5000);  
    }
  }
}
