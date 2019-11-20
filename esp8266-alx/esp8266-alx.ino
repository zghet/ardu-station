#include <ESP8266WiFi.h>



void setup() 
{
  Serial.begin(115200);
  delay(10);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Conectando a: \t");
  Serial.println(ssid);

  //tiempo de espera en lo que conecta
  while (WiFi.status()!=WL_CONNECTED)
  {
    delay(200);
    Serial.print('.');
  }

  // Mostramos mensaje de exito y dirección IP asignada
  Serial.println();
  Serial.print("Conectado a:\t");
  Serial.println(WiFi.SSID()); 
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  
}
