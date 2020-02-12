

#include <ESP8266WiFi.h>
#include "fauxmoESP.h" 

//Se mandan a llamar los archivos de wifi
#include "config.h"
#include "ESP8266-Util.hpp"


// Se definen los pines
#define RELAY_PIN_1 D5
#define RELAY_PIN_2 D7


#define serial_rate 115200 

#define LAMPARA1 "luz comedor"
#define LAMPARA2 "luz comida"
#define LAMPARAS "luces"

fauxmoESP fauxmo;

void setup() {
  // Init serial port and clean garbage
  Serial.begin(serial_rate);
  Serial.println();

  // Wi-Fi connection
  wifiSetup();

  // LED
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, HIGH);
  //delay(500);
  pinMode(RELAY_PIN_2, OUTPUT);
  digitalWrite(RELAY_PIN_2,HIGH);
  //delay(500);

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
  fauxmo.addDevice(LAMPARA1);
  fauxmo.addDevice(LAMPARA2);
  fauxmo.addDevice(LAMPARAS);
    fauxmo.onSetState
  (
    [](unsigned char device_id, const char * device_name, bool state, unsigned char value) 
  {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

  if ( (strcmp(device_name, "luz comedor") == 0) )
  {
  if (!state)
  {
  digitalWrite(RELAY_PIN_1, HIGH);
  }
  else
  {
  digitalWrite(RELAY_PIN_1, LOW);
  }
  }

    if ( (strcmp(device_name, "luz comida") == 0) )
  {
  if (!state)
  {
  digitalWrite(RELAY_PIN_2, HIGH);
  }
  else
  {
  digitalWrite(RELAY_PIN_2, LOW);
  }
  }

    if ( (strcmp(device_name, "luces") == 0) ) 
  {
    if (!state) 
    {
      digitalWrite(RELAY_PIN_1, HIGH);
      digitalWrite(RELAY_PIN_2, HIGH);
      //digitalWrite(RELAY_3, HIGH);
      //digitalWrite(RELAY_4, HIGH);
    } 
    else 
    {
      digitalWrite(RELAY_PIN_1, LOW);
      digitalWrite(RELAY_PIN_2, LOW);
      //digitalWrite(RELAY_3, LOW);
      //digitalWrite(RELAY_4, LOW);
    }
  }
  });

}

void loop() 
{
  // fauxmoESP uses an async TCP server but a sync UDP server
  // Therefore, we have to manually poll for UDP packets
  fauxmo.handle();

}
