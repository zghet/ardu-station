// Incluimos librería de sensor de temperatura y humedad
#include <DHT.h>

//libreria Ethernet
#include <SPI.h>
#include <Ethernet.h>

//Libreria LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(4, 8, 9, 10, 11 , 12);

////////////////////////////////////////////////////////////////////////////
 
// the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 

// the dns server ip
IPAddress dnServer(192, 168, 15, 1);

// the router gateway address:
IPAddress gateway(192, 168, 15, 1);

// the subnet:
IPAddress subnet(255, 255, 255, 0);

//the IP address is dependent on your network
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
  
  // MOVER EL CURSOR A LA PRIMERA POSICION DE LA PANTALLA (0, 0)
  //Se inicializa LCD
  lcd.begin(16,2);
  lcd.home();

  // initialize the ethernet device
  Ethernet.begin(mac, ip, dnServer, gateway, subnet);

}

////////////////////////////////////////////////////////////////////////////

void loop() 
{
  // EN EL CICLO PRINCIPAL SOLAMENTE RECORREMOS EL MENSAJE DE UN LADO A OTRO
  // VARIABLE PARA CONTROL DE CICLOS
  int i;

  // Esperamos 4 segundos entre medidas
  delay(4000);

  // DESPLAZAR LA PANTALLA A LA DERECHA 2 VECES
  for ( int i = 0; i < 5; i++ ) 
  {
    lcd.scrollDisplayRight();
    delay (1000);
  }

  // DESPLAZAR LA PANTALLA A LA IZQUIERDA 2 VECES
  for ( int i = 0; i < 5; i++ ) 
  {
    lcd.scrollDisplayLeft();
    delay (1000);
  }

  // Leemos la humedad relativa
  float h = dht.readHumidity();

  // Leemos la temperatura en grados centígrados (por defecto)
  float t = dht.readTemperature();
     
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t))
  {
    // || isnan(f)) 
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  // Calcular el índice de calor en grados centígrados
  float hic = dht.computeHeatIndex(t, h, false);
 
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" *C\n");

  //Impresion de temp y humedad  
  delay(4000);
  lcd.setCursor(0,0);
  lcd.write("Temp: ");
  lcd.setCursor(5,0);
  lcd.print(t);

  lcd.setCursor(0,1);
  lcd.print("Humedad: ");
  lcd.setCursor(8,1);
  lcd.print(h);

  // Limpiamos la pantalla
  //lcd.clear();
  
  //print out the IP address
  //delay(4000);
  //lcd.setCursor(9,1);
  //lcd.print("IP = ");
  //lcd.print(Ethernet.localIP());
  
  // Limpiamos la pantalla
  //lcd.clear();
 
}
