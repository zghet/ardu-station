#include <ESP8266WiFi.h>

#include "fauxmoESP.h" 

//Se mandan a llamar los archivos de configuracio basica
#include "config.h"
#include "ESP8266-Util.hpp"

// Empezamos a declarar variables
#define RELAY_PIN_1 4
#define RELAY_PIN_2 14
#define LAMPARA1 "lampara uno"
#define LAMPARA2 "lampara dos"

void setup() 
{
  Serial.begin(115200);
  ConnectWiFi_STA();

  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, HIGH);

  pinMode(RELAY_PIN_2, OUTPUT);
  digitalWrite(RELAY_PIN_2, HIGH);
}

void loop() 
{
  
}
