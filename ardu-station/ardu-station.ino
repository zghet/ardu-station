// Incluimos librería de sensor de temperatura y humedad
#include <DHT.h>

//libreria APIRest
#include <aREST.h>

//libreria Ethernet
#include <SPI.h>
#include <Ethernet.h>

//Libreria LCDI2C
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
//Se declara el tipo de LCD a usar
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

////////////////////////////////////////////////////////////////////////////
 
// Declaracion de mac address para shield ethernet:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 

// DNS Server
IPAddress dnServer(192, 168, 15, 1);

// Gateway:
IPAddress gateway(192, 168, 15, 1);

// Subnet:
IPAddress subnet(255, 255, 255, 0);

//ip Direction 
IPAddress ip(192, 168, 15, 20);

//InicializarCrear la instancia del server
EthernetServer server(81);


//////////////////////statement of variables and ports///////////////////////////////////

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);

//Ports
#define LISTEN_PORT 81

//rest
aREST rest = aREST();

//definimos variables para la api
float humidity, temperature;

////////////////////////////////////////////////////////////////////////////

void setup()
{

  //API
  rest.variable("Temperatura:", &temperature);
  rest.variable("Humedad:", &humidity);
  
  //identificacion
  rest.set_id("1");
  rest.set_name("Sensor NanoMCUv3");

  //////////////////////////////////////////////////////////////////////
  
  // Inicializamos comunicación serie
  Serial.begin(9600);
     
 // Comenzamos el sensor DHT
  dht.begin();
  
  //Se inicializa LCD
  lcd.begin(16, 2);
  
  // initialize the ethernet device
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);

  //inicializar servidor web
  server.begin();
  Serial.println("Server inicializado");
}

////////////////////////////////////////////////////////////////////////////

void loop() 
{

  // Esperamos 3 segundos entre medidas
  delay(3000);

 // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
   
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t))
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    lcd.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
  /////////////////////////////////////////////////
  
  //Impresion de temp
  lcd.setCursor(0,0);
  lcd.write("Temp: ");
  lcd.setCursor(5,0);
  lcd.print(t);
  
  //Impresion de  humedad 
  lcd.setCursor(0,1);
  lcd.print("Humedad: ");
  lcd.setCursor(8,1);
  lcd.print(h);


}
