// se incluyen librerias
#include <ESP8266WiFi.h>

//Se mandan a llamar los archivos de wifi
#include "config.h"
#include "ESP8266-Util.hpp"


// Se definen los dipositivos
#define relay_1 3
#define relay_2 4


#include "fauxmoESP.h" 
#define SERIAL_BAUDRATE 115200

#define lamp1 "luz julio"
#define lamp2 "luz visita"


fauxmoESP fauxmo;

void setup() 
{
  
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
  
  wifiSetup();

  //Define relays
  pinMode(relay_1, OUTPUT);
  digitalWrite(relay_1, HIGH);

  pinMode(relay_2, OUTPUT);
  digitalWrite(relay_2, HIGH);

  // Add virtual devices
  fauxmo.addDevice(lamp1);
  fauxmo.addDevice(lamp2);
  
  // By default, fauxmoESP creates it's own webserver on the defined port
  fauxmo.createServer(true); // not needed, this is the default value
  fauxmo.setPort(80); // This is required for gen3 devices
  
  // You have to call enable(true) once you have a WiFi connection
  fauxmo.enable(true);

}

void loop()
{
  // fauxmoESP uses an async TCP server but a sync UDP server
  // Therefore, we have to manually poll for UDP packets
  fauxmo.handle();

}
