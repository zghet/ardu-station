#include <ESP8266WiFi.h>

#include "fauxmoESP.h" 

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

#define luz1 "luz cuarto"
#define luz2 "luz visita"
#define luz3 "luz baño"
#define luz4 "luz sala"

fauxmoESP fauxmo;

void setup() 
{
  Serial.begin(115200);
  ConnectWiFi_STA();

  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_1, HIGH);

  pinMode(RELAY_PIN_2, OUTPUT);
  digitalWrite(RELAY_PIN_2, HIGH);

  pinMode(RELAY_PIN_3, OUTPUT);
  digitalWrite(RELAY_PIN_3, HIGH);

  pinMode(RELAY_PIN_4, OUTPUT);
  digitalWrite(RELAY_PIN_4, HIGH);
  
  fauxmo.createServer(true); // not needed, this is the default value
  fauxmo.setPort(80); // This is required for gen3 devices
  fauxmo.enable(true);

  // Add virtual devices
  fauxmo.addDevice(luz1);
  fauxmo.addDevice(luz2);
  fauxmo.addDevice(luz3);
  fauxmo.addDevice(luz4);

///****************************************************************************************

  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) 
  {
    // Callback when a command from Alexa is received. 
    // You can use device_id or device_name to choose the element to perform an action onto (relay, LED,...)
    // State is a boolean (ON/OFF) and value a number from 0 to 255 (if you say "set kitchen light to 50%" you will receive a 128 here).
    // Just remember not to delay too much here, this is a callback, exit as soon as possible.
    // If you have to do something more involved here set a flag and process it in your main loop.
        
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    if ( (strcmp(device_name, luz1) == 0) ) 
    {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 1 switched by Alexa");
      //digitalWrite(RELAY_PIN_1, !digitalRead(RELAY_PIN_1));
      if (state) 
      {
        digitalWrite(RELAY_PIN_1, LOW);
      } 
      else 
      {
        digitalWrite(RELAY_PIN_1, HIGH);
      }
    }

   // *************************************************************************  

    if ( (strcmp(device_name, luz2) == 0) ) 
    {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 2 switched by Alexa");
      if (state) 
      {
        digitalWrite(RELAY_PIN_2, LOW);
      } else 
      {
        digitalWrite(RELAY_PIN_2, HIGH);
      }
    }
   
     //*************************************************************************  
     
    if ( (strcmp(device_name, luz3) == 0) ) 
    {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 2 switched by Alexa");
      if (state) 
      {
        digitalWrite(RELAY_PIN_2, LOW);
      } else 
      {
        digitalWrite(RELAY_PIN_2, HIGH);
      }
    }
  
     //*************************************************************************  
     
    if ( (strcmp(device_name, luz3) == 0) ) 
    {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 2 switched by Alexa");
      if (state) 
      {
        digitalWrite(RELAY_PIN_2, LOW);
      } else 
      {
        digitalWrite(RELAY_PIN_2, HIGH);
      }
    }
  });
    ///****************************************************************************************
  
}

void loop() 
{
  // fauxmoESP uses an async TCP server but a sync UDP server
  // Therefore, we have to manually poll for UDP packets
  fauxmo.handle();

  
}
