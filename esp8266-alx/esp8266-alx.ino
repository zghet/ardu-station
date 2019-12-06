#include <ESP8266WiFi.h>
#include "fauxmoESP.h" 

//Se mandan a llamar los archivos de wifi
#include "config.h"
#include "ESP8266-Util.hpp"


// Se definen los pines
#define relay_one D0
#define relay_two D1
#define relay_thr D2
#define relay_for D3
#define relay_fiv D4
#define relay_six D5
#define relay_sev D6
#define relay_eig D7
#define relay_nin D8

#define serial_rate 115200 

#define light1 "luz 1"
#define light2 "luz 2"
#define light3 "luz 3"
#define light4 "luz 4"
#define light5 "luz 5"
#define light6 "luz 6"
#define light7 "luz 7"
#define light8 "luz 8"
#define light9 "luz 9"

fauxmoESP fauxmo;

void setup() {
  // Init serial port 
  Serial.begin(serial_rate);
  Serial.println();

  // Wi-Fi connection
  wifiSetup();

  // LED define
  pinMode(relay_one, OUTPUT);
  digitalWrite(relay_one, HIGH);

  pinMode(relay_two, OUTPUT);
  digitalWrite(relay_two,HIGH);

  pinMode(relay_thr, OUTPUT);
  digitalWrite(relay_thr, HIGH);

  pinMode(relay_for, OUTPUT);
  digitalWrite(relay_for,HIGH);

  pinMode(relay_fiv, OUTPUT);
  digitalWrite(relay_fiv, HIGH);

  pinMode(relay_six, OUTPUT);
  digitalWrite(relay_six,HIGH);

  pinMode(relay_sev, OUTPUT);
  digitalWrite(relay_sev, HIGH);

  pinMode(relay_eig, OUTPUT);
  digitalWrite(relay_eig,HIGH);

  pinMode(relay_nin, OUTPUT);
  digitalWrite(relay_nin,HIGH);


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
  fauxmo.addDevice(light1);
  fauxmo.addDevice(light2);
  fauxmo.addDevice(light3);
  fauxmo.addDevice(light4);
  fauxmo.addDevice(light5);
  fauxmo.addDevice(light6);
  fauxmo.addDevice(light7);
  fauxmo.addDevice(light8);
  fauxmo.addDevice(light9);
  fauxmo.addDevice(light10);
  fauxmo.onSetState
  (
    [](unsigned char device_id, const char * device_name, bool state, unsigned char value) 
  {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);

    if ( (strcmp(device_name, "light1") == 0) )
    {
      if (!state)
      {
        digitalWrite(relay_one, HIGH);
      }
      else
      {
        digitalWrite(relay_one, LOW);
      }
    }

    if ( (strcmp(device_name, "light2") == 0) )
    {
      if (!state)
      {
        digitalWrite(relay_two, HIGH);
      }
      else
      {
        digitalWrite(relay_two, LOW);
      }
    }

    if ( (strcmp(device_name, "light3") == 0) )
    {
      if (!state)
      {
        digitalWrite(relay_thr, HIGH);
      }
      else
      {
        digitalWrite(relay_thr, LOW);
      }
    }

    if ( (strcmp(device_name, "light4") == 0) )
    {
      if (!state)
      {
        digitalWrite(relay_for, HIGH);
      }
      else
      {
        digitalWrite(relay_for, LOW);
      }
    }

    if ( (strcmp(device_name, "light5") == 0) )
    {
      if (!state)
      {
        digitalWrite(relay_fiv, HIGH);
      }
      else
      {
        digitalWrite(relay_fiv, LOW);
      }
    }

    if ( (strcmp(device_name, "light6") == 0) )
    {
      if (!state)
      {
        digitalWrite(relay_six, HIGH);
      }
      else
      {
        digitalWrite(relay_six, LOW);
      }
    }

    if ( (strcmp(device_name, "light7") == 0) )
    {
      if (!state)
      {
        digitalWrite(relay_sev, HIGH);
      }
      else
      {
        digitalWrite(relay_sev, LOW);
      }
    }

    if ( (strcmp(device_name, "light8") == 0) )
    {
      if (!state)
      {
        digitalWrite(relay_eig, HIGH);
      }
      else
      {
        digitalWrite(relay_eig, LOW);
      }
    }

    if ( (strcmp(device_name, "light9") == 0) )
    {
      if (!state)
      {
        digitalWrite(relay_nin, HIGH);
      }
      else
      {
        digitalWrite(relay_nin, LOW);
      }
    }

    if ( (strcmp(device_name, "light10") == 0) ) 
    {
      if (!state) 
      {
        digitalWrite(relay_one, HIGH);
        digitalWrite(relay_two, HIGH);
        digitalWrite(relay_thr, HIGH);
        digitalWrite(relay_for, HIGH);
        digitalWrite(relay_fiv, HIGH);
        digitalWrite(relay_six, HIGH);
        digitalWrite(relay_sev, HIGH);
        digitalWrite(relay_eig, HIGH);
        digitalWrite(relay_nin, HIGH);
      } 
      else 
      {
        digitalWrite(relay_one, LOW);
        digitalWrite(relay_two, LOW);
        digitalWrite(relay_thr, LOW);
        digitalWrite(relay_for, LOW);
        digitalWrite(relay_fiv, LOW);
        digitalWrite(relay_six, LOW);
        digitalWrite(relay_sev, LOW);
        digitalWrite(relay_eig, LOW);
        digitalWrite(relay_nin, LOW);
      }
    }
  }
  );
}

void loop() 
{
  // fauxmoESP uses an async TCP server but a sync UDP server
  // Therefore, we have to manually poll for UDP packets
  fauxmo.handle();

}