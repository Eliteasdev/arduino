#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

//Configuracion wifi servidor
const char *ssid = "";
const char *password = "";
String servidor = "";
WiFiClient client;

//Definicion de pines
int potPin = A0;
int btnPin = 5;
int led1 = 12;
int led2 =13;

void setup()
{

  pinMode(potPin, INPUT);
  pinMode(btnPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  Serial.begin(9600);

  Serial.println("Conectando  a: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
	  delay(500);
	  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado!");

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
}

void loop() {
    int distance = analogRead(potPin);
    int btn = digitalRead(btnPin);

  
    HTTPClient http;
    Serial.print("Numero actual: ");
    Serial.println(distance);
    
    String sEnviado = "{ \"value1\": " + String(distance) + ", \"value2\":" + String(btn) +" }";
    Serial.println("Enviar a servidar: ");
    Serial.println("<- "+sEnviado);

    http.begin(client,servidor);
    http.addHeader("Content-Type", "application/json");

    int iCodigoRespuesta = http.POST(sEnviado);
    if(iCodigoRespuesta>0)
    {
      
      Serial.println("Codigo de respuesta: " + String(iCodigoRespuesta));
      if(iCodigoRespuesta == 200)
      {
        String sRecibido = http.getString();
        Serial.println("Respuesta Servidor: ");
        Serial.println("-> " +sRecibido);
        DynamicJsonDocument doc(1024);
        deserializeJson(doc, sRecibido);

        // Obtener los valores del JSON
        bool valor1 = doc["response1"];
        bool valor2 = doc["response2"];

        Serial.println("Valor1: " + String(valor1));
        Serial.println("Valor2: " + String(valor2));

        if(String(valor1) == "1"){
          digitalWrite(led1, HIGH);
          
        }else{
          digitalWrite(led1, LOW);
          
        }

        if(String(valor2) == "1"){
          digitalWrite(led2, HIGH);
        }else{
          digitalWrite(led2, LOW);
        }

      }
    }
    else
    {
      Serial.print("error en envio de post: ");
      Serial.println(iCodigoRespuesta);
    }
    http.end();
    Serial.println("Espera...");
    delay(5000);
  
}
