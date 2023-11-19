// http://arduino.esp8266.com/stable/package_esp8266com_index.json

#include <ESP8266WiFi.h>
#include "NewPing.h"

String apiKey = "";
const char *ssid = "PC_PUMA";
const char *password = "";
const char *servidor = "api.thingspeak.com";
WiFiClient client;

int TRIGGER = 16;
int ECHO = 5;
int LED = 4;

NewPing sonar(TRIGGER, ECHO);

void setup() {
  // put your setup code here, to run once:
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(LED, OUTPUT);

  Serial.begin(9600);
  Serial.println("Conectando a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!");
  digitalWrite(LED, LOW);
}

void loop() {
  float distancia = sonar.ping_median(5);
  distancia = distancia/88.2;
  if(distancia>=5){
    digitalWrite(LED, LOW);
  }else{
    digitalWrite(LED, HIGH);
  }

  if(client.connect(servidor,80)){
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(distancia);
    postStr += "\r\n\r\n";
    client.print("POST /update HTTP/1.1\n");
    client.print("HOST: api.thingspeak.com\n");
    client.print("Connetion: close\n");
    client.print("X-THINGSPEAKAPIKEY:" + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
    Serial.print("Distancia: ");
    Serial.print(distancia);
    Serial.print(" ");
    Serial.println("%. Enviado a THingspeak.");
  }
  client.stop();
  Serial.println("Espera...");
  delay(5000);
}
