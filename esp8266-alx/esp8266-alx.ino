

#include <ESP8266WiFi.h>

//Se mandan a llamar los archivos de wifi
#include "config.h"
#include "ESP8266-Util.hpp"


// Se definen los dipositivos
#define RELAY_PIN_1 1
#define RELAY_PIN_2 2
#define RELAY_PIN_3 3
#define RELAY_PIN_4 4
#define RELAY_PIN_5 5
#define RELAY_PIN_6 6

#include "fauxmoESP.h" 
#define SERIAL_BAUDRATE 115200 

#define LAMPARA1 "luz cuarto"
#define LAMPARA2 "luz visita"
#define LIGHT3 "luz baño"
#define LIGHT4 "luz sala"

fauxmoESP fauxmo;

void setup() 
{
  
  Serial.begin(SERIAL_BAUDRATE);
  Serial.println();
  
  ConnectWiFi_STA();

  //Define relays
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, HIGH);

  pinMode(RELAY_PIN_2, OUTPUT);
  digitalWrite(RELAY_PIN_2, HIGH);

  pinMode(RELAY_PIN_3, OUTPUT);
  digitalWrite(RELAY_PIN_3, HIGH);

  pinMode(RELAY_PIN_4, OUTPUT);
  digitalWrite(RELAY_PIN_4, HIGH);


  // Add virtual devices
  fauxmo.addDevice(LAMPARA1);
  fauxmo.addDevice(LAMPARA2);
  fauxmo.addDevice(LIGHT3);
  fauxmo.addDevice(LIGHT4);

  
  fauxmo.createServer(true); // not needed, this is the default value
  fauxmo.setPort(80); // This is required for gen3 devices
fauxmo.enable(true);

}

void loop() 
{
  // fauxmoESP uses an async TCP server but a sync UDP server
  // Therefore, we have to manually poll for UDP packets
  fauxmo.handle();

}
