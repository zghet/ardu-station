// Incluimos librería de sensor de temperatura y humedad
#include <DHT.h>

//libreria Ethernet
#include <SPI.h>
#include <Ethernet.h>

//Libreria LCD
#include <LiquidCrystal_I2C.h>
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

////////////////////////////////////////////////////////////////////////////

// Definimos el pin digital donde se conecta el sensor
#define DHTPIN 2
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11

// Inicializamos el sensor DHT11
DHT dht(DHTPIN, DHTTYPE);
 
 ////////////////////////////////////////////////////////////////////////////

void setup()
{
  // Inicializamos comunicación serie
  Serial.begin(9600);
 
  // Comenzamos el sensor DHT
  dht.begin();
  
  //Se inicializa LCD
  lcd.begin(16, 2);
  // Mover el cursor a la primera posición de la pantalla (0, 0)
  lcd.clear();

  // initialize the ethernet device
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);

}

////////////////////////////////////////////////////////////////////////////

void loop() 
{
// Esperamos 4 segundos entre medidas
  delay(500);

 // Leemos la humedad relativa
  float h = dht.readHumidity();
  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
   
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t))
  {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }
 
    // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);

 /////////////////////////////////////////////////
 //Impresion Serial
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C\n ");


/////////////////////////////////////////////////
  //desplazamos una posición a la izquierda
  lcd.scrollDisplayLeft(); 
  delay(500);
  // Actualizar la pantalla completa cada segundo
  //lcd.clear();
  //Impresion de temp
  //delay(4000);
  lcd.setCursor(0,0);
  lcd.write("Temp: ");
  lcd.setCursor(5,0);
  lcd.print(t);
  //Impresion de  humedad 
  lcd.setCursor(0,1);
  lcd.print("Humedad: ");
  lcd.setCursor(8,1);
  lcd.print(h);
  //Impresion de ip
  lcd.setCursor(14,0);
  lcd.print("IP: ");
  lcd.setCursor(17,0);
  lcd.print("192.168.15.20"); 
}
