#include "DHT.h"    
#include <SoftwareSerial.h>

SoftwareSerial sw(2,3);
int id = 99;
const int DHTPIN = 4;      
const int DHTTYPE = DHT11;  
int light = A5;

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600);
  dht.begin();
  sw.begin(9600);       
}

void loop() {
  float h = dht.readHumidity();    
  float t = dht.readTemperature(); 
  float l = analogRead(light);
 
  
 sw.print("{");
 sw.print("\"place\": \"Nghi Loc, Nghe An\", ");
 sw.print("\"node_id\": 1, ");
 sw.print("\"temperature\": ");
 sw.print(t);
 sw.print(", ");
 sw.print("\"humidity\": ");
 sw.print(h);
 sw.print(", ");
 sw.print("\"light\": ");
 sw.print(l);
 sw.print("}");
 sw.println();
 
  delay(110000);                     
}
