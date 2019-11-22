#include <ESP8266WiFi.h>

#include "fauxmoESP.h" 

//Se mandan a llamar los archivos de configuracio basica
#include "config.h"
#include "ESP8266-Util.hpp"

void setup() 
{
  Serial.begin(115200);
  ConnectWiFi_STA();
}

void loop() 
{
  
}
